#include "pebble.h"
#include "Vlc.h"
#include "common.h"
#include "appMessage.h"
#include "sendData.h"

    
static Window *window;
static ActionBarLayer *action_bar;

static GBitmap *action_icon_previous;
static GBitmap *action_icon_next;
static GBitmap *action_icon_playpause;

static GBitmap *action_icon_forward;
static GBitmap *action_icon_rewind;

static GBitmap *action_icon_up ;
static GBitmap *action_icon_down ;
static GBitmap *action_icon_start;

static GBitmap *action_icon_black ;
static GBitmap *action_icon_white;

static bool controlling_keypad;

static void display_action_bar_icons();

static BitmapLayer *logo_layer;

static GBitmap *logo_img_vlc;
static GBitmap *logo_img_xbmc;
static GBitmap *logo_img_itunes;
static GBitmap *logo_img_spotify;
static GBitmap *logo_img_youtube;
static GBitmap *logo_img_netflix;
static GBitmap *logo_img_ppt;

static GBitmap *logo_img_pandora;
static GBitmap *logo_img_foobar;
static GBitmap *logo_img_monkey;
static GBitmap *logo_img_winamp;
static GBitmap *logo_img_windows;
static GBitmap *logo_img_media;
static GBitmap *logo_img_slide;

static GBitmap *action_icon_tup ;
static GBitmap *action_icon_tdown ;

static int player = 0;

uint16_t op1;
uint16_t op2;
uint16_t op3;
uint16_t op4;
uint16_t op5;
uint16_t op6;


static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
     send_message1(controlling_keypad ? op1 : op2 );
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    send_message1(controlling_keypad ? op3 : op4 );
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    send_message1(controlling_keypad ? op5 : op6);
}

static void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
    if(player != 6 && player !=4 && player !=14 && player !=9 && player !=10 && player !=11 && player !=12 && player !=13){
        controlling_keypad = !controlling_keypad;
    }
    display_action_bar_icons();
}
static void select_long_click_handler_down(ClickRecognizerRef recognizer, void *context) {
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "stop clicked. !!!!!  downnnn down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  //window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler_down, select_long_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler,NULL);
}

static void display_action_bar_icons() {
    
	action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, controlling_keypad ? action_icon_previous : action_icon_rewind);
	action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, controlling_keypad ? action_icon_next : action_icon_forward);
	action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, controlling_keypad ? action_icon_playpause : action_icon_playpause);
    
    if(player == 7){
        action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, controlling_keypad ?  action_icon_up  : action_icon_black);
    	action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, controlling_keypad ? action_icon_down  : action_icon_white);
    	action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, controlling_keypad ? action_icon_start  : action_icon_start);         
    }
    if(player == 14){
        action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, controlling_keypad ?  action_icon_up  : action_icon_up );
    	action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, controlling_keypad ? action_icon_down  : action_icon_down );
    	action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, controlling_keypad ? action_icon_start  : action_icon_start);     
    }
    if(player == 8){
        action_bar_layer_set_icon(action_bar, BUTTON_ID_UP, controlling_keypad ?  action_icon_tup  : action_icon_tup );
    	action_bar_layer_set_icon(action_bar, BUTTON_ID_DOWN, controlling_keypad ? action_icon_tdown  : action_icon_tdown);
    	action_bar_layer_set_icon(action_bar, BUTTON_ID_SELECT, controlling_keypad ? action_icon_playpause  : action_icon_playpause);         
    }
    
    if (player == 1){ 
    bitmap_layer_set_bitmap(logo_layer,logo_img_vlc);
        
        op1 = VLC_PREVIOUS;
        op2 = VLC_L10;
        op3 = VLC_NEXT ;
        op4 = VLC_M10;
        op5 = VLC_PLAY;
        op6 = VLC_PLAY ;
    }
    else if (player == 2){
        bitmap_layer_set_bitmap(logo_layer,logo_img_xbmc);
        
        
        op1 = XBMC_PREVIOUS;
        op2 = XBMC_L10;
        op3 = XBMC_NEXT; 
        op4 = XBMC_M10;
        op5 = XBMC_PLAY;
        op6 = XBMC_PLAY ;
    }else if (player == 3){
        bitmap_layer_set_bitmap(logo_layer,logo_img_itunes);
        
        
        op1 = ITUNES_PREVIOUS;
        op2 = ITUNES_L10;
        op3 = ITUNES_NEXT; 
        op4 = ITUNES_M10;
        op5 = ITUNES_PLAY;
        op6 = ITUNES_PLAY ;
    }else if (player == 4){
    bitmap_layer_set_bitmap(logo_layer,logo_img_spotify);
        
        op1 = SPOTIFY_PREVIOUS;
        op2 = SELECT_KEY;
        op3 = SPOTIFY_NEXT ;
        op4 = SELECT_KEY;
        op5 = SPOTIFY_PLAY;
        op6 = SPOTIFY_PLAY ;
    }
    
    if (player == 5){
        
        bitmap_layer_set_bitmap(logo_layer,logo_img_youtube);
        
        op1 = YOUTUBE_PREVIOUS;
        op2 = YOUTUBE_L10;
        op3 = YOUTUBE_NEXT ;
        op4 = YOUTUBE_M10;
        op5 = YOUTUBE_PLAY;
        op6 = YOUTUBE_PLAY ;
    }else if (player == 6){
        bitmap_layer_set_bitmap(logo_layer,logo_img_netflix);
        
        //fcontrolling_keypad = true;
        
        op1 = NETFLIX_PREVIOUS;
        op2 = SELECT_KEY;
        op3 = NETFLIX_NEXT ;
        op4 = SELECT_KEY;
        op5 = NETFLIX_PLAY;
        op6 = NETFLIX_PLAY ;
        
    }else if (player == 7){
        bitmap_layer_set_bitmap(logo_layer,logo_img_ppt);
        
        //fcontrolling_keypad = true;
        
        
        op1 = PPOINT_PREVOUS;
        op2 = PPOINT_BLACK;
        op3 = PPOINT_NEXT ;
        op4 = PPOINT_WHITE;
        op5 = PPOINT_START;
        op6 = PPOINT_START;
    
    }else if (player == 8){
        bitmap_layer_set_bitmap(logo_layer,logo_img_pandora);
        
        //fcontrolling_keypad = true;
        
        op1 = PANDORA_UP;
        op2 = SELECT_KEY;
        op3 = PANDORA_DOWN;
        op4 = SELECT_KEY;
        op5 = PANDORA_PLAY;
        op6 = PANDORA_PLAY;
    
    }else if (player == 9){
        bitmap_layer_set_bitmap(logo_layer,logo_img_foobar);
        
        //fcontrolling_keypad = true;
        
        op1 = FOOBAR_PREVIOUS; 
        op2 = SELECT_KEY;
        op3 = FOOBAR_NEXT;
        op4 = SELECT_KEY;
        op5 = FOOBAR_PLAY;
        op6 = FOOBAR_PLAY;
    
    }else if (player == 10){
        bitmap_layer_set_bitmap(logo_layer,logo_img_monkey);
        
        //fcontrolling_keypad = true;
        
        op1 = MONKEY_PREVIOUS;
        op2 = SELECT_KEY;
        op3 = MONKEY_NEXT;
        op4 = SELECT_KEY;
        op5 = MONKEY_PLAY;
        op6 = MONKEY_PLAY;
    
    }else if (player == 11){
        bitmap_layer_set_bitmap(logo_layer,logo_img_windows);
        
        //fcontrolling_keypad = true;
        
        op1 = WMPLAYER_PREVIOUS;
        op2 = SELECT_KEY;
        op3 = WMPLAYER_NEXT ;
        op4 = SELECT_KEY;
        op5 = WMPLAYER_PLAY;
        op6 = WMPLAYER_PLAY;
    
    }else if (player == 12){
        bitmap_layer_set_bitmap(logo_layer,logo_img_media);
        
        //fcontrolling_keypad = true;
        
        op1 = GMEDIA_PREVIOUS;
        op2 = SELECT_KEY;
        op3 = GMEDIA_NEXT ;
        op4 = SELECT_KEY;
        op5 = GMEDIA_PLAY;
        op6 = GMEDIA_PLAY;
    
    }else if (player == 13){
        bitmap_layer_set_bitmap(logo_layer,logo_img_winamp);
        
        //fcontrolling_keypad = true;
        
        op1 = WINAP_PREVIOUS;
        op2 = SELECT_KEY;
        op3 = WINAP_NEXT ;
        op4 = SELECT_KEY;
        op5 = WINAP_PLAY;
        op6 = WINAP_PLAY;
    
    }else if (player == 14){
        bitmap_layer_set_bitmap(logo_layer,logo_img_slide);
        
        //fcontrolling_keypad = true;
        
        op1 = GSLIDE_PREVIOUS;
        op2 = SELECT_KEY;
        op3 = GSLIDE_NEXT ;
        op4 = SELECT_KEY;
        op5 = GSLIDE_START;
        op6 = GSLIDE_START;
    }
}
static void window_load(Window *window) {
	
	//LAYER TEXT
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);

  	logo_layer = bitmap_layer_create(GRect(20,43,100,60));
  	
  	layer_add_child(window_layer, bitmap_layer_get_layer(logo_layer));
    
  	// Action Bar
  	action_bar = action_bar_layer_create();
  	action_bar_layer_add_to_window(action_bar, window);
  	action_bar_layer_set_click_config_provider(action_bar, click_config_provider);

    display_action_bar_icons();
}

static void window_unload(Window *window) {

  	action_bar_layer_destroy(action_bar);
    gbitmap_destroy(action_icon_previous);
    gbitmap_destroy(action_icon_next);
    gbitmap_destroy(action_icon_playpause);
    gbitmap_destroy(action_icon_forward);
	gbitmap_destroy(action_icon_rewind);
    
    gbitmap_destroy(action_icon_up );
    gbitmap_destroy(action_icon_down );
    gbitmap_destroy(action_icon_start);
    
    gbitmap_destroy(action_icon_black );
    gbitmap_destroy(action_icon_white );
    
    bitmap_layer_destroy(logo_layer);
  	gbitmap_destroy(logo_img_vlc);
	gbitmap_destroy(logo_img_spotify);
    
    gbitmap_destroy(logo_img_xbmc);
    gbitmap_destroy(logo_img_itunes);
    gbitmap_destroy(logo_img_ppt);
    
    gbitmap_destroy(logo_img_youtube);
    gbitmap_destroy(logo_img_netflix);
    
    gbitmap_destroy(logo_img_pandora);
    gbitmap_destroy(logo_img_foobar);
    gbitmap_destroy(logo_img_monkey);
    gbitmap_destroy(logo_img_winamp);
    gbitmap_destroy(logo_img_windows);
    gbitmap_destroy(logo_img_media);
    gbitmap_destroy(logo_img_slide);
    gbitmap_destroy(action_icon_tup);
    gbitmap_destroy(action_icon_tdown);
  	window_destroy(window);
}

static void init(void) {
  
  controlling_keypad = true;
        
  action_icon_previous = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_UP);
  action_icon_next = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DOWN);
  action_icon_playpause = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PLAY);
    
  action_icon_forward = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_DOWN_FAST);
  action_icon_rewind = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_UP_FAST);
    
  action_icon_up = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_P_UP);
  action_icon_down = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_P_DOWN);
  action_icon_start = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_P_START);
    
  action_icon_black= gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BLACK);
  action_icon_white = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_WHITE);
    
  logo_img_vlc = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LOGO_VLC);
  logo_img_spotify = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LOGO_SPOTIFY);
    
  logo_img_xbmc = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LOGO_XBMC);
  logo_img_itunes = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LOGO_ITUNES);
    
  logo_img_youtube = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LOGO_YOUTUBE);
  logo_img_netflix = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LOGO_NETFLIX); 
    
  logo_img_ppt = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LOGO_PPT); 
    
    logo_img_pandora = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PANDORA); 
    
    logo_img_foobar = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_FOOBAR);
    logo_img_monkey = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MONKEY);
    logo_img_winamp = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_WINAMP);
    logo_img_windows = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_WINDOWS);
    logo_img_media = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MEDIA);
    logo_img_slide = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SLIDE);
    
    action_icon_tup = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TUP);
    action_icon_tdown = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TDOWN);
    
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
 
}

static void deinit(void) {

}

void show_vlc_menu(int a) {
    
  player = a;
  APP_LOG(APP_LOG_LEVEL_DEBUG, "PPLayer %i",player);
    
  init();

  deinit();
	
  window_stack_push(window, true);
}