/*========================================================
				   Stage 00 of the game
========================================================*/
/*=================================
            Libraries
=================================*/

#include <nusys.h>
#include <nualstl_n.h>
#include "configuration.h"
#include "stages.h"


/*=================================
             Prototypes
=================================*/

static void paint_screen(char r, char g, char b);
void soundTest(void);


/*=================================
          Global Variables
=================================*/

static char r;
static char g;
static char b;
static int increase;

static int          playingmusic = 0;
static musHandle	seqHandle = 0;
static musHandle	sndHandle = 0;


/*=================================
           stage00_init
       Initialize the level
=================================*/

void stage00_init(void)
{
    r = 0;
    g = 0;
    b = 255;
    increase = 0;
    
    // Read and register the sample bank and it's pointers.
    Rom2Ram((void *)PBANK_START, (void *)ptr_buf, PBANK_END-PBANK_START);
    MusPtrBankInitialize(ptr_buf, WBANK_START);

    // Read and register the sound effects.
    Rom2Ram((void *)SFX_START, (void *)sfx_buf, SFX_END-SFX_START);
    MusFxBankInitialize(sfx_buf);
    
    // Read the song
    Rom2Ram((void *)MUSIC1_START, (void *)tune_buf, MUSIC1_END-MUSIC1_START);
    // Play the song as soon as the stage starts
    seqHandle = MusStartSong(tune_buf);
}


/*=================================
          stage00_update
    Update the level every clock
=================================*/

void stage00_update(void)
{
    // Change value of "b" depending on the value of increment.
    if (increase == 1)
        b +=3;
    else
        b -=3;
        
    // If we got pure black, start incrementing "b"
    if (b == 0)
    {
        sndHandle = MusStartEffect(FX_IMPDEAD1);
        increase = 1;
    }
    
    // If we got pure blue, start decreasing "b"
    if (b == 255)
    {
        sndHandle = MusStartEffect(FX_IMPDEAD2);
        increase = 0;
    }
}


/*=================================
          stage00_draw
        Make our display
=================================*/

void stage00_draw(void)
{
    // Assign our glist pointer to the glist array to make our life easier
    glistp = glist;

    // Initialze the RCP
    RCPInit();
    
    // Fill the screen with a color
    paint_screen(r, g, b);

    // Syncronize the CPU and GPU
    gDPFullSync(glistp++);
    
    // State that we finished our display list
    gSPEndDisplayList(glistp++);

    // Start the display list task
    nuGfxTaskStart(glist, (s32)(glistp - glist) * sizeof(Gfx), NU_GFX_UCODE_F3DEX, NU_SC_SWAPBUFFER);    
}


/*=================================
            paint_screen
    Wipe the screen with a color
=================================*/

static void paint_screen(char r, char g, char b)
{
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, osVirtualToPhysical(nuGfxCfb_ptr));
    gDPSetFillColor(glistp++, (GPACK_RGBA5551(r, g, b, 1) << 16 | GPACK_RGBA5551(r, g, b, 1)));
    gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
    gDPPipeSync(glistp++);
}