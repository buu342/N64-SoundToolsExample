include $(ROOT)/usr/include/make/PRdefs

N64KITDIR    = d:/nintendo/n64kit
NUSYSINCDIR  = $(N64KITDIR)/nusys/include
NUSYSLIBDIR  = $(N64KITDIR)/nusys/lib

LIB = $(ROOT)/usr/lib
LPR = $(LIB)/PR
INC = $(ROOT)/usr/include
CC  = gcc
LD  = ld
MAKEROM = mild

LCDEFS =	-DNU_DEBUG -DF3DEX_GBI_2
LCINCS =	-I. -I$(NUSYSINCDIR) -I$(ROOT)/usr/include/PR
LCOPTS =	-G 0

NUAUDIOLIB = -lnualstl_n_d -ln_gmus_d -ln_gaudio_sc

LDFLAGS = $(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) $(NUAUDIOLIB)  -lnusys_d -lgultra_d -L$(GCCDIR)/mipse/lib -lkmc

OPTIMIZER =	-g

APP =		soundtutorial.out

TARGETS =	soundtutorial.n64

CODEFILES   = 	main.c stage00.c configuration.c

CODEOBJECTS =	$(CODEFILES:.c=.o)  $(NUSYSLIBDIR)/nusys.o

DATAFILES   =	

DATAOBJECTS =	$(DATAFILES:.c=.o)

CODESEGMENT =	codesegment.o

OBJECTS =	$(CODESEGMENT) $(DATAOBJECTS)

default:        $(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(CODEOBJECTS) Makefile
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJECTS) $(LDFLAGS)

$(TARGETS):	$(OBJECTS)
		$(MAKEROM) spec -I$(NUSYSINCDIR) -r $(TARGETS) -e $(APP)
