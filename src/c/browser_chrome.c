#include "pebble.h"
#include "browser_chrome.h"
#include "appMessage.h"
#include "common.h"
#include "sendData.h"

#define NUM_MENU_ITEMS 8
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
      menu_cell_basic_header_draw(ctx, cell_layer,"Window");
      break;
  }
  
}

static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
switch (cell_index->section) {
	  
    case 0:
    
      switch (cell_index->row) {
		  
        case 0:
          menu_cell_basic_draw(ctx, cell_layer, "Home" , NULL , NULL);
          break;
          
        case 1:    
          menu_cell_basic_draw(ctx, cell_layer, "Refresh",  NULL , NULL );
          break;
          
        case 2:    
          menu_cell_basic_draw(ctx, cell_layer, "Back Page",  NULL , NULL );
          break;
          
        case 3:
          menu_cell_basic_draw(ctx, cell_layer, "Next Page",  NULL , NULL);
          break;
          
        case 4:
          menu_cell_basic_draw(ctx, cell_layer, "Back Tab",  NULL , NULL);
          break;
          
        case 5:
          menu_cell_basic_draw(ctx, cell_layer, "Next Tab",  NULL , NULL);
          break;
          
        case 6:
          menu_cell_basic_draw(ctx, cell_layer, "Scroll Up",  NULL , NULL);
          break;
          
        case 7:
          menu_cell_basic_draw(ctx, cell_layer, "Scroll Down",  NULL , NULL);
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
                    send_message1(CHROME_HOME);
	  	        break;
	 
                case 1:
                    send_message1(CHROME_REFRESH);
                break;
	  
	            case 2:
                     send_message1(CHROME_BACK_P);
	            break;
                
                 case 3:
                     send_message1(CHROME_NEXT_P);
	            break;
                   case 4:
                     send_message1(CHROME_BACK_T);
	            break;
                  
                   case 5:
                     send_message1(CHROME_NEXT_T);
	            break;
                  
                   case 6:
                     send_message1(CHROME_UP);
	            break;
                  
                   case 7:
                     send_message1(CHROME_DOWN);
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

void show_browser_chrome(){
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,

    .unload = window_unload,
  });
         
  window_stack_push(window, true /* Animated */);
}