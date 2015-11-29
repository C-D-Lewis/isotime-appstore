#include "comm.h"

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
#if defined(PBL_COLOR)
  Tuple *background_t = dict_find(iter, AppKeyColorBackground);
  if(background_t) {
    data_set_color(ColorBackground, (GColor){ .argb = background_t->value->int32 });
  }

  Tuple *sides_t = dict_find(iter, AppKeyColorSides);
  if(sides_t) {
    data_set_color(ColorSides, (GColor){ .argb = sides_t->value->int32 });
  }

  Tuple *face_t = dict_find(iter, AppKeyColorFace);
  if(face_t) {
    data_set_color(ColorFace, (GColor){ .argb = face_t->value->int32 });
  }
#endif

  // Other settings


  // Quit to be reloaded - PGE must be reinitialized to set the background color
  window_stack_pop_all(true);
}

void comm_init(int inbox, int outbox) {
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(inbox, outbox);
}
