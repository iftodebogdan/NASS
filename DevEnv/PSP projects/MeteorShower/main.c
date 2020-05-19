#include "Globals.c"
#include "GU.c"
#include "GameEngine.c"
#include "Debug.c"
#include "MainMenu.c"
#include "LoadData.c"
#include "Audio.c"

int main()
{
	//SetupCallbacks(); //uncomment pt folosirea butonului HOME
		
	pspDebugScreenInit();
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	sceRtcGetCurrentTick( &fpsTickLast );
	
	while( 1 )
		{
			init_vars();
			InitCamera();
			InitAudio();
			LoadData();
	
			sceKernelUtilsMt19937Init( &ctx, time( NULL ) );
			
			
	        main_menu();
	        
			InitGU();
			SetupProjection();
			
			while ( 1 )
				{
					scePowerTick(6);
					MoveTriangle();
					MoveCircle();
					MoveRocket();
					MoveBackground();
					Collision_Detection();
					if( RenderFreq == 1 )
                        {
                                   fbp0 = sceGuSwapBuffers();
                                   DrawScene();
					               DebugMode();
					               RenderFreq = fpsMode;
                        }
                    else RenderFreq--;
					
				}
			sceGuTerm(); // incheie modulul grafic
			// elibereaza memoria
			free( dList );
			free( fbp0 );
		}

	sceKernelSleepThread();
	return 0;
}
