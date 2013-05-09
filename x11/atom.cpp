#include "atom.h"

#include <X11/Xlib.h>
#include <string.h>

namespace x11
{
  void atom::intern_atom( display d, const std::string& atom_name, bool only_if_exists )
  {
    data = XInternAtom( static_cast<Display*>( d.get() ), atom_name.c_str(), only_if_exists );
  }

  bool atom::intern_atoms( display d, const std::vector< std::string >& names, bool only_if_exists, std::vector< atom >& atoms )
  {
    Atom* array = new Atom[names.size()];
    char** namesarray = new char*[names.size()];

    for( int c = 0; c < names.size(); ++c )
    {
      namesarray[c] = new char[names[c].length() + 1];
      memcpy( namesarray[c], names[c].c_str(), names[c].length() );
      namesarray[c][names[c].length()] = '\0';
    }

    int ret = XInternAtoms( static_cast<Display*>( d.get() ), namesarray, names.size(), only_if_exists, array );

    for( int c = 0; c < names.size(); ++c )
    {
      atoms.push_back( array[c] );
      delete [] namesarray[c];
    }

    delete [] array;
    delete [] namesarray;
    return ret;
  }

  std::string atom::get_atom_name( display d )
  {
    char* name = XGetAtomName( static_cast<Display*>( d.get() ), data );
    std::string s( name );
    XFree( name );
    return s;
  }

  bool atom::get_atom_names( display d, const std::vector< atom >& atoms, std::vector< std::string >& names )
  {
    char** namesarray = new char*[names.size()];
    int ret = XGetAtomNames( static_cast<Display*>( d.get() ), ( Atom* )&atoms[0], atoms.size(), namesarray );

    for( int c = 0; c < atoms.size(); ++c )
    {
      names.push_back( namesarray[c] );
      XFree( namesarray[c] );
    }

    delete [] namesarray;
    return ret;
  }
}
