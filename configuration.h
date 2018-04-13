/*========================================================
                Configuration of the game
                       for porting
========================================================*/

#ifndef N64_CONFIG_H
#define N64_CONFIG_H

    /*=================================
           Hardware configuration
    =================================*/

    #define DISPLAY_LIST_LEN     2048

    
    /*=================================
            Television and Screen
    =================================*/

    #define SCREEN_WD 320
    #define SCREEN_HT 240

    
    /*=================================
         Variables and prototypes
    =================================*/
    
    extern Gfx glist[DISPLAY_LIST_LEN]; // Display list array
    extern Gfx * glistp;                 // Display list buffer
    
    extern int ptr_buf[];
    extern int tune_buf[];
    extern int sfx_buf[];
    
    void RCPInit(void);
    void Rom2Ram(void *from_addr, void *to_addr, s32 seq_size);
    
    
    /*=================================
           Sound code segments
    =================================*/
    
    // Code segment start and end
    extern char _codeSegmentStart[];
    extern char _codeSegmentEnd[];

    // Segment arrays
    extern u8 _wbankSegmentRomStart[];
    extern u8 _pbankSegmentRomStart[];
    extern u8 _pbankSegmentRomEnd[];
    extern u8 _song1SegmentRomStart[];
    extern u8 _song1SegmentRomEnd[];
    extern u8 _sfxSegmentRomStart[];
    extern u8 _sfxSegmentRomEnd[];

    // Segment macros
    #define WBANK_START	    _wbankSegmentRomStart
    #define PBANK_START	    _pbankSegmentRomStart
    #define PBANK_END	    _pbankSegmentRomEnd
    #define MUSIC1_START	_song1SegmentRomStart
    #define MUSIC1_END   	_song1SegmentRomEnd
    #define SFX_START	    _sfxSegmentRomStart
    #define SFX_END		    _sfxSegmentRomEnd
    
    // compfx.bfx sound effect macros
    #define FX_IMPDEAD1             0
    #define FX_IMPDEAD2             1


#endif