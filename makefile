TARGET = test
OBJS = main.o  
 
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
PSP_FW_VERSION=390
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = test
 
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak