#pragma once

#include <pebble.h>

typedef enum {
  ColorBackground = 0,
  ColorSides,
  ColorFace,
  ColorMax  // Range of enum
} Color;

typedef enum {
  PreferenceAnimations = 10
} Preference;

void data_init();

void data_set_color(Color which, GColor new_color);

GColor data_get_color(Color which);

void data_set_animations(bool value);
bool data_get_animations();
