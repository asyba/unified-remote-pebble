#include "pebble.h"
#include "Volume.h"
#include "appMessage.h"
#include "common.h"
#include "sendData.h"

#define NUM_MENU_ITEMS 3
#define	NUM_MENU_SECTIONS 1

static Window *window;
static MenuLayer *menu_layer; 

static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer1, void *data) {
  return NUM_MENU_SECTIONS;
}
static int16_t main_get_cell_height(struct MenuLayer *menu_layer1, MenuIndex *cell_index, void *callback_context)   
{ // Always 20px tall for a normal cell
	return 30;
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
  return 1;
}

static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    
  switch (section_index) {
    case 0:
      menu_cell_basic_header_draw(ctx, cell_layer,"Volume");
      break;
  }
}
static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
switch (cell_index->section) {
	  
    case 0:
    
      switch (cell_index->row) {
		  
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "UP" , NULL , NULL);
          break;

        case 1:    
          menu_cell_basic_draw(ctx, cell_layer, "DOWN",  NULL , NULL );
          break;
          
        case 2:
          menu_cell_basic_draw(ctx, cell_layer, "MUTE",  NULL , NULL);
          break;
      }
      break;   
    break;

  }
}

void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
    
    switch (cell_index->section) {
        
        case 0:
        
              switch (cell_index->row) {
	  
	            case 0:
                    //APP_LOG(APP_LOG_LEVEL_DEBUG, "v up clicked.");
                    send_message1(VOLUME_UP);
	  	        break;
	 
                case 1:
                    //APP_LOG(APP_LOG_LEVEL_DEBUG, "v down clicked.");
                    send_message1(VOLUME_DOWN);
                break;
	  
	            case 2:
                     //APP_LOG(APP_LOG_LEVEL_DEBUG, "v mute clicked.");
                     send_message1(VOLUME_MUTE);
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

void show_menu_volume(){
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,

    .unload = window_unload,
  });
         
  window_stack_push(window, true /* Animated */);
}