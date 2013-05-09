#include "pixmap.h"

#include <X11/Xlib.h>

namespace x11
{
  void pixmap::create_pixmap( display d, long unsigned int drawable, unsigned int width, unsigned int height, unsigned int depth )
  {
    XCreatePixmap( static_cast<Display*>( d.get() ), drawable, width, height, depth );
  }

  void x11::pixmap::free_pixmap( display d )
  {
    XFreePixmap( static_cast<Display*>( d.get() ), data );
  }
}
