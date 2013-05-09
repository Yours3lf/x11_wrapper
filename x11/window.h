#ifndef window_h
#define window_h

#include "display.h"

namespace x11
{
  struct window_attributes
  {
    int x, y;     /* location of window */
    int width, height;    /* width and height of window */
    int border_width;   /* border width of window */
    int depth;      /* depth of window */
    void* visual;     /* the associated visual structure */
    unsigned long root;      /* root of screen containing window */
    int classid;      /* InputOutput, InputOnly*/
    int bit_gravity;    /* one of the bit gravity values */
    int win_gravity;    /* one of the window gravity values */
    int backing_store;    /* NotUseful, WhenMapped, Always */
    unsigned long backing_planes; /* planes to be preserved if possible */
    unsigned long backing_pixel;  /* value to be used when restoring planes */
    bool save_under;    /* boolean, should bits under be saved? */
    unsigned long colormap;    /* color map to be associated with window */
    bool map_installed;   /* boolean, is color map currently installed*/
    int map_state;      /* IsUnmapped, IsUnviewable, IsViewable */
    long all_event_masks;   /* set of events all people have interest in*/
    long your_event_mask;   /* my event mask */
    long do_not_propagate_mask; /* set of events that should not propagate */
    bool override_redirect;   /* boolean value for override-redirect */
    void* screen;     /* back pointer to correct screen */
    window_attributes( int xx = 0, int yy = 0, int w = 0, int h = 0, int bw = 0, int de = 0,
                       void* vi = 0, unsigned long ro = 0, int clid = 0, int bg = 0, int wg = 0, int bs = 0,
                       unsigned long bap = 0, unsigned long bapi = 0, bool su = false, unsigned long cm = 0, bool mi = false,
                       int ms = 0, long aem = 0, long yem = 0, long dnpm = 0, bool ovr = 0, void* sc = 0 )
    {
      x = xx;
      y = yy;
      width = w;
      height = h;
      border_width = bw;
      depth = de;
      visual = vi;
      root = ro;
      classid = clid;
      bit_gravity = bg;
      win_gravity = wg;
      backing_store = bs;
      backing_planes = bap;
      backing_pixel = bapi;
      save_under = su;
      colormap = cm;
      map_installed = mi;
      map_state = ms;
      all_event_masks = aem;
      your_event_mask = yem;
      do_not_propagate_mask = dnpm;
      override_redirect = ovr;
      screen = sc;
    }
  };

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
      bool get_window_attributes( display d, window_attributes& attributes );
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


