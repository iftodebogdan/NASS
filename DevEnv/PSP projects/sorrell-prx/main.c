#include <pspkernel.h>
#include <pspdisplay.h>
#include <stdlib.h>
#include <pspdebug.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <pspgu.h>
#include <pspthreadman.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "blit.h"
#include <psploadcore.h>
#include <pspiofilemgr.h>
#include <malloc.h>
#include <psprtc.h>
#include <psputility.h>
#include <pspctrl.h>
#include <pspwlan.h>
#include <psppower.h>

#define O_RDONLY    0x0001
#define O_WRONLY    0x0002
#define O_RDWR      0x0003
#define O_NBLOCK    0x0010
#define O_APPEND    0x0100
#define O_CREAT     0x0200
#define O_TRUNC     0x0400
#define O_NOWAIT    0x8000 

PSP_MODULE_INFO("sorrell", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

int main_thread(SceSize args, void *argp) {

sceKernelDelayThread(2000000);

blit_setup();
blit_set_color(0x00ffffff,0x00000000);
int posx = 188;
int posy = 260;
int time = 0;
u32 tickResolution = sceRtcGetTickResolution();
u64 fpsTickNow;
u64 fpsTickLast;
char sVal[256];
SceCtrlData pad;

sceUtilityGetSystemParamString(PSP_SYSTEMPARAM_ID_STRING_NICKNAME, sVal, 256);
sceCtrlSetSamplingCycle(0);
sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	    
sceRtcGetCurrentTick( &fpsTickLast );
while(time <= 10)
	{/*
        if(time<=6)
                   blit_string(10, 10, "Detecting bio-signals");
        if(time<=6 && time>=2)
                   {
                              if (time==2) blit_string(8*20 + 32, 10, "0%");
                              if (time==3) blit_string(8*20 + 32, 10, "25%");
                              if (time==4) blit_string(8*20 + 32, 10, "50%");
                              if (time==5) blit_string(8*20 + 32, 10, "75%");
                              if (time==6) blit_string(8*20 + 32, 10, "100%");
                              if (time<=5)
                                      {
                                          sceCtrlReadBufferPositive(&pad, 1);
                                          if ( !(pad.Buttons & PSP_CTRL_DOWN) || pad.Ly >= 20 )
                                             while(1)
                                                         {
                                                                  blit_string(10, 20, "Subject does not match database! Shutting down PSP.");
                                                                  scePowerRequestStandby();
                                                                  sceDisplayWaitVblankStart();
                                                         }
                                      }
                   }
        if(time>=7)
                   {
                                 blit_string(10, 10, "Subject matches database...PSP unlocked");
                                 blit_string(10 + 8*8, 20, "Welcome, Iftode Bogdan!");
                   }
        */
		sceRtcGetCurrentTick( &fpsTickNow );
			if( (fpsTickNow - fpsTickLast) /  (u64)tickResolution >= 1 )
				{
					time++;
					fpsTickLast = fpsTickNow;
				}
				
		blit_string(posx, posy, sVal);
		sceDisplayWaitVblankStart();
	}
	
return 0;
}

int module_start(SceSize args, void *argp) {

int thid;

/* Create a high priority thread */
thid = sceKernelCreateThread("driver", main_thread, 0x18, 0x1000, 0, NULL);//8, 64*1024, PSP_THREAD_ATTR_USER, NULL);
if(thid >= 0) sceKernelStartThread(thid, args, argp);

return 0;
}
