#include "pebble.h"
#include "pc.h"
#include "Volume.h"
#include "pc_window.h"
#include "Vlc.h"

#define NUM_CLIENT_MENU_ITEMS 5
#define NUM_MENU_SECTIONS 1

static Window *window;
static SimpleMenuLayer *simple_menu_layer;
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem bus_menu_items[NUM_CLIENT_MENU_ITEMS];

static void bus1_select_callback(int index, void *ctx) {
    show_menu_pc();
}
static void bus2_select_callback(int index, void *ctx) {
   show_menu_volume();
}
static void bus3_select_callback(int index, void *ctx) {
    int a = 7;
    show_vlc_menu(a);
}
static void bus5_select_callback(int index, void *ctx) {
    int a = 14;
    show_vlc_menu(a);
}
static void bus4_select_callback(int index, void *ctx) {
    show_pc_window();
}

static void window_load(Window *window) {

  int num_a_items = 0;

  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Power",
        .subtitle = "On/Off",
    .callback = bus1_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Volume",
        .subtitle = "Up/Down/Mute",
    .callback = bus2_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Power Point",
        .subtitle = "Start/End/Next/Previous",
    .callback = bus3_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Generic Slide Show",
        .subtitle = "Start/Next/Previous",
    .callback = bus5_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Window",
        .subtitle = "Explorer/Run/Minimize",
    .callback = bus4_select_callback,
  };
   
  menu_sections[0] = (SimpleMenuSection){
  .title ="Category",
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

void show_pc_menu () {
    
  window = window_create();

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true /* Animated */);
}