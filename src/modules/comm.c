#include "comm.h"

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
#if defined(PBL_COLOR)
  Tuple *background_t = dict_find(iter, AppKeyColorBackground);
  if(background_t) {
    data_set_color(ColorBackground, GColorFromHEX(background_t->value->int32));
  }

  Tuple *sides_t = dict_find(iter, AppKeyColorSides);
  if(sides_t) {
    data_set_color(ColorSides, GColorFromHEX(sides_t->value->int32));
  }

  Tuple *face_t = dict_find(iter, AppKeyColorFace);
  if(face_t) {
    data_set_color(ColorFace, GColorFromHEX(face_t->value->int32));
  }
#endif

  // Other settings
  Tuple *anim_t = dict_find(iter, AppKeyAnimations);
  if(anim_t) {
    data_set_animations(anim_t->value->int8 == 1);
  }

  Tuple *bluetooth_t = dict_find(iter, AppKeyBluetooth);
  if(bluetooth_t) {
    data_set_bluetooth_alert(bluetooth_t->value->int8 == 1);
  }

  main_reload_config();
}

void comm_init(int inbox, int outbox) {
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(inbox, outbox);
}
