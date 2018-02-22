#include "pebble.h"
#include "appMessage.h"
#include "common.h"

static void in_received_handler(DictionaryIterator *iter, void *context);
static void in_dropped_handler(AppMessageResult reason, void *context);
static void out_sent_handler(DictionaryIterator *sent, void *context);
static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context);
void appmessage_init(void) {
    
    app_message_register_inbox_received(in_received_handler);
    app_message_register_inbox_dropped(in_dropped_handler);
    app_message_register_outbox_sent(out_sent_handler);
    app_message_register_outbox_failed(out_failed_handler);
    app_comm_set_sniff_interval(SNIFF_INTERVAL_REDUCED);
    app_message_open(124 /* inbound_size */, 124/* outbound_size */);
}

// Vibe pattern: ON for 200ms, OFF for 100ms, ON for 400ms:
static const uint32_t const segments[] = { 50};
VibePattern pat = {
  .durations = segments,
  .num_segments = ARRAY_LENGTH(segments),
};

static void in_received_handler(DictionaryIterator *received, void *context) {
    
    Tuple *s0 = dict_find(received, DATA_KEY);
    Tuple *s1 = dict_find(received, SERVER1_KEY);
    Tuple *s2 = dict_find(received, SERVER2_KEY);
    Tuple *s3 = dict_find(received, SERVER3_KEY);
    
    if (s0) {
	  
	    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Text instalado: %s", s0->value->cstring);
	    //APP_LOG(APP_LOG_LEVEL_DEBUG, "ser.");
        //app_timer_cancel (timer);
        //timer = NULL;
        splash_timer_callback();
	}
     if (s1) {
	  
	    APP_LOG(APP_LOG_LEVEL_DEBUG, "Text s1: %s", s1->value->cstring);
        strncpy(config.s1,s1->value->cstring ,30);
        config.save= true;
        //app_timer_cancel (timer);
        //timer = NULL;
	}
     if (s2) {
	  
	    APP_LOG(APP_LOG_LEVEL_DEBUG, "Text s2: %s", s2->value->cstring);
        strncpy(config.s2,s2->value->cstring ,30);
        config.save= true;
        //app_timer_cancel (timer);
        //timer = NULL;
	}
    if (s3) {
	  
	    APP_LOG(APP_LOG_LEVEL_DEBUG, "Text s3: %s", s3->value->cstring);
        strncpy(config.s3,s3->value->cstring ,30);
        config.save= true;
        //app_timer_cancel (timer);
        //timer = NULL;
	}
}

static void in_dropped_handler(AppMessageResult reason, void *context) {
    
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "Incoming AppMessage from Pebble dropped, %d", reason);
}

static void out_sent_handler(DictionaryIterator *sent, void *context) {
    
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "AppMessage dropped out sent handle");
    vibes_enqueue_custom_pattern(pat);
    //void splash_timer_callback();
    //vibes_short_pulse();
}

static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
    
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed to send AppMessage to Pebble, %d",reason);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "I, %s", failed->dict_size);
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "I, %d", failed->value->cstring);
}