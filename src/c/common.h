#define SETTINGS_KEY 0
#define SETTINGS_KEY1 1

enum {
    SELECT_KEY = 0x0,
    SHUTDOWN_KEY = 0x1,
    RESTART_KEY = 0x2,
    LOCK_KEY = 0x3,
    LOG_OFF_KEY = 0x4,
    SLEEP_KEY =  0x5,
    ABORT_KEY = 0x6,

    SERVER1_KEY = 0x7,
    SERVER2_KEY = 0x8,
    SERVER3_KEY = 0x9,
    
    TURN_ON = 0x11,
    TURN_OFF = 0x12,
    
    VLC_PLAY = 0x21,
    VLC_NEXT = 0x22,
    VLC_PREVIOUS = 0x23,
    VLC_M10 = 0x24,
    VLC_L10 = 0x25,
    
    XBMC_PLAY = 0x26,
    XBMC_NEXT = 0x27,
    XBMC_PREVIOUS = 0x28,
    XBMC_M10 = 0x29,
    XBMC_L10 = 0x30,
    
    PLEX_PLAY = 0x31,
    PLEX_PREVIOUS = 0x32,
    PLEX_NEXT = 0x33,
    PLEX_FORWARD = 0x34,
    PLEX_REWIND = 0x35,
    
    SPOTIFY_PLAY = 0x36,
    SPOTIFY_NEXT = 0x37,
    SPOTIFY_PREVIOUS = 0x38,
    
    VOLUME_UP  = 0x41,
    VOLUME_DOWN  = 0x42,
    VOLUME_MUTE  = 0x43,
    
    ITUNES_PLAY = 0x44,
    ITUNES_NEXT = 0x45,
    ITUNES_PREVIOUS = 0x46,
    ITUNES_M10 = 0x47,
    ITUNES_L10 = 0x48,
    
    WINDOW_OPEN = 0x51,
    WINDOW_RUN = 0x52,
    WINDOW_MINIMIZE = 0x53,
    
    PPOINT_NEXT = 0x61,
    PPOINT_PREVOUS = 0x62,
    PPOINT_BLACK = 0x63,
    PPOINT_WHITE = 0x64,
    PPOINT_START = 0x65,
    PPOINT_END =  0x66,
    
    CHROME_HOME = 0x71,
    CHROME_REFRESH = 0x72,
    CHROME_BACK_P = 0x73,
    CHROME_NEXT_P = 0x74,
    CHROME_BACK_T = 0x75,
    CHROME_NEXT_T = 0x76,
    CHROME_UP = 0x77,
    CHROME_DOWN = 0x78,
    
    YOUTUBE_PLAY = 0x81,
    YOUTUBE_NEXT = 0x82,
    YOUTUBE_PREVIOUS = 0x83,
    YOUTUBE_M10 = 0x84,
    YOUTUBE_L10 = 0x85,
    
    NETFLIX_PLAY = 0x91,
    NETFLIX_NEXT = 0x92,
    NETFLIX_PREVIOUS = 0x93,
    
    PANDORA_PLAY = 0X94,
    PANDORA_NEXT = 0x95,
    PANDORA_UP = 0x96,
    PANDORA_DOWN = 0x97,
      
    FOOBAR_PLAY = 0x98,
    FOOBAR_NEXT = 0x99,
    FOOBAR_PREVIOUS = 0x100,
    FOOBAR_STOP = 0x101,
      
    MONKEY_PLAY = 0x102,
    MONKEY_NEXT = 0x103,
    MONKEY_PREVIOUS = 0x104,
    MONKEY_STOP = 0x105,
      
    WMPLAYER_PLAY = 0x106,
    WMPLAYER_NEXT = 0x107,
    WMPLAYER_PREVIOUS = 0x108,
    WMPLAYER_STOP = 0x109,
      
    GMEDIA_PLAY = 0x110,
    GMEDIA_NEXT = 0x111,
    GMEDIA_PREVIOUS = 0x112,
    GMEDIA_STOP = 0x113,
      
    WINAP_PLAY = 0x114,
    WINAP_NEXT = 0x115,
    WINAP_PREVIOUS = 0x116,
    WINAP_STOP = 0x117,
      
    GSLIDE_NEXT = 0x118,
    GSLIDE_PREVIOUS = 0x119,
    GSLIDE_START = 0x120,
    GSLIDE_END = 0x121,
    
    DATA_INSTALLED = 0x10, 
    DATA_KEY = 0
};
typedef struct Information {
	char s1[30];
    char s2[30];
    char s3[30];
    bool save;
} __attribute__((__packed__)) Information;

typedef struct Information1 {
 
    char s0[30];
    bool save1;
} __attribute__((__packed__)) Information1;

extern Information config;
extern Information1 config1;
