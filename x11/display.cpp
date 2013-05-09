#include "display.h"

#include <X11/Xlib.h>

#include "window.h"
#include "screen.h"

namespace x11
{
  int display::destroy_all = DestroyAll;
  int display::retain_permanent = RetainPermanent;
  int display::retain_temporary = RetainTemporary;

  int display::lsb_first = LSBFirst;
  int display::msb_first = MSBFirst;

  void display::open_display( const std::string& name )
  {
    data = XOpenDisplay( name.c_str() );
  }

  unsigned long display::all_planes()
  {
    return XAllPlanes();
  }

  unsigned long display::black_pixel( int screen_num )
  {
    return XBlackPixel( static_cast<Display*>( data ), screen_num );
  }

  unsigned long display::white_pixel( int screen_num )
  {
    return XWhitePixel( static_cast<Display*>( data ), screen_num );
  }

  int display::connection_number()
  {
    return XConnectionNumber( static_cast<Display*>( data ) );
  }

  long unsigned int display::default_colormap( int screen_num )
  {
    return XDefaultColormap( static_cast<Display*>( data ), screen_num );
  }

  int display::default_depth( int screen_num )
  {
    return XDefaultDepth( static_cast<Display*>( data ), screen_num );
  }

  void display::list_depths( std::vector< int >& v, int screen_num )
  {
    int count = 0;
    int* tmp = XListDepths( static_cast<Display*>( data ), screen_num, &count );

    for( int c = 0; c < count; ++c )
      v.push_back( tmp[c] );

    XFree( tmp );
  }

  void* display::default_gc( int screen_num )
  {
    return XDefaultGC( static_cast<Display*>( data ), screen_num );
  }

  window display::default_root_window()
  {
    return window( XDefaultRootWindow( static_cast<Display*>( data ) ) );
  }

  screen display::default_screen_of_display()
  {
    return screen( XDefaultScreenOfDisplay( static_cast<Display*>( data ) ) );
  }

  screen display::screens_of_display( int screen_num )
  {
    return screen( XScreenOfDisplay( static_cast<Display*>( data ), screen_num ) );
  }

  int display::default_screen()
  {
    return XDefaultScreen( static_cast<Display*>( data ) );
  }

  void* display::default_visual( int screen_num )
  {
    return XDefaultVisual( static_cast<Display*>( data ), screen_num );
  }

  int display::screen_cells( int screen_num )
  {
    return XDisplayCells( static_cast<Display*>( data ), screen_num );
  }

  int display::screen_planes( int screen_num )
  {
    return XDisplayPlanes( static_cast<Display*>( data ), screen_num );
  }

  std::string display::display_string( int screen_num )
  {
    return std::string( XDisplayString( static_cast<Display*>( data ) ) );
  }

  long int display::extended_max_request_size()
  {
    return XExtendedMaxRequestSize( static_cast<Display*>( data ) );
  }

  long int display::max_request_size()
  {
    return XMaxRequestSize( static_cast<Display*>( data ) );
  }

  long unsigned int display::last_known_request_processed()
  {
    return XLastKnownRequestProcessed( static_cast<Display*>( data ) );
  }

  long unsigned int display::next_request()
  {
    return XNextRequest( static_cast<Display*>( data ) );
  }

  int display::protocol_version()
  {
    return XProtocolRevision( static_cast<Display*>( data ) );
  }

  int display::protocol_revision()
  {
    return XProtocolRevision( static_cast<Display*>( data ) );
  }

  int display::q_length()
  {
    return XQLength( static_cast<Display*>( data ) );
  }

  window display::root_window( int screen_num )
  {
    return window( XRootWindow( static_cast<Display*>( data ), screen_num ) );
  }

  int display::screen_count()
  {
    return XScreenCount( static_cast<Display*>( data ) );
  }

  std::string display::server_vendor()
  {
    return std::string( XServerVendor( static_cast<Display*>( data ) ) );
  }

  int display::vendor_release()
  {
    return XVendorRelease( static_cast<Display*>( data ) );
  }

  void display::list_pixmap_formats( std::vector< pixel_format_values >& v )
  {
    int count = 0;
    XPixmapFormatValues* tmp = 0;
    tmp = XListPixmapFormats( static_cast<Display*>( data ), &count );

    for( int c = 0; c < count; ++c )
      v.push_back( pixel_format_values( tmp[c].depth, tmp[c].bits_per_pixel, tmp[c].scanline_pad ) );

    XFree( tmp );
  }

  int display::image_byte_order()
  {
    return XImageByteOrder( static_cast<Display*>( data ) );
  }

  int display::bitmap_unit()
  {
    return XBitmapUnit( static_cast<Display*>( data ) );
  }

  int display::bitmap_bit_order()
  {
    return XBitmapBitOrder( static_cast<Display*>( data ) );
  }

  int display::bitmap_pad()
  {
    return XBitmapPad( static_cast<Display*>( data ) );
  }

  int display::screen_height( int screen_num )
  {
    return XDisplayHeight( static_cast<Display*>( data ), screen_num );
  }

  int display::screen_height_mm( int screen_num )
  {
    return XDisplayHeightMM( static_cast<Display*>( data ), screen_num );
  }

  int display::screen_width( int screen_num )
  {
    return XDisplayWidth( static_cast<Display*>( data ), screen_num );
  }

  int display::screen_width_mm( int screen_num )
  {
    return XDisplayWidthMM( static_cast<Display*>( data ), screen_num );
  }

  void display::close()
  {
    XCloseDisplay( static_cast<Display*>( data ) );
    data = 0;
  }

  void display::set_close_down_mode( int cm )
  {
    XSetCloseDownMode( static_cast<Display*>( data ), cm );
  }

  void display::syncronize( bool onoff )
  {
    XSynchronize( static_cast<Display*>( data ), onoff );
  }

  void display::flush()
  {
    XFlush( static_cast<Display*>( data ) );
  }
}
