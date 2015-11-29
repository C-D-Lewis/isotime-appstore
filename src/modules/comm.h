#pragma once

#include <pebble.h>

#include "data.h"

typedef enum {
  AppKeyColorBackground = 0,
  AppKeyColorSides,
  AppKeyColorFace
} AppKey;

void comm_init(int inbox, int outbox);