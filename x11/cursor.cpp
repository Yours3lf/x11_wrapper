#include "cursor.h"

#include "pixmap.h"

#include <X11/Xlib.h>

namespace x11
{
  void cursor::create_font_cursor( display d, unsigned int shape )
  {
    data = XCreateFontCursor( static_cast<Display*>( d.get() ), shape );
  }

  void cursor::create_glyph_cursor( display d, long unsigned int font_source, long unsigned int mask_font, unsigned int source_char, unsigned int mask_char, void* foreground_color, void* background_color )
  {
    data = XCreateGlyphCursor( static_cast<Display*>( d.get() ), font_source, mask_font, source_char, mask_char, static_cast<XColor*>( foreground_color ), static_cast<XColor*>( background_color ) );
  }

  void cursor::create_pixmap_cursor( display d, pixmap source, pixmap mask, void* foreground_color, void* background_color, unsigned int x, unsigned int y )
  {
    data = XCreatePixmapCursor( static_cast<Display*>( d.get() ), source.get(), mask.get(), static_cast<XColor*>( foreground_color ), static_cast<XColor*>( background_color ), x, y );
  }

  bool cursor::query_best_cursor( display d, long unsigned int drawable, unsigned int width, unsigned int height, unsigned int& width_ret, unsigned int& height_ret )
  {
    unsigned int w, h;
    bool ret = XQueryBestCursor( static_cast<Display*>( d.get() ), drawable, width, height, &w, &h );
    width_ret = w;
    height_ret = h;
    return ret;
  }

  void cursor::recolor_cursor( display d, void* foreground_color, void* background_color )
  {
    XRecolorCursor( static_cast<Display*>( d.get() ), data, static_cast<XColor*>( foreground_color ), static_cast<XColor*>( background_color ) );
  }

  void cursor::free_cursor( display d )
  {
    XFreeCursor( static_cast<Display*>( d.get() ), data );
  }
}
