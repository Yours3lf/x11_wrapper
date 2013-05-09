#ifndef cursor_h
#define cursor_h

#include "display.h"

namespace x11
{
  class cursor
  {
      unsigned long data;
    public:
      cursor( unsigned long d = 0 ): data( d ) {}

      unsigned long get()
      {
        return data;
      }

      void create_font_cursor( display d, unsigned int shape = 0 );
      void create_glyph_cursor( display d, unsigned long font_source = 0, unsigned long mask_font = 0, unsigned int source_char = 0, unsigned int mask_char = 0, void* foreground_color = 0, void* background_color = 0 );
      void create_pixmap_cursor( display d, class pixmap source, class pixmap mask, void* foreground_color, void* background_color, unsigned int x, unsigned int y );
      bool query_best_cursor( display d, unsigned long drawable, unsigned int width, unsigned int height, unsigned int& width_ret, unsigned int& height_ret );
      void recolor_cursor( display d, void* foreground_color, void* background_color );
      void free_cursor( display d );
  };
}

#endif
