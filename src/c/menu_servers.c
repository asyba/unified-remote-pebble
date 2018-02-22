#include "pebble.h"
#include "menu_servers.h"
#include "common.h"
#include "sendData.h"
#include "appMessage.h"
    
#define NUM_MENU_ITEMS 3
#define	NUM_MENU_SECTIONS 1

static Window *window;
static MenuLayer *menu_layer; 

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer1, void *data) {
  return NUM_MENU_SECTIONS;
}
static int16_t main_get_cell_height(struct MenuLayer *menu_layer1, MenuIndex *cell_index, void *callback_context)   
{ // Always 20px tall for a normal cell
	return 42;
}
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer1, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      return  NUM_MENU_ITEMS;
    default:
      return 0;
  }
}

static int16_t menu_get_header_height_callback(MenuLayer *menu_layer1, uint16_t section_index, void *data) {
  return 18;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    
  switch (section_index) {
    case 0:
      menu_cell_basic_header_draw(ctx, cell_layer,"Server");
      break;
  }
  
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
switch (cell_index->section) {
	  
    case 0:
    
      switch (cell_index->row) {
		  
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "Server 1" , config.s1, NULL);
          break;

        case 1:    
          menu_cell_basic_draw(ctx, cell_layer, "Server 2",  config.s2, NULL );
          break;
          
        case 2:
          menu_cell_basic_draw(ctx, cell_layer, "Server 3",  config.s3 , NULL);
          break;
      }
      break;   
    break;
      
  }
}

static void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
    
    switch (cell_index->section) {
        
        case 0:
        
              switch (cell_index->row) {
	  
	            case 0:
                    APP_LOG(APP_LOG_LEVEL_DEBUG, "s1");
                    send_message1(SERVER1_KEY);
                    strcpy(config1.s0,config.s1);
                    config1.save1=true;
      
	  	        break;
	 
                case 1:
                    APP_LOG(APP_LOG_LEVEL_DEBUG, "s2");
                    send_message1(SERVER2_KEY);
                    strcpy(config1.s0,config.s2);
                    config1.save1=true;
                break;
	  
	            case 2:
                     APP_LOG(APP_LOG_LEVEL_DEBUG, "s3");
                     send_message1(SERVER3_KEY);
                     strcpy(config1.s0,config.s3);
                     config1.save1=true;
	            break;
                          
               }
               break;   
  }
}

static void window_unload(Window *window) {
    menu_layer_destroy(menu_layer);
  	window_destroy(window);
}

static void window_load(Window *window) {

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  menu_layer = menu_layer_create(bounds);

  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_cell_height = main_get_cell_height,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });
    
  menu_layer_set_click_config_onto_window(menu_layer, window);

  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
}

void show_menu_servers(){
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,

    .unload = window_unload,
  });
         
  window_stack_push(window, true /* Animated */);
}