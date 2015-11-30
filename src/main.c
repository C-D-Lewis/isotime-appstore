#include <pebble.h>

#include "config.h"

#include "modules/data.h"
#include "modules/comm.h"

#include "pge/pge.h"
#include "pge/modules/pge_isometric.h"

#include "drawable/segment.h"
#include "drawable/digit.h"

static Digit *s_digits[4];

static bool s_initd;

static bool digits_are_animating() {
  for(int i = 0; i < 4; i++) {
    if(digit_is_animating(s_digits[i])) {
      return true;
    }
  }
  return false;
}

static void pge_logic() {
  for(int i = 0; i < 4; i++) {
    digit_logic(s_digits[i]);
  }
}

static void pge_render(GContext *ctx) {
#ifdef BENCHMARK
  uint16_t start = time_ms(NULL, NULL);
#endif

  pge_isometric_begin(ctx);
  for(int i = 0; i < 4; i++) {
    digit_render(s_digits[i]);
  }
  pge_isometric_finish(ctx);

  if(!digits_are_animating()) {
    pge_pause();
    if(!s_initd) {
      // Any further interruptions will cause fast-forwarding
      s_initd = true;
    }
  }

#ifdef BENCHMARK
  uint16_t finish = time_ms(NULL, NULL);
  APP_LOG(APP_LOG_LEVEL_INFO, "Frame time: %d", (int)finish - start);
#endif
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  int hours = tick_time->tm_hour;
  int mins = tick_time->tm_min;

  if(hours < 10) {
    digit_set_value(s_digits[0], 0);
  } else {
    digit_set_value(s_digits[0], hours / 10);
  }
  digit_set_value(s_digits[1], hours % 10);

  if(mins < 10) {
    digit_set_value(s_digits[2], 0);
  } else {
    digit_set_value(s_digits[2], mins / 10);
  }
  digit_set_value(s_digits[3], mins % 10);

  for(int i = 0; i < 4; i++) {
    digit_set_colors(s_digits[i], data_get_color(ColorSides), data_get_color(ColorFace));
  }

  // Smooth transition
  if(data_get_animations()) {
    pge_resume();
  } else {
    // Instant transition
    while(digits_are_animating()) {
      pge_logic();
    }
    pge_manual_advance();
  }
}

static void fix_handler(void *context) {
  // Render new state
  pge_manual_advance();
}

static void focus_handler(bool now_in_focus) {
  if(now_in_focus && s_initd) {
    // Prevent bad rendering after notifications
    while(digits_are_animating()) {
      pge_logic();
    }

    app_timer_register(500, fix_handler, NULL);
  }
}

void pge_init() {
  s_initd = false;

  data_init();
  comm_init(64, 64);

  s_digits[0] = digit_create(GPoint(-HOURS_OFFSET, 0), 0);
  s_digits[1] = digit_create(GPoint(-HOURS_OFFSET + (5 * SEGMENT_SIZE.w), 0), 0);
  s_digits[2] = digit_create(GPoint(MINS_OFFSET, 7 * SEGMENT_SIZE.h), 0);
  s_digits[3] = digit_create(GPoint(MINS_OFFSET + (5 * SEGMENT_SIZE.w), 7 * SEGMENT_SIZE.h), 0);

  pge_isometric_set_projection_offset(PROJECTION_OFFSET);
  pge_set_framerate(FRAME_RATE_HIGH);
  pge_begin(data_get_color(ColorBackground), pge_logic, pge_render, NULL);

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  time_t temp = time(NULL);
  struct tm *t = localtime(&temp);
  tick_handler(t, MINUTE_UNIT);

  // Fast forward - save power when lots of notifications
  while(digits_are_animating()) {
    pge_logic();
  }

  if(!data_get_animations()) {
    pge_manual_advance();

    // Don't animate after this
    pge_pause();
  }

  app_focus_service_subscribe(focus_handler);
}

void pge_deinit() {
  pge_finish();

  for(int i = 0; i < 4; i++) {
    digit_destroy(s_digits[i]);
  }
}
