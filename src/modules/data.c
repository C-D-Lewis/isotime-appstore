#include "data.h"

#if defined(PBL_COLOR)
static GColor s_colors[ColorMax];
#endif

void data_init() {
#if defined(PBL_COLOR)
  if(persist_exists(ColorBackground)) {
    // Load the data
    for(int i = 0; i < ColorMax; i++) {
      s_colors[i] = (GColor){ .argb = persist_read_int(i) };
    }
  } else {
    // Default colors
    s_colors[ColorBackground] = GColorBlack;
    s_colors[ColorSides] = GColorOrange;
    s_colors[ColorFace] = GColorYellow;

    // Write defaults
    for(int i = 0; i < ColorMax; i++) {
      persist_write_int(i, s_colors[i].argb);
    }
  }
#endif

  // Other settings
}

void data_set_color(Color which, GColor new_color) {
#if defined(PBL_COLOR)
  s_colors[which] = new_color;
  persist_write_int(which, new_color.argb);
#endif
}

GColor data_get_color(Color which) {
#if defined(PBL_COLOR)
  return s_colors[which];
#endif

  // Dummy B&W value
  return GColorWhite;
}
