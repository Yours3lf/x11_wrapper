#ifndef window_h
#define window_h

#include "display.h"

namespace x11
{
  class window
  {
      unsigned long data;
    public:
      static unsigned int input_only;
      static unsigned int input_output;
      static int copy_from_parent;
      static int raise_lowest;
      static int lower_highest;
      static int prop_mode_replace;
      static int prop_mode_prepend;
      static int prop_mode_append;

      window( unsigned long d = 0 ): data( d ) {}

      unsigned long get()
      {
        return data;
      }

      void create_window( display d, window parent = window(), int x = 0, int y = 0, unsigned int width = 0, unsigned int height = 0, unsigned int border_width = 0, int depth = 0, unsigned int win_class = 0, void* visual = 0, unsigned long valuemask = 0, void* attributes = 0 );
      void create_simple_window( display d, window parent = window(), int x = 0, int y = 0, unsigned int width = 0, unsigned int height = 0, unsigned int border_width = 0, unsigned long border = 0, unsigned long background = 0 );

      void destroy_window( display d );
      void destroy_subwindows( display d );

      void map_window( display d );
      void map_raised( display d );
      void map_subwindows( display d );

      void unmap_window( display d );
      void unmap_subwindows( display d );

      void configure_window( display d, unsigned int value_mask = 0, void* values = 0 );
      void move_window( display d, int x = 0, int y = 0 );
      void resize_window( display d, unsigned int width = 0, unsigned int height = 0 );
      void move_resize_window( display d, int x = 0, int y = 0, unsigned int width = 0, unsigned int height = 0 );
      void set_window_border_width( display d, unsigned int width = 0 );

      void raise_window( display d );
      void lower_window( display d );
      void circulate_subwindows( display d, int direction = 0 );
      void circulate_subwindows_up( display d );
      void circulate_subwindows_down( display d );
      void restack_windows( display d, const std::vector<window>& windows );

      void change_window_attributes( display d, unsigned long valuemask = 0, void* attributes = 0 );
      void set_window_background( display d, unsigned long background_pixel = 0 );
      void set_window_background_pixmap( display d, unsigned long pixmap = 0 );
      void set_window_border( display d, unsigned long border_pixel = 0 );
      void set_window_border_pixmap( display d, unsigned long border_pixmap = 0 );
      void set_window_colormap( display d, unsigned long colormap = 0 );
      void define_cursor( display d, unsigned long cursor = 0 );
      void undefine_cursor( display d );

      bool query_tree( display d, window& root, window& parent, std::vector<window>& children );
      bool get_window_attributes( display d, void* attributes = 0 );
      bool get_geometry( display d, unsigned long drawable, window& root, int& x, int& y, unsigned int& width, unsigned int& height, unsigned int& border_width, unsigned int& depth );

      bool translate_coordinates( display d, window src, window dst, int src_x, int src_y, int& dst_x, int& dst_y, window& child );
      bool query_pointer( display d, window& root, window& child, int& root_x, int& root_y, int& win_x, int& win_y, unsigned int& mask );

      bool get_window_property_char( display d, class atom property_name, long prop_offset, std::vector<char>& property );
      bool get_window_property_short( display d, class atom property_name, long prop_offset, std::vector<short>& property );
      bool get_window_property_long( display d, class atom property_name, long prop_offset, std::vector<long>& property );

      void change_property_char( display d, class atom property, class atom type, int mode, const std::vector<char>& data );
      void change_property_short( display d, class atom property, class atom type, int mode, const std::vector<short>& data );
      void change_property_long( display d, class atom property, class atom type, int mode, const std::vector<long>& data );

      void list_properties( display d, std::vector<class atom>& atoms );
      void rotate_window_properties( display d, const std::vector<class atom>& atoms, int npositions = 0 );
      void delete_property( display d, class atom property );

      window get_selection_owner( display d, class atom selection );
      void convert_selection( display d, class atom selection, class atom target, class atom property, unsigned long time = 0 );
      void set_selection_owner( display d, class atom selection, unsigned long time = 0 );
  };
}

#endif


