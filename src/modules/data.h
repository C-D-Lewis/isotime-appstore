#pragma once

#include <pebble.h>

typedef enum {
  ColorBackground = 0,
  ColorSides,
  ColorFace,
  ColorMax  // Range of enum
} Color;

void data_init();

void data_set_color(Color which, GColor new_color);

GColor data_get_color(Color which);
