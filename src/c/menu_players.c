#include "pebble.h"
#include "menu_players.h"
#include "Vlc.h"

#define NUM_CLIENT_MENU_ITEMS 11
#define NUM_MENU_SECTIONS 1

static Window *window;
static SimpleMenuLayer *simple_menu_layer;
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem bus_menu_items[NUM_CLIENT_MENU_ITEMS];

static void bus1_select_callback(int index, void *ctx) {
    int a = 1;
    show_vlc_menu(a);
}
static void bus2_select_callback(int index, void *ctx) {
    int a = 2;
    show_vlc_menu(a);
}
static void bus3_select_callback(int index, void *ctx) {
    int a = 3;
    show_vlc_menu(a);
}
static void bus4_select_callback(int index, void *ctx) {
     int a = 4;
    show_vlc_menu(a);
}
static void bus5_select_callback(int index, void *ctx) {
     int a = 8;
    show_vlc_menu(a);
}
static void bus6_select_callback(int index, void *ctx) {
     int a = 9;
    show_vlc_menu(a);
}
static void bus7_select_callback(int index, void *ctx) {
     int a = 10;
    show_vlc_menu(a);
}
static void bus8_select_callback(int index, void *ctx) {
     int a = 11;
    show_vlc_menu(a);
}
static void bus9_select_callback(int index, void *ctx) {
     int a = 12;
    show_vlc_menu(a);
}
static void bus10_select_callback(int index, void *ctx) {
     int a = 13;
    show_vlc_menu(a);
}

static void window_load(Window *window) {

  int num_a_items = 0;

    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "VLC",
        //.subtitle = "Media Player",
        .callback = bus1_select_callback,
    };
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "XBMC",
        //.subtitle = "Media Player",
        .callback = bus2_select_callback,
    };
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "iTunes",
        //.subtitle = "Home/Refresh/Back/etc",
        .callback = bus3_select_callback,
    };
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "Spotify",
        //.subtitle = "Home/Refresh/Back/etc",
        .callback = bus4_select_callback,
    };
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "Pandora",
        //.subtitle = "Home/Refresh/Back/etc",
        .callback = bus5_select_callback,
    };
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "FOOBAR2000",
        //.subtitle = "Home/Refresh/Back/etc",
        .callback = bus6_select_callback,
    };
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "MediaMonkey",
        //.subtitle = "Home/Refresh/Back/etc",
        .callback = bus7_select_callback,
    };
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "WindowsMediaPlayer",
        //.subtitle = "Home/Refresh/Back/etc",
        .callback = bus8_select_callback,
    };
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "GeneralMedia",
        //.subtitle = "Home/Refresh/Back/etc",
        .callback = bus9_select_callback,
    };
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "Winamp",
        //.subtitle = "Home/Refresh/Back/etc",
        .callback = bus10_select_callback,
    };
  
    
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
        .title = "More Soon ...",
        //.subtitle = "",
        //.callback = bus4_select_callback,
    };
   
  menu_sections[0] = (SimpleMenuSection){
  .title ="Players",
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

void show_menu_players () {
    
  window = window_create();

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true /* Animated */);
}