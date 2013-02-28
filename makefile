TARGET = NASS
OBJS = Src/main.o Src/Drawable.o Src/Game.o Src/AnimatedSprite.o \
	   Src/ScrollingDrawable.o Src/Background.o Src/GameLogo.o Src/TitleScreen.o \
	   Src/Resources.o Src/DropDownMenu.o
 
INCDIR = 
CFLAGS = -G4 -Wall -O2 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
 
LIBDIR =
LDFLAGS =
STDLIBS= -losl -lpng -lz -ljpeg \
		 -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgu -lpspaudiolib \
		 -lpspaudio -lm -lstdc++ -lpsphprm
LIBS=$(STDLIBS)$(YOURLIBS)
 
BUILD_PRX = 1
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = N.A.S.S.
 
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak