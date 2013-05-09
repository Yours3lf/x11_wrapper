#include "screen.h"

#include <X11/Xlib.h>

namespace x11
{
  int screen::when_mapped = WhenMapped;
  int screen::not_useful = NotUseful;
  int screen::always = Always;

  long unsigned int screen::black_pixel_of_screen()
  {
    return XBlackPixelOfScreen( static_cast<Screen*>( data ) );
  }

  long unsigned int screen::white_pixel_of_screen()
  {
    return XWhitePixelOfScreen( static_cast<Screen*>( data ) );
  }

  int screen::cells_of_screen()
  {
    return XCellsOfScreen( static_cast<Screen*>( data ) );
  }

  long unsigned int screen::default_colormap_of_screen()
  {
    return XDefaultColormapOfScreen( static_cast<Screen*>( data ) );
  }

  int screen::default_depth_of_screen()
  {
    return XDefaultDepthOfScreen( static_cast<Screen*>( data ) );
  }

  void* screen::default_gc_of_screen()
  {
    return XDefaultGCOfScreen( static_cast<Screen*>( data ) );
  }

  void* screen::default_visual_of_screen()
  {
    return XDefaultVisualOfScreen( static_cast<Screen*>( data ) );
  }

  int screen::does_backing_store()
  {
    return XDoesBackingStore( static_cast<Screen*>( data ) );
  }

  bool screen::does_save_unders()
  {
    return XDoesSaveUnders( static_cast<Screen*>( data ) );
  }

  display screen::display_of_screen()
  {
    return display( XDisplayOfScreen( static_cast<Screen*>( data ) ) );
  }

  int screen::screen_number_of_screen()
  {
    return XScreenNumberOfScreen( static_cast<Screen*>( data ) );
  }

  long int screen::event_mask_of_screen()
  {
    return XEventMaskOfScreen( static_cast<Screen*>( data ) );
  }

  int screen::width_of_screen()
  {
    return XWidthOfScreen( static_cast<Screen*>( data ) );
  }

  int screen::height_of_screen()
  {
    return XHeightOfScreen( static_cast<Screen*>( data ) );
  }

  int screen::width_mm_of_screen()
  {
    return XWidthMMOfScreen( static_cast<Screen*>( data ) );
  }

  int screen::height_mm_of_screen()
  {
    return XHeightMMOfScreen( static_cast<Screen*>( data ) );
  }

  int screen::max_cmaps_of_screen()
  {
    return XMaxCmapsOfScreen( static_cast<Screen*>( data ) );
  }

  int screen::min_cmaps_of_screen()
  {
    return XMinCmapsOfScreen( static_cast<Screen*>( data ) );
  }

  int screen::planes_of_screen()
  {
    return XPlanesOfScreen( static_cast<Screen*>( data ) );
  }

  long unsigned int screen::root_window_of_screen()
  {
    return XRootWindowOfScreen( static_cast<Screen*>( data ) );
  }
}
