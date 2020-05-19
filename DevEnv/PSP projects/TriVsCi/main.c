#include <pspkernel.h>
#include <pspdisplay.h>
#include <psphprm.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <pspgum.h>
#include <psprtc.h>
#include <pspctrl.h>
#include <psppower.h>
#include <psputils.h>
#include <pspthreadman.h>
#include <pspsdk.h>
#include <pspuser.h>
#include <pspiofilemgr.h>
#include <psputility.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_INPUT_FIELDS	(1)
#define TEXT_LENGTH			(25)

#define BUF_WIDTH (512)
#define SCR_WIDTH (479)
#define SCR_HEIGHT (271)

PSP_MODULE_INFO("My_Module",0,1,1);

#define printf pspDebugScreenPrintf

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
          sceKernelExitGame();
          return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
          int cbid;

          cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
          sceKernelRegisterExitCallback(cbid);

          sceKernelSleepThreadCB();

          return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
          int thid = 0;

          thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
          if(thid >= 0) {
                    sceKernelStartThread(thid, 0, 0);
          }

          return thid;
}

//inceput functii
void FPS( void );				// Calculeaza FPS-ul

//Functii pentru grafica:
void InitGU( void );			        // Initializeaza sistemul grafic
void SetupProjection( void );	                // Initiaza matricea de proiectie
void DrawScene( void );			        // Deseneaza pe ecran

int quit_menu();
void init_vars();
void game_over();
void DebugMode();
time_t time ( time_t * timer );         //pt a nu mai aparea warning la compilare
//sfarsit functii

//declarare variabile
void *dList;		// display List, folosit de sceGUStart
void *fbp0;		// frame buffer

int fps = 0;		// variabile pentru calcularea FPS-ului
int fpsDisplay;
u32 tickResolution;
u32 HPRM_input = -1;
u64 fpsTickNow;
u64 fpsTickLast;

SceCtrlData pad;	// variabila pentru citirea tastelor
float SpeedX = 0;	//variabile pentru miscarea obiectului pe X si Y
float SpeedY = 0;
float SpeedCircle = 0.050f;
float PlayerHP = 100, PlayerX = -3.80f, PlayerY, PlayerRandY = 0.00f, CircleX = 5.00f, CircleY, CircleRandY = 0.00f, CircleRadius = 0.5f, menu_select = 1, quit_select = 2, debug_init = -1, HPRM_inv = 1, distance;
float time_now = 0,time_last = 0;

SceKernelUtilsMt19937Context ctx;
int low = -200, high = 200;
u32 rand_val;

SceUID file;
int i,j,print_highscore=0;
char data[5];
struct
      {
             int pos;
             char name[26];
             int time;
      } record[10];

unsigned short intext[NUM_INPUT_FIELDS][TEXT_LENGTH];
unsigned short outtext[NUM_INPUT_FIELDS][TEXT_LENGTH];
unsigned short desc[NUM_INPUT_FIELDS][TEXT_LENGTH];
SceUtilityOskData osk_data[NUM_INPUT_FIELDS];
SceUtilityOskParams params;

typedef struct {
	unsigned int color;
	float x, y, z;
} Vertex;

Vertex __attribute__((aligned(16))) triangle[3] = 
{
	{ GU_COLOR( 1.0f, 0.0f, 0.0f, 0.0f ),  2 * 0.288f, 0.0f, 0.0f },     // varf sus
	{ GU_COLOR( 0.0f, 0.0f, 1.0f, 0.0f ), -1 * 0.288f,-0.5f, 0.0f },     // varf dreapta
	{ GU_COLOR( 0.0f, 0.0f, 1.0f, 0.0f ), -1 * 0.288f, 0.5f, 0.0f }      // varf stanga
};

Vertex __attribute__((aligned(16))) circle[360];
//sfarsit declarare variabile

void FPS( void )
{
	fps++;
	sceRtcGetCurrentTick( &fpsTickNow );
	
	if( ( (fpsTickNow - fpsTickLast) / ( (float)sceRtcGetTickResolution()) ) >= 1.0f )
	{
		fpsTickLast = fpsTickNow;
		fpsDisplay = fps;
		fps = 0;
	} 
}

void InitGU( void )
{
	// Init GU
	sceGuInit();
	gumInit();
        sceGuStart( GU_DIRECT, dList );
	// Set Buffers
	sceGuDrawBuffer( GU_PSM_8888, fbp0, BUF_WIDTH );
	sceGuDispBuffer( SCR_WIDTH, SCR_HEIGHT, (void*)0x88000, BUF_WIDTH);
	sceGuDepthBuffer( (void*)0x110000, BUF_WIDTH);
 
	sceGuViewport( 2048, 2048, SCR_WIDTH, SCR_HEIGHT);
	sceGuOffset( 2048 - (SCR_WIDTH/2), 2048 - (SCR_HEIGHT/2));
	sceGuDepthRange( 65535, 0);
	// Set Render States
	sceGuScissor( 0, 0, SCR_WIDTH, SCR_HEIGHT);
	sceGuEnable( GU_SCISSOR_TEST );
	sceGuDepthFunc( GU_GEQUAL );
	sceGuEnable( GU_DEPTH_TEST );
	sceGuFrontFace( GU_CW );
	sceGuShadeModel( GU_SMOOTH );
	sceGuEnable( GU_CULL_FACE );
	sceGuEnable( GU_CLIP_PLANES );
        sceGuFinish();
	sceGuSync(0,0);
 
	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);
}

void SetupProjection( void )
{
	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective(75.0f,16.0f/9.0f,2.0f,1000.0f);
	
	sceGumMatrixMode(GU_VIEW);
	sceGumLoadIdentity();
 
	sceGuClearColor( GU_COLOR( 0.0f, 0.0f, 0.0f, 1.0f ) ); 
	sceGuClearDepth(0);	
}

void InitCircle()
{
	int i;
	for(i=0;i<=89;i++)
		{
			//coordonatele X
			circle[i].x = CircleRadius * sin(i);
			circle[i + 180].x = -circle[i].x;
			circle[180 - i].x = circle[i].x;
			circle[360 - i].x = -circle[i].x;
			
			//coordonatele Y
			circle[i].y = CircleRadius * cos(i);
			circle[i + 180].y = -circle[i].y;
			circle[180 - i].y = -circle[i].y;
			circle[360 - i].y = circle[i].y;
			
			//culoarea
			circle[i].color = circle[180 + i].color = circle[180 - i].color = circle[360 - i].color = GU_COLOR( 1.0f, 1.0f, 1.0f, 0.0f );
		}
}

void DrawScene( void )
{
	sceGuStart( GU_DIRECT, dList );
	
	// clr scr
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	sceGumMatrixMode(GU_MODEL);
	//deseneaza triunghi
	sceGumLoadIdentity();
	{
	ScePspFVector3 move = { PlayerX, PlayerRandY, -3.0f };
	sceGumTranslate( &move );
	}
	sceGumDrawArray( GU_TRIANGLES, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,
			3, 0, triangle );
	//deseneaza cerc
	sceGumLoadIdentity();
	{
	ScePspFVector3 move = { CircleX, CircleRandY, -3.0f };
	sceGumTranslate( &move );
	}
	sceGumDrawArray( GU_TRIANGLE_FAN, GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,
	360, 0, circle );
	
	sceGuFinish();
	sceGuSync(0,0);
}

void MoveTriangle()
{	
	sceCtrlReadBufferPositive(&pad, 1);
    
    //control de pe analog
	SpeedX = ( (float)pad.Lx - ( 255 / 2 ) ) / 2000;
	SpeedY = -1 * ( ( (float)pad.Ly - ( 255 / 2 ) ) / 2000 );
	
	//control de pe telecomanda
	if( (sceHprmIsRemoteExist() && HPRM_input == -1) || (!sceHprmIsRemoteExist() && HPRM_input != -1) )
	    time_last = time_now; //in momentul conectarii/deconectarii, afiseaza info despre Debug Mode
	if( sceHprmIsRemoteExist() )
	    {
                               sceHprmPeekCurrentKey( &HPRM_input );
                               if( HPRM_input != PSP_HPRM_HOLD )
                                   {
                                         //Nu sunt citite VOL_UP si VOL_DOWN in User Mode! Damn it!
                                         /*
                                         if (HPRM_input == PSP_HPRM_VOL_UP) SpeedY = 0.0635f;
				                         else if (HPRM_input == PSP_HPRM_VOL_DOWN) SpeedY = -0.0640f;
				                         */
				                         
				                         if (HPRM_input == PSP_HPRM_FORWARD) SpeedY = -0.0640f * HPRM_inv;
				                         else if (HPRM_input == PSP_HPRM_BACK) SpeedY = 0.0640f * HPRM_inv;
                                         if (HPRM_input == PSP_HPRM_PLAYPAUSE)
                                            {
                                                     debug_init *= (-1);
													 time_last = time_now;
                                                     do
                                                       sceHprmPeekCurrentKey( &HPRM_input );
                                                     while( HPRM_input == PSP_HPRM_PLAYPAUSE );
                                            }
                                   }
        }
     else HPRM_input = -1;
	
	if( SpeedX >= 0.01f || SpeedX <= -0.01f )
		{
			if( PlayerX > 3.5f && SpeedX < 0 )
				PlayerX += SpeedX;
			if( PlayerX < -3.8f && SpeedX > 0 )
				PlayerX += SpeedX;
			if(PlayerX <= 3.5f && PlayerX >= -3.8f)
				PlayerX += SpeedX;
		}
	
	if( SpeedY >= 0.01f || SpeedY <= -0.01f )
		{
			if( PlayerRandY > 1.8f && SpeedY < 0 )
				PlayerRandY += SpeedY;
			if( PlayerRandY < -1.8f && SpeedY > 0 )
				PlayerRandY += SpeedY;
			if( PlayerRandY <= 1.8f && PlayerRandY >= -1.8f )
				PlayerRandY += SpeedY;
		}
	if( pad.Buttons != 0 )
		{
			if (pad.Buttons & PSP_CTRL_START)
				{
					while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
					quit_menu();
				}
			if(pad.Buttons & PSP_CTRL_SQUARE)
						{
							while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
							debug_init *= (-1);
							time_last = time_now;
						}
			if(pad.Buttons & PSP_CTRL_TRIANGLE)
						{
							while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
							HPRM_inv *= (-1);
							time_last = time_now;
						}
		}
}

void MoveCircle()
{
	if( CircleX < -5.00f )
		{
			CircleX = 5.00f;
			SpeedCircle += 0.002f;
			
			rand_val = sceKernelUtilsMt19937UInt(&ctx);
   	 rand_val = low + rand_val % (high-low);
			
			CircleRandY = (float)( (int)rand_val ) / 100;
		}
	else CircleX -= SpeedCircle;
}

int Collision_Detection()
{
	distance = sqrt( pow( CircleX - PlayerX , 2 ) + pow( CircleRandY - PlayerRandY , 2 ) );
	if( distance <= CircleRadius + 0.288f )
		{
			if( PlayerHP > 10 * SpeedCircle )
					PlayerHP -= 10 * SpeedCircle;
			else PlayerHP = 0;
			sceKernelDelayThread( 1000000 / 30 );
			if( PlayerHP == 0 )
				{
					DebugMode();
					sceKernelDelayThread( 2 * 1000000 );
					game_over();
				}
			return 1;
		}
	else return 0;
}

void DebugMode()
{
	pspDebugScreenSetOffset( (int)fbp0 );
	pspDebugScreenSetXY( 1, 1 );
	printf( "HP: %1.0f %c", PlayerHP , 37 );
	
	pspDebugScreenSetXY( 56, 1 );
	sceRtcGetCurrentTick( &fpsTickNow );
	if( (fpsTickNow - fpsTickLast) /  (float)sceRtcGetTickResolution() >= 1 )
		{
			time_now++;
			fpsTickLast = fpsTickNow;
		}
	printf( "Time: %2d:%02d", (int)time_now / 60, (int)time_now % 60 );
	
	if( PlayerHP == 0 )
		{
			pspDebugScreenSetXY ( 15, 10 );
			printf("Game Over!");
		}
	
	if( debug_init == 1 )
		{
			pspDebugScreenSetXY( 1, 3 );
			printf( "PlayerX: %f u.m.", PlayerX );
			pspDebugScreenSetXY( 1, 4);
			printf( "PlayerY: %f u.m.", PlayerRandY );
			pspDebugScreenSetXY( 1, 5 );
			printf( "SpeedX: %f u.m./s", SpeedX );
			pspDebugScreenSetXY( 1, 6 );
			printf( "SpeedY: %f u.m./s", SpeedY );
			pspDebugScreenSetXY( 1, 7 );
			printf( "CircleX: %f u.m.", CircleX );
			pspDebugScreenSetXY( 1, 8 );
		    printf( "CircleY: %f u.m.", CircleRandY );
			pspDebugScreenSetXY( 1, 9 );
			printf( "CircleRadius: %f u.m.", CircleRadius );
			pspDebugScreenSetXY( 1, 10 );
			printf( "SpeedCircle: %f u.m./s", SpeedCircle );
			pspDebugScreenSetXY( 1, 11 );
			printf( "Distance: %f u.m.", distance );
			if( sceHprmIsRemoteExist() )
                {
                   pspDebugScreenSetXY( 1, 12 );
			       printf( "HPRM input: %x", HPRM_input );
                }
		}
	if(time_now - time_last <= 5)
				{
					if( debug_init == 1 )
						pspDebugScreenSetXY( 1, 14 );
					else pspDebugScreenSetXY( 1, 2 );
					if( sceHprmIsRemoteExist() )
                        {
                            printf( "Press SQUARE or PLAY/PAUSE (HPRM) to enable/disable Debug Mode" );
                            if( debug_init == 1 )
						        pspDebugScreenSetXY( 1, 15 );
					        else pspDebugScreenSetXY( 1, 3 );
					        printf( "Press TRIANGLE to invert HPRM input" );
                        }
                    else printf( "Press SQUARE to enable/disable Debug Mode" );
				}
	pspDebugScreenSetXY ( 1, 32 );
	printf("Press START to quit");
	pspDebugScreenSetXY ( 32, 32 );
	printf("Copyright (c) 2010 by Iftode Bogdan");
}

int main_menu()
{
	while( 1 )
		{
            if( !sceHprmIsRemoteExist() )
                if( menu_select == 4 )
                    menu_select = 1; //reseteaza menu_select in caz de deconectare HPRM
            
			//pspDebugScreenClear();
			pspDebugScreenSetOffset( (int)fbp0 );
			pspDebugScreenSetXY ( 2, 2 );
			if( menu_select == 1 ) printf( "->" );
			else printf( "  " );
			printf( "Play" );
	
			pspDebugScreenSetXY ( 2, 3 );
			if( menu_select == 2 ) printf( "->" );
			else printf( "  " );
			printf( "Debug Screen        " );
			if( debug_init == 1 ) printf( "Enabled  " );
			if( debug_init == -1 ) printf( "Disabled" );
            
            if( sceHprmIsRemoteExist() )
                {
                    pspDebugScreenSetXY ( 2, 4 );
			        if( menu_select == 3 ) printf( "->" );
			        else printf( "  " );
			        printf( "HPRM inverse        " );
                    if( HPRM_inv == 1 ) printf( "PREV - move up  &  NEXT - move down" );
			        if( HPRM_inv == -1 ) printf( "NEXT - move up  &  PREV - move down" );
			
			        pspDebugScreenSetXY ( 2, 5 );
			        if( menu_select == 4 ) printf( "->" );
			        else printf( "  " );
			        printf( "Exit" );
                }
            else
                {
                    pspDebugScreenSetXY ( 2, 4 );
			        if( menu_select == 3 ) printf( "->" );
			        else printf( "  " );
			        printf( "Exit                                                        " ); //spatiul e pt a acoperi scrisul care ramane
					pspDebugScreenSetXY ( 2, 5 );										  	  //in cazul deconectarii HPRM-ului
					printf( "          " );
                }
	
			pspDebugScreenSetXY ( 32, 32 );
			printf("Copyright (c) 2010 by Iftode Bogdan");
			
//			while( 1 )
//				{
					sceCtrlReadBufferPositive(&pad, 1);
			
					if (pad.Buttons != 0)
						{
							if (pad.Buttons & PSP_CTRL_UP)
								{
									if( menu_select > 1 ) menu_select--;
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									//break;
								} 
							if (pad.Buttons & PSP_CTRL_DOWN)
								{
									if( sceHprmIsRemoteExist() )
                                          {
                                               if( menu_select < 4 ) menu_select++;
                                          }
									else if( menu_select < 3 ) menu_select++;
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									//break;
								}
							if (pad.Buttons & PSP_CTRL_CROSS)
								{
									if( menu_select == 1 )
										{
											while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											return 0;
										}
									if( menu_select == 2 )
										{
											debug_init *= (-1);
											time_last = time_now;
											while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											//break;
										}
									if( sceHprmIsRemoteExist() )
                                        {
                                            if( menu_select == 3 )
										         {
										         	HPRM_inv *= (-1);
									                while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											        //break;
										         }
									        if( menu_select == 4 )
										         {
			                                        while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											        sceKernelExitGame();
											        return 0;
										         }
                                        }
                                    else
                                        {
                                            if( menu_select == 3 )
										         {
			                                        while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											        sceKernelExitGame();
											        return 0;
										         }
                                        }
								}
						}
					sceDisplayWaitVblankStart();
//				}
		}
}

int quit_menu()
{
	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
	sceGuClearColor(0);
	sceGuClearDepth(0);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	while ( 1 )
		{
			pspDebugScreenSetOffset( (int)fbp0 );
			pspDebugScreenClear();
			pspDebugScreenSetXY ( 2, 2 );
			printf("Quit?");
			pspDebugScreenSetXY ( 2, 4 );
			if( quit_select == 1 ) printf( "->Yes             No" );
			else 									printf( "  Yes           ->No" );
			
			pspDebugScreenSetXY ( 32, 32 );
			printf("Copyright (c) 2010 by Iftode Bogdan");
			
			while( 1 )
				{
					sceCtrlReadBufferPositive(&pad, 1);
			
					if (pad.Buttons != 0)
						{
							if (pad.Buttons & PSP_CTRL_LEFT)
								{
									if( quit_select == 2 ) quit_select--;
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									break;
								}
							if (pad.Buttons & PSP_CTRL_RIGHT)
								{
									if( quit_select == 1 ) quit_select++;
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									break;
								}
							if (pad.Buttons & PSP_CTRL_CROSS)
								{
									if( quit_select == 1 )
										{
											while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											init_vars();
											main_menu();
										}
									if( quit_select == 2 )
										{
											while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											return 0;
										}
								}
						}
				}
		}
}

void on_screen_keyboard()
{	
	memset(&intext, 0, NUM_INPUT_FIELDS * TEXT_LENGTH * sizeof(unsigned short));
	memset(&outtext, 0, NUM_INPUT_FIELDS * TEXT_LENGTH * sizeof(unsigned short));
	memset(&desc, 0, NUM_INPUT_FIELDS * TEXT_LENGTH * sizeof(unsigned short));
	
	int i;
	
	for(i = 0;i < NUM_INPUT_FIELDS;i++)
	{
		desc[i][0] = 'N';
		desc[i][1] = 'e';
		desc[i][2] = 'w';
		desc[i][3] = ' ';
		desc[i][4] = 'H';
		desc[i][5] = 'i';
		desc[i][6] = 'g';
		desc[i][7] = 'h';
		desc[i][8] = '-';
		desc[i][9] = 'S';
		desc[i][10] = 'c';
		desc[i][11] = 'o';
		desc[i][12] = 'r';
		desc[i][13] = 'e';
		desc[i][14] = '!';
		
		intext[i][0] = 'Y';
		intext[i][1] = 'o';
		intext[i][2] = 'u';
		intext[i][3] = 'r';
		intext[i][4] = ' ';
		intext[i][5] = 'N';
		intext[i][6] = 'a';
		intext[i][7] = 'm';
		intext[i][8] = 'e';
		
	}
	
	for(i = 0; i < NUM_INPUT_FIELDS;i++)
	{
		memset(&osk_data[i], 0, sizeof(SceUtilityOskData));
		osk_data[i].language = PSP_UTILITY_OSK_LANGUAGE_DEFAULT; // Use system default for text input
		osk_data[i].lines = 1;
		osk_data[i].unk_24 = 1;
		osk_data[i].inputtype = PSP_UTILITY_OSK_INPUTTYPE_ALL; // Allow all input types
		osk_data[i].desc = desc[i];
		osk_data[i].intext = intext[i];
		osk_data[i].outtextlength = TEXT_LENGTH;
		osk_data[i].outtextlimit = 25; // Limit input to 25 characters
		osk_data[i].outtext = outtext[i];
	}
	
	memset(&params, 0, sizeof(params));
	params.base.size = sizeof(params);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &params.base.language);
	sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_UNKNOWN, &params.base.buttonSwap);
	params.base.graphicsThread = 17;
	params.base.accessThread = 19;
	params.base.fontThread = 18;
	params.base.soundThread = 16;
	params.datacount = NUM_INPUT_FIELDS;
	params.data = osk_data;

	sceUtilityOskInitStart(&params);

	while(1)
	{
		switch(sceUtilityOskGetStatus())
		{
			case PSP_UTILITY_DIALOG_INIT:
				break;
			
			case PSP_UTILITY_DIALOG_VISIBLE:
				sceUtilityOskUpdate(1);
				break;
			
			case PSP_UTILITY_DIALOG_QUIT:
				sceUtilityOskShutdownStart();
				break;
			
			case PSP_UTILITY_DIALOG_FINISHED:
				break;
				
			case PSP_UTILITY_DIALOG_NONE:
				return;
				
			default :
				break;
		}

		sceDisplayWaitVblankStart();
	}
}

void highscore_read()
{     
     if(!(file = sceIoOpen("HISC.DB", PSP_O_RDONLY, 0777)))
             {
			   printf("HISC.DB could not be opened for reading!\n");
			   return;
             }
             
     for(i=1;i<=9;i++)
                       {
                            sceIoRead(file, data, 2); //pozitia
                            record[i].pos = atoi(data); //char->int
                            
                            for(sceIoRead(file, data, 1) , j=0 ; data[0] != ' ' ; sceIoRead(file, data, 1) , j++)
                                                record[i].name[j] = data[0];  //numele
                            record[i].name[j] = '\0';
                            
                            record[i].time = 0;
                            for(sceIoRead(file, data, 1) ; data[0] != '\n' ; sceIoRead(file, data, 1))
                                                record[i].time = record[i].time * 10 + atoi(data); //timpul
                       }
     sceIoClose(file);
}

void highscore_write(int x)
{
     if(!(file = sceIoOpen("HISC.DB", PSP_O_WRONLY|PSP_O_TRUNC, 0777)))
             {
               printf("HISC.DB could not be opened for writing!\n");
               return;
             }
     
     char itoa[5];
     
     for(i=1;i<x;i++)
                     {
                                      sprintf(itoa, "%d", record[i].pos);
                                      sceIoWrite(file, itoa, 1);
                                      
                                      sceIoWrite(file, " ", 1);
                                      
                                      sceIoWrite(file, record[i].name, strlen(record[i].name));
                                      
                                      sceIoWrite(file, " ", 1);
                                      
                                      sprintf(itoa, "%d", record[i].time);
                                      sceIoWrite(file, itoa, strlen(itoa));
                                      
                                      sceIoWrite(file, "\n", 1);
                     }
                     
     sprintf(itoa, "%d", x);
     sceIoWrite(file, itoa, 1);
                                      
     sceIoWrite(file, " ", 1);
     
     do
       {
                      on_screen_keyboard();
					  pspDebugScreenClear();
                      sceKernelDelayThread(1000000);
       }
     while(osk_data[0].result == PSP_UTILITY_OSK_RESULT_CANCELLED || (unsigned)osk_data[0].outtext[0] < 33 || (unsigned)osk_data[0].outtext[0] > 127);

     for(j = 0; osk_data[0].outtext[j]; j++)
		{
			unsigned c = osk_data[0].outtext[j];
			
			if(33 <= c && c <= 127) //numai ascii (mai putin space)
				{
                     char temp[2];
                     temp[0] = osk_data[0].outtext[j];
                     temp[1] = '\0';
                     sceIoWrite(file, temp, 1);
                }
		}
	if(!j)
		sceIoWrite(file, "null", 4);
		
     sceIoWrite(file, " ", 1);
                                      
     sprintf(itoa, "%d", (int)time_now);
     sceIoWrite(file, itoa, strlen(itoa));
                                      
     sceIoWrite(file, "\n", 1);
     
     for(i=x;i<=8;i++)
                        {
                            sprintf(itoa, "%d", record[i].pos + 1);
                            sceIoWrite(file, itoa, 1);
                                      
                            sceIoWrite(file, " ", 1);
                                      
                            sceIoWrite(file, record[i].name, strlen(record[i].name));
                                      
                            sceIoWrite(file, " ", 1);
                                      
                            sprintf(itoa, "%d", record[i].time);
                            sceIoWrite(file, itoa, strlen(itoa));
                                      
                            sceIoWrite(file, "\n", 1);
                        }
     sceIoClose(file);
}

void game_over()
{
	sceDisplayWaitVblankStart();
	sceGuSwapBuffers();
	sceGuClearColor(0);
	sceGuClearDepth(0);
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	
	pspDebugScreenSetOffset( (int)fbp0 );
	pspDebugScreenClear();
	
	pspDebugScreenSetXY ( 0, 0 );
    highscore_read();
    for(i=1;i<=9;i++)
                     if(time_now > record[i].time)
                                 {
                                                  print_highscore = 1;
                                                  highscore_write(i);
                                                  highscore_read();
                                                  break;
                                 }
                                 
    pspDebugScreenClear();
	pspDebugScreenSetXY ( 15, 10 );
	printf("Game Over!");
	pspDebugScreenSetXY ( 15, 12 );
	printf( "Time: %2d:%02d", (int)time_now / 60, (int)time_now % 60 );
	if(print_highscore)
	                   {
                              pspDebugScreenSetXY ( 15, 14 );
                              printf("New High-Score!!!");
                              print_highscore = 0;
                       }
	pspDebugScreenSetXY ( 32, 32 );
	printf("Copyright (c) 2010 by Iftode Bogdan");
    
    for(i=1;i<=9;i++)
                     {
                          pspDebugScreenSetXY ( 35, 2*i );
                          if(record[i].time)
                                printf("%d. %s %2d:%02d", record[i].pos, record[i].name, record[i].time / 60, record[i].time % 60);
                     }

	pspDebugScreenSetXY ( 1, 32 );
	printf("Press X to continue");
	while( 1 )
				{
					sceCtrlReadBufferPositive(&pad, 1);
			
					if (pad.Buttons != 0)
						{
							if (pad.Buttons & PSP_CTRL_CROSS)
								{
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									break;
								}
                        }
                }
	
	pspDebugScreenClear();
	init_vars();
	main_menu();
}

void init_vars()
{
	SpeedX = 0;
	SpeedY = 0;
	SpeedCircle = 0.050f;
	PlayerHP = 100;
	PlayerX = -3.80f;
	PlayerRandY = 0.00f;
	CircleX = 5.00f;
	CircleRandY = 0.00f;
	CircleRadius = 0.5f;
	menu_select = 1;
	quit_select = 2;
	debug_init = -1;
	time_now = 0;
	time_last = 0;
	InitCircle();
	sceRtcGetCurrentTick( &fpsTickLast );
}

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
	
			main_menu();
			
			sceKernelUtilsMt19937Init(&ctx, time( NULL ));
			
			dList = memalign( 16, 640 );
			fbp0  = 0;
			InitGU();
			SetupProjection();
			
			while ( 1 )
				{
					scePowerTick(6);
					DrawScene();
					MoveTriangle();
					MoveCircle();
					Collision_Detection();
					DebugMode();
					fbp0 = sceGuSwapBuffers();
				}
			sceGuTerm(); // incheie modulul grafic
			// elibereaza memoria
			free( dList );
			free( fbp0 );
		}

	sceKernelSleepThread();
	return 0;
}

