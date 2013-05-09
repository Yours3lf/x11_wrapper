#ifndef screen_h
#define screen_h

#include "display.h"

namespace x11
{
  class screen
  {
      void* data;
    public:
      static int when_mapped;
      static int not_useful;
      static int always;

      screen( void* d = 0 ): data( d ) {}

      void* get()
      {
        return data;
      }

      unsigned long black_pixel_of_screen();
      unsigned long white_pixel_of_screen();
      int cells_of_screen();
      unsigned long default_colormap_of_screen();
      int default_depth_of_screen();
      void* default_gc_of_screen();
      void* default_visual_of_screen();
      int does_backing_store();
      bool does_save_unders();
      display display_of_screen();
      int screen_number_of_screen();
      long event_mask_of_screen();
      int width_of_screen();
      int height_of_screen();
      int width_mm_of_screen();
      int height_mm_of_screen();
      int max_cmaps_of_screen();
      int min_cmaps_of_screen();
      int planes_of_screen();
      unsigned long root_window_of_screen();
  };
}

#endif
