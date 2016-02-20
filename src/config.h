#pragma once

#include <pebble.h>

// #define DRAW_BG
// #define BENCHMARK

#define FRAME_RATE_HIGH PBL_IF_ROUND_ELSE(10, 30)

#define HOURS_OFFSET      40
#define MINS_OFFSET       25
#define PROJECTION_OFFSET PBL_IF_ROUND_ELSE(GPoint(120, 45), GPoint(100, 45))
