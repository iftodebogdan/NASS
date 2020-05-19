TARGET = sorrell
OBJS = main.o blit.o
BUILD_PRX = 1

#USE_PSPSDK_LIBC = 1

INCDIR =
LIBDIR =
LIBS = -lpspctrl -lpsprtc -lpsppower 
LDFLAGS =
CFLAGS = -Os -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak