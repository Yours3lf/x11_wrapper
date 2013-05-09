#ifndef atom_h
#define atom_h

#include "display.h"

namespace x11
{
  class atom
  {
      unsigned long data;
    public:
      atom( unsigned long d = 0 ): data( d ) {}

      unsigned long get()
      {
        return data;
      }

      void intern_atom( display d, const std::string& atom_name = "", bool only_if_exists = false );
      bool intern_atoms( display d, const std::vector<std::string>& names, bool only_if_exists, std::vector<atom>& atoms );
      std::string get_atom_name( display d );
      bool get_atom_names( display d, const std::vector<atom>& atoms, std::vector<std::string>& names );
  };
}

#endif
