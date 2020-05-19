#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
/* structuri necesare activarii Kernel-ului PSP-ului */
PSP_MODULE_INFO("CONTROLTEST", 0, 1, 1);

PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

void dump_threadstatus(void);

int done = 0, x = 0, y = 0, i, n = 1, k = 1, OK=0;

int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread,
				     0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}

/* structura centrala */
int main(void)
{
while (OK==0){
	SceCtrlData pad;

	pspDebugScreenInit();
	SetupCallbacks();

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	pspDebugScreenPrintf ("UP=1 LEFT=2 DOWN=3 RIGHT=4 TRIANGLE=5 SQUARE=6 X=7 CIRCLE=8 L-TRIGGER=9 R-TRIGGER=0 START=OK \n");
	pspDebugScreenPrintf ("\n *dupa fiecare cifra scrisa apasati SELECT pentru a introduce o alta cifra in coada numarului \n");
	pspDebugScreenPrintf ("\nscrie numarul ce va fi ridicat la putere apoi apasa START: ");
	
	while(!done){
    		while (k!=0) {
		sceCtrlReadBufferPositive(&pad, 1); 
			if (pad.Buttons & PSP_CTRL_SQUARE){
				x = x*10+6;
				pspDebugScreenPrintf("6");
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_TRIANGLE){
				x = x*10+5;
				pspDebugScreenPrintf("5");
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_CIRCLE){
				x = x*10+8;
				pspDebugScreenPrintf("8");
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_CROSS){
				x = x*10+7;
				pspDebugScreenPrintf("7");
				k = 0;
			} 

			if (pad.Buttons & PSP_CTRL_UP){
				x = x*10+1;
				pspDebugScreenPrintf("1");
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_DOWN){
				x = x*10+3;
				pspDebugScreenPrintf("3");
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_LEFT){
				x = x*10+2;
				pspDebugScreenPrintf("2");
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_RIGHT){
				x = x*10+4;
				pspDebugScreenPrintf("4");
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_LTRIGGER){
				x = x*10+9;
				pspDebugScreenPrintf("9");
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_RTRIGGER){
				x = x*10;
				pspDebugScreenPrintf("0");
				k = 0;
			}
			}
			while (k==0){
			sceCtrlReadBufferPositive(&pad, 1);
			if (pad.Buttons & PSP_CTRL_SQUARE){
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_TRIANGLE){
				
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_CIRCLE){
				
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_CROSS){
				
				k = 0;
			} 

			if (pad.Buttons & PSP_CTRL_UP){
				
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_DOWN){
				
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_LEFT){
				
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_RIGHT){
				
				k = 0;
			}      

			if (pad.Buttons & PSP_CTRL_START){
				done = 1;
				pspDebugScreenPrintf ("\n");
				k = 1;
			}
			if (pad.Buttons & PSP_CTRL_LTRIGGER){
				
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_RTRIGGER){
				
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_SELECT)
			{k = 1;}
			}
		}
	
	/* se reinitializeaza variabilele done si k */	
	done = 0;
	k = 1;
	
	pspDebugScreenPrintf ("scrie puterea la care va fi ridicat x: ");
	
	/* se citeste y */
	while(!done){
    		while (k!=0) {
		sceCtrlReadBufferPositive(&pad, 1); 
			if (pad.Buttons & PSP_CTRL_SQUARE){
				y = y * 10+6;
				pspDebugScreenPrintf("6");
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_TRIANGLE){
				y = y*10+5;
				pspDebugScreenPrintf("5");
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_CIRCLE){
				y = y*10+8;
				pspDebugScreenPrintf("8");
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_CROSS){
				y = y*10+7;
				pspDebugScreenPrintf("7");
				k = 0;
			} 

			if (pad.Buttons & PSP_CTRL_UP){
				y = y*10+1;
				pspDebugScreenPrintf("1");
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_DOWN){
				y = y*10+3;
				pspDebugScreenPrintf("3");
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_LEFT){
				y = y*10+2;
				pspDebugScreenPrintf("2");
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_RIGHT){
				y = y*10+4;
				pspDebugScreenPrintf("4");
				k = 0;
			}      
			if (pad.Buttons & PSP_CTRL_LTRIGGER){
				y = y*10+9;
				pspDebugScreenPrintf("9");
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_RTRIGGER){
				y = y*10;
				pspDebugScreenPrintf("0");
				k = 0;
			}
			}
			while (k==0){
			sceCtrlReadBufferPositive(&pad, 1);
			if (pad.Buttons & PSP_CTRL_SQUARE){
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_TRIANGLE){
				
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_CIRCLE){
				
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_CROSS){
				
				k = 0;
			} 

			if (pad.Buttons & PSP_CTRL_UP){
				
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_DOWN){
				
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_LEFT){
				
				k = 0;
			} 
			if (pad.Buttons & PSP_CTRL_RIGHT){
				
				k = 0;
			}      

			if (pad.Buttons & PSP_CTRL_START){
				done = 1;
				pspDebugScreenPrintf ("\n");
				k = 1;
			}
			if (pad.Buttons & PSP_CTRL_LTRIGGER){
				
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_RTRIGGER){
				
				k = 0;
			}
			if (pad.Buttons & PSP_CTRL_SELECT)
			{k = 1;}
			}
		}

		done = 0;
		
	/* se calculeaza x la puterea y si se stocheaza valoarea in variabila n*/
	for (i=1;i<=y;i++){
		n = n*x;
		}
		
	/* se afiseaza n*/
	pspDebugScreenPrintf ("\n");pspDebugScreenPrintf ("%d", x);pspDebugScreenPrintf (" la puterea ");pspDebugScreenPrintf ("%d", y);pspDebugScreenPrintf (" = %d", n);
		
	/* se pune conditia inchiderii aplicatiei*/
	pspDebugScreenPrintf ("\n");pspDebugScreenPrintf ("apasa L+R+SELECT pentru a mai calcula o data sau L+R+START pentru a inchide aplicatia");
	while (!done){
		sceCtrlReadBufferPositive(&pad, 1);
		if (pad.Buttons & PSP_CTRL_LTRIGGER){
		if (pad.Buttons & PSP_CTRL_RTRIGGER){
		if (pad.Buttons & PSP_CTRL_START){
		done = 1;
		sceKernelExitGame();
		OK=1;
		return 0;}
		else if(pad.Buttons & PSP_CTRL_SELECT){
		pspDebugScreenClear();}
		}
	}
}
}
}