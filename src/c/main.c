#include "pebble.h"
#include "menu_principal.h"
#include "common.h"
#include "appMessage.h"
#include "sendData.h"
    
bool menuStarted = false;
static Window *window;
static GBitmap *splashImage;
static BitmapLayer *splashLayer;
static TextLayer *loading_layer;

char bt[30];
bool btu;

Information config;
Information1 config1;

void splash_deinit () {
    
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "destruye splash");
	window_stack_remove(window, true);
	gbitmap_destroy(splashImage);
	bitmap_layer_destroy(splashLayer);
	text_layer_destroy(loading_layer);  
}

void splash_timer_callback () {
    
	splash_deinit();
	menuStarted = true;
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "envia timer callback termino");
	init_principal();
}

void config_init() {

	btu=true;
	if (bluetooth_connection_service_peek()) {
        //APP_LOG(APP_LOG_LEVEL_INFO, "Phone is connected!");
	      strcpy(bt,"Loading" );
          send_message1(DATA_KEY);
          config.save=false;
        
    if (persist_exists(SETTINGS_KEY)){
        
            int valueRead = persist_read_data(SETTINGS_KEY , &config, sizeof(Information) );
            APP_LOG(APP_LOG_LEVEL_WARNING, "Read %d bytes from settings", valueRead);
        }
        
        if (persist_exists(SETTINGS_KEY1)){
            
            int valueRead = persist_read_data(SETTINGS_KEY1 , &config1, sizeof(Information1) );
            APP_LOG(APP_LOG_LEVEL_WARNING, "Read %d bytes from settings1", valueRead);
        }
         
        config.save=false;
        config1.save1=false;
        
    }
    else {
        //APP_LOG(APP_LOG_LEVEL_INFO, "Phone is not connected!");
		strcpy(bt,"Phone not connected!");
	    btu = false;
    }
	
}
void init_splash () {
	
	window = window_create();
	window_set_fullscreen(window, true);
   
	Layer * windowLayer = window_get_root_layer(window);
	splashImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LOGO_UNIFIED);
	GRect bounds = layer_get_frame(windowLayer);
	splashLayer = bitmap_layer_create(bounds);
	
	bitmap_layer_set_bitmap(splashLayer, splashImage);
	bitmap_layer_set_alignment(splashLayer, GAlignCenter);
	bitmap_layer_set_background_color(splashLayer, GColorClear);
	layer_add_child(windowLayer, bitmap_layer_get_layer(splashLayer));
	
	loading_layer = text_layer_create(
      (GRect) { .origin = { 0, 135 }, .size = { bounds.size.w, 25 } });
  	text_layer_set_text(loading_layer, bt);
  	text_layer_set_text_alignment(loading_layer, GTextAlignmentCenter);
  	text_layer_set_font(loading_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
	
  	layer_add_child(windowLayer, text_layer_get_layer(loading_layer));
	
	const bool animated = true;
	window_stack_push(window, animated);
	
}
int main(void) {
    
	appmessage_init();
	config_init();
    init_splash ();
	app_event_loop();
    if (menuStarted) { deinit_principal();  }
    else splash_deinit();
    window_destroy(window);
	return 0;	
}
