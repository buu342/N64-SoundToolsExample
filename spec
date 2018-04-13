#include <nusys.h>

beginseg
    name    "code"
    flags   BOOT OBJECT
    entry   nuBoot
    address NU_SPEC_BOOT_ADDR
    stack   NU_SPEC_BOOT_STACK
    include "codesegment.o"
	include "$(ROOT)/usr/lib/PR/rspboot.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspL3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.Rej.fifo.o"
    include "$(ROOT)/usr/lib/PR/aspMain.o"
	include "$(ROOT)/usr/lib/PR/n_aspMain.o"
        include "$(ROOT)/usr/lib/PR/gspF3DEX2.NoN.fifo.o"
        include "$(ROOT)/usr/lib/PR/gspF3DLX2.Rej.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspS2DEX2.fifo.o"
endseg

// Pointer to bank sounds
beginseg
	name "pbank"
	flags RAW
	include "compbank.ptr"
endseg

// Bank containing sound data
beginseg
	name "wbank"
	flags RAW
	include "compbank.wbk"
endseg

// Music score
beginseg
	name "song1"
	flags RAW
	include "compmidi.bin"
endseg


// Sound effects list
beginseg
	name "sfx"
	flags RAW
	include "compfx.bfx"
endseg

beginwave
    name    "soundtutorial"
    include "code"
    
	include "pbank"
	include "wbank"
	include "song1"
	include "sfx"
endwave
