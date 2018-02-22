#include "pebble.h"
#include "instructions.h"

static Window *window;
static ScrollLayer *scroll_layer;
static TextLayer *text_layer;
static InverterLayer *inverter_layer;
static char scroll_text[] = "-Media Player:          VLC - XBMC - ITUNES YOUTUBE have fast forward/rewind. You must click long select and the icon will change with the new function and long click select again to back to default.             -Power Point            you can move slide with up/down, select start the presentation and if you long click select you have the options to show a black/white screen.";

static const int vert_scroll_text_padding = 4;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  GRect max_text_bounds = GRect(0, 0, bounds.size.w, 2000);

  scroll_layer = scroll_layer_create(bounds);
  scroll_layer_set_click_config_onto_window(scroll_layer, window);
  text_layer = text_layer_create(max_text_bounds);
  text_layer_set_text(text_layer, scroll_text);
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  GSize max_size = text_layer_get_content_size(text_layer);
  text_layer_set_size(text_layer, max_size);
  scroll_layer_set_content_size(scroll_layer, GSize(bounds.size.w, max_size.h + vert_scroll_text_padding));
  scroll_layer_add_child(scroll_layer, text_layer_get_layer(text_layer));
  layer_add_child(window_layer, scroll_layer_get_layer(scroll_layer));
}

static void window_unload(Window *window) {
  inverter_layer_destroy(inverter_layer);
  text_layer_destroy(text_layer);
  scroll_layer_destroy(scroll_layer);
    
    window_destroy(window);
}
void instructions() {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true /* Animated */);
}