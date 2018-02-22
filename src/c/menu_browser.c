#include "pebble.h"
#include "browser_chrome.h"
#include "Vlc.h"

#define NUM_CLIENT_MENU_ITEMS 4
#define NUM_MENU_SECTIONS 1

static Window *window;

static SimpleMenuLayer *simple_menu_layer;

static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];

static SimpleMenuItem bus_menu_items[NUM_CLIENT_MENU_ITEMS];

static void bus1_select_callback(int index, void *ctx) {
     int a = 5;
    show_vlc_menu(a);
}
static void bus2_select_callback(int index, void *ctx) {
     int a = 6;
    show_vlc_menu(a);
}
static void bus3_select_callback(int index, void *ctx) {
    show_browser_chrome();
}


static void window_load(Window *window) {

  int num_a_items = 0;

  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "YouTube",
        .subtitle = "Media Player",
    .callback = bus1_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Netflix",
        .subtitle = "Media Player",
    .callback = bus2_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Chrome/Firefox",
        .subtitle = "Home/Refresh/Back/etc",
    .callback = bus3_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "More Soon ...",
  };
   
  menu_sections[0] = (SimpleMenuSection){
  .title ="Browser",
  .num_items = NUM_CLIENT_MENU_ITEMS,
  .items = bus_menu_items,
  };
      
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  simple_menu_layer = simple_menu_layer_create(bounds, window, menu_sections,NUM_MENU_SECTIONS, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(simple_menu_layer));
}
static void window_unload(Window *window) {
   simple_menu_layer_destroy(simple_menu_layer);
   window_destroy(window);
}

void show_browser_menu () {
    
  window = window_create();

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true /* Animated */);

}