#pragma once

#include <pebble.h>

// #define DRAW_BG
// #define BENCHMARK

#define FRAME_RATE_HIGH PBL_IF_ROUND_ELSE(10, 30)

#define HOURS_OFFSET      40
#define MINS_OFFSET       25
#define PROJECTION_OFFSET PBL_IF_ROUND_ELSE(GPoint(120, 45), GPoint(100, 45))

#define FG_COL_YELLOW PBL_IF_COLOR_ELSE(GColorOrange, GColorBlack)
#define BG_COL_YELLOW PBL_IF_COLOR_ELSE(GColorYellow, GColorWhite)
#define FG_COL_RED    PBL_IF_COLOR_ELSE(GColorDarkCandyAppleRed, GColorBlack)
#define BG_COL_RED    PBL_IF_COLOR_ELSE(GColorOrange, GColorWhite)
#define FG_COL_BLUE   PBL_IF_COLOR_ELSE(GColorBlue, GColorBlack)
#define BG_COL_BLUE   PBL_IF_COLOR_ELSE(GColorPictonBlue, GColorWhite)
#define FG_COL_GREEN  PBL_IF_COLOR_ELSE(GColorDarkGreen, GColorBlack)
#define BG_COL_GREEN  PBL_IF_COLOR_ELSE(GColorGreen, GColorWhite)
#define FG_COL_GRAY   PBL_IF_COLOR_ELSE(GColorDarkGray, GColorBlack)
#define BG_COL_GRAY   PBL_IF_COLOR_ELSE(GColorLightGray, GColorWhite)
