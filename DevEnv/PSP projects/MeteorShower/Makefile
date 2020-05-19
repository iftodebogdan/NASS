TARGET = Meteor_Shower_v0.6
OBJS = main.o TGALoader.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS += -losl -lpspuht -lpsppower -lpspgum -lpspgu -lstdc++ -lm -lpspusb -lpsputility -lpspusbcam -lpspjpeg -lpsprtc -lpsphprm -lpsphprm_driver -lpspaudiolib -lpspaudio
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Meteor Shower v0.6
PSP_EBOOT_ICON = icon0.png
PSP_EBOOT_PIC1 = pic1.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

./main.o: ./main.c 
	$(CXX) $(CXXFLAGS) -c ./main.c -o ./main.o

./TGALoader.o: ./TGALoader.cpp 
	$(CXX) $(CXXFLAGS) -c ./TGALoader.cpp -o ./TGALoader.o

./uht.o: ./uht.cpp 
	$(CXX) $(CXXFLAGS) -c ./uht.cpp -o ./uht.o