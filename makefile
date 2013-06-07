TARGET = NASS
OBJS = Src/main.o Src/Drawable.o Src/Game.o Src/AnimatedSprite.o \
	   Src/ScrollingDrawable.o Src/Background.o Src/GameLogo.o \
	   Src/DropDownMenu.o Src/Controller.o Src/Font.o Src/Resources.o \
	   Src/Player.o Src/Enemy.o Src/CollisionDetection.o Src/ExperienceSystem.o \
	   Src/SkillsSystem.o Src/SaveLoad.o Src/SkillWarp.o Src/SkillDematerialize.o \
	   Src/SkillOverdrive.o Src/SkillForceField.o Src/Audio.o Src/Screen.o
 
INCDIR = 
CFLAGS = -O2 -g -G0 -Wall 
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