#include <iostream>

#include "x11/window.h"
#include "x11/display.h"
#include "x11/screen.h"
#include "x11/atom.h"

int main( int argc, char** argv )
{
  x11::display d;
  d.open_display();
  d.syncronize( true );

  std::vector<x11::pixel_format_values> pfvs;
  d.list_pixmap_formats( pfvs );

  x11::screen s = d.default_screen_of_display();

  x11::window w;
  w.create_simple_window( d, d.default_root_window(), 0, 0, 300, 100 );

  std::cout << d.display_string() << std::endl;
  std::cout << s.height_mm_of_screen() << std::endl;

  std::vector<x11::window> ws;
  ws.push_back( w );
  w.restack_windows( d, ws );

  x11::window root;
  x11::window parent;
  std::vector<x11::window> children;
  w.query_tree( d, root, parent, children );

  x11::atom a;
  std::vector<std::string > names;
  std::vector<x11::atom> atoms;
  names.push_back( "WM_NAME" );
  a.intern_atoms( d, names, false, atoms );

  a.intern_atom( d, "STRING" );
  std::string name = "hello world";
  std::vector<char> str( name.begin(), ++name.end() ); //include the closing 0 as well
  w.change_property_char( d, atoms[0], a, x11::window::prop_mode_replace, str );

  std::vector<char> array;
  bool ret = w.get_window_property_char( d, atoms[0], 0, array );

  w.rotate_window_properties( d, atoms, 1 );

  x11::atom client_list_atom;
  client_list_atom.intern_atom( d, "_NET_CLIENT_LIST" );
  x11::atom wm_name_atom;
  wm_name_atom.intern_atom( d, "_NET_WM_NAME" );

  std::vector<long> client_list;
  d.default_root_window().get_window_property_long( d, client_list_atom, 0, client_list );

  for( int c = 0; c < client_list.size(); ++c )
  {
    x11::window tmp( client_list[c] );
    std::vector<char> name;
    tmp.get_window_property_char( d, wm_name_atom, 0, name );
    name.push_back( '\0' );
    std::cout << &name[0] << std::endl;
  }

  std::vector<long> num_desktops;
  x11::atom num_desktops_atom;
  num_desktops_atom.intern_atom( d, "_NET_NUMBER_OF_DESKTOPS" );
  d.default_root_window().get_window_property_long( d, num_desktops_atom, 0, num_desktops );

  for( int c = 0; c < num_desktops.size(); ++c )
  {
    std::cout << "Num desktops: " << num_desktops[c] << std::endl;
  }

  std::vector<long> desktop_geometry;
  x11::atom desktop_geometry_atom;
  desktop_geometry_atom.intern_atom( d, "_NET_DESKTOP_GEOMETRY" );
  d.default_root_window().get_window_property_long( d, desktop_geometry_atom, 0, desktop_geometry );

  for( int c = 0; c < desktop_geometry.size(); ++c )
  {
    std::cout << "Desktop geometry: " << desktop_geometry[c] << std::endl;
  }

  std::vector<long> current_desktop;
  x11::atom current_desktop_atom;
  current_desktop_atom.intern_atom( d, "_NET_CURRENT_DESKTOP" );
  d.default_root_window().get_window_property_long( d, current_desktop_atom, 0, current_desktop );

  for( int c = 0; c < current_desktop.size(); ++c )
  {
    std::cout << "Current desktop: " << current_desktop[c] << std::endl;
  }
  
  //clipboard input
  //std::string str = "hello world";

  w.map_window( d );

  d.flush();

  sleep( 10 );

  std::cout << "Hello, world!" << std::endl;
  return 0;
}
