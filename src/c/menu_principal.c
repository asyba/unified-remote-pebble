#include "pebble.h"
#include "appMessage.h"
#include "sendData.h"
#include "Menu_pc.h"
#include "menu_browser.h"
#include "Monitor.h"
#include "menu_players.h"
#include "instructions.h"
#include "menu_servers.h"
#include "common.h"

#define NUM_CLIENT_MENU_ITEMS 4
#define NUM_MENU_SECTIONS 2
#define NUM_CLIENT_MENU_ITEMS_2 3
    
static Window *window;

static SimpleMenuLayer *simple_menu_layer;
static SimpleMenuSection menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem bus_menu_items[NUM_CLIENT_MENU_ITEMS];
static SimpleMenuItem bus_menu_items1[NUM_CLIENT_MENU_ITEMS_2];
static void display_action_bar_icons();

static void bus1_select_callback(int index, void *ctx) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "t1");
    show_menu_players();
}
static void bus2_select_callback(int index, void *ctx) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "t2");
    show_pc_menu ();
}
static void bus3_select_callback(int index, void *ctx) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "t3");
    show_menu_monitor();
}
static void bus4_select_callback(int index, void *ctx) {
    show_browser_menu ();
}
static void bus5_select_callback(int index, void *ctx) {
    instructions();
}
static void bus6_select_callback(int index, void *ctx) {
    show_menu_servers();
}

static void window_load(Window *window) {

    int num_a_items = 0;
    int num_a_items1 = 0;

  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Aplications",
        .subtitle = "VLC/Itunes/Spotify/More",
    .callback = bus1_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "PC",
        .subtitle = "Power/Volume/PPT",
    .callback = bus2_select_callback,
  };
  bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Monitor",
        .subtitle = "On/Off",
    .callback = bus3_select_callback,
  };
    bus_menu_items[num_a_items++] = (SimpleMenuItem){
    .title = "Browser",
        .subtitle = "YouTube/Netflix/Chrome/etc",
    .callback = bus4_select_callback,
  };
    
   bus_menu_items1[num_a_items1++] = (SimpleMenuItem){
     .title = "Instructions",
     .callback = bus5_select_callback,
  };
  bus_menu_items1[num_a_items1++] = (SimpleMenuItem){
     .title = "Servers",
      .subtitle = config1.s0,
     .callback = bus6_select_callback,
  };
   bus_menu_items1[num_a_items1++] = (SimpleMenuItem){
    .title = "Version",
        .subtitle = "1.3",
  };
 
  menu_sections[0] = (SimpleMenuSection){
  .title ="Control Category",
  .num_items = NUM_CLIENT_MENU_ITEMS,
  .items = bus_menu_items,
  };
    
   menu_sections[1] = (SimpleMenuSection){
  .title ="Options",
  .num_items = NUM_CLIENT_MENU_ITEMS_2,
  .items = bus_menu_items1,
  };
      
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  simple_menu_layer = simple_menu_layer_create(bounds, window, menu_sections,NUM_MENU_SECTIONS, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(simple_menu_layer));
}
static void window_unload(Window *window) {
  simple_menu_layer_destroy(simple_menu_layer);
}

void init_principal (void) {
    
    window = window_create();
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    window_stack_push(window, true /* Animated */);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);    
}
void deinit_principal (void) {
    
    if (config.save) {
        int valueWritten = persist_write_data(SETTINGS_KEY, &config, sizeof(Information));
        APP_LOG(APP_LOG_LEVEL_WARNING, "Wrote %d bytes to settings.", valueWritten);  
	}
    if(config1.save1){
        int valueWritten = persist_write_data(SETTINGS_KEY1, &config1, sizeof(Information1));
        APP_LOG(APP_LOG_LEVEL_WARNING, "Wrote %d bytes to settings1.", valueWritten);  
    //persist_write_string(S0, config.s0);
    }
    window_destroy(window);
}
