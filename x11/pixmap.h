#ifndef pixmap_h
#define pixmap_h

#include "display.h"

namespace x11
{
  class pixmap
  {
      unsigned long data;
    public:
      pixmap( unsigned long d = 0 ): data( d ) {}

      unsigned long get()
      {
        return data;
      }

      void create_pixmap( display d, unsigned long drawable, unsigned int width, unsigned int height, unsigned int depth );
      void free_pixmap( display d );
  };
}

#endif
