#ifndef display_h
#define display_h

#include <iostream>
#include <vector>

namespace x11
{
  struct pixel_format_values
  {
    int depth, bits_per_pixel, scanline_pad;
    pixel_format_values( int d = 0, int b = 0, int s = 0 )
    {
      depth = d;
      bits_per_pixel = b;
      scanline_pad = s;
    }
  };

  class display
  {
      void* data;
    public:
      static int destroy_all;
      static int retain_permanent;
      static int retain_temporary;

      static int lsb_first;
      static int msb_first;

      display( void* d = 0 ): data( d ) {}

      void* get()
      {
        return data;
      }

      void open_display( const std::string& name = "" );
      unsigned long all_planes();
      unsigned long black_pixel( int screen_num = 0 );
      unsigned long white_pixel( int screen_num = 0 );
      int connection_number();
      unsigned long default_colormap( int screen_num = 0 );
      int default_depth( int screen_num = 0 );
      void list_depths( std::vector<int>& v, int screen_num = 0 );
      void* default_gc( int screen_num = 0 );
      class window default_root_window();
      class screen default_screen_of_display();
      class screen screens_of_display( int screen_num = 0 );
      int default_screen();
      void* default_visual( int screen_num = 0 );
      int screen_cells( int screen_num = 0 );
      int screen_planes( int screen_num = 0 );
      std::string display_string( int screen_num = 0 );
      long extended_max_request_size();
      long max_request_size();
      unsigned long last_known_request_processed();
      unsigned long next_request();
      int protocol_version();
      int protocol_revision();
      int q_length();
      class window root_window( int screen_num = 0 );
      int screen_count();
      std::string server_vendor();
      int vendor_release();

      void list_pixmap_formats( std::vector<pixel_format_values>& v );
      int image_byte_order();
      int bitmap_unit();
      int bitmap_bit_order();
      int bitmap_pad();
      int screen_height( int screen_num = 0 );
      int screen_height_mm( int screen_num = 0 );
      int screen_width( int screen_num = 0 );
      int screen_width_mm( int screen_num = 0 );

      void close();
      void set_close_down_mode( int cm = 0 );

      void syncronize( bool onoff = false );
      void sync( bool discard = false );
      void flush();

      void set_error_handler( void* func = 0 );
  };
}

#endif

