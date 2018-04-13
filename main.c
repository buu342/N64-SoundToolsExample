/*========================================================
				Initialize the game
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

static void   vsyncCallback(int pendingTaskCount);
void initAudio(void);


/*=================================
         Global Variables
=================================*/

int ptr_buf[NU_AU_SAMPLE_SIZE];
int tune_buf[NU_AU_SONG_SIZE];
int sfx_buf[NU_AU_SE_SIZE];


/*=================================
              Main
=================================*/

void  mainproc(void)
{
    // Initialize and activate the graphics thread and Graphics Task Manager.
    nuGfxInit(); 
    
    // Initialize audio thread
    initAudio();
    
    // Create a callback function
    nuGfxFuncSet((NUGfxFunc)vsyncCallback);
    
    // Turn on the screen
    nuGfxDisplayOn();

    // Initialize stage00
    stage00_init();

    // Loop forever to keep the idle thread busy
    while(1);
}


/*=================================
              initAudio
    Initialize the audio thread
=================================*/
void initAudio(void)
{
    musConfig c;

    c.control_flag	    = 0;                                // Set to MUSCONTROL_RAM if wbk file also placed in RAM
    c.channels		    = NU_AU_CHANNELS;                   // Maximum total number of channels
    c.sched		        = NULL;                             // ?
    c.thread_priority	= NU_AU_MGR_THREAD_PRI;             // thread priority (highest)
    c.heap		        = (unsigned char*)NU_AU_HEAP_ADDR;  // Heap address
    c.heap_length	    = NU_AU_HEAP_SIZE;                  // Heap size
    c.ptr		        = NULL;                             // Allows you to set a default ptr file
    c.wbk		        = NULL;                             // Allows you to set a default wbk file
    c.default_fxbank	= NULL;                             // Allows you to set a default bfx file
    c.fifo_length	    = NU_AU_FIFO_LENGTH;                // ?
    c.syn_updates	    = NU_AU_SYN_UPDATE_MAX;             // ?
    c.syn_output_rate	= 44100;                            // Audio output rate. The higher, the better quality
    c.syn_rsp_cmds	    = NU_AU_CLIST_LEN;                  // ?
    c.syn_retraceCount	= 1;                                // ?
    c.syn_num_dma_bufs	= NU_AU_DMA_BUFFER_NUM;             // ?
    c.syn_dma_buf_size	= NU_AU_DMA_BUFFER_SIZE;            // ?

    // Initialize the Audio Manager.
    nuAuStlMgrInit(&c);

    // Register the PRENMI function.
    nuAuPreNMIFuncSet(nuAuPreNMIProc);
}

/*=================================
          vsyncCallback
This is a callback functions which
execute instructions, and once
it has run out of instructions, it
activates the display process.
=================================*/
void  vsyncCallback(int pendingTaskCount)
{
    // Update stage00
    stage00_update();
    
    // If out of instructions, make the display
    if(pendingTaskCount < 1) 
        stage00_draw();
}
