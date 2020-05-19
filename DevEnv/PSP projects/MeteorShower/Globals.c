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
#include <pspaudio.h>//*
#include <pspmp3.h>//*
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include "TGALoader.h"
#include "uht.cpp"
#include <oslib/oslib.h>

#define NUM_INPUT_FIELDS	(1)
#define TEXT_LENGTH			(25)

#define BUF_WIDTH (512)
#define SCR_WIDTH (479)
#define SCR_HEIGHT (271)

PSP_MODULE_INFO("Meteor_Shower_v0.6",0,1,1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER); //*
PSP_HEAP_SIZE_KB(-1024);//*

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

//Functii pentru grafica:
void InitGU( void );			        // Initializeaza sistemul grafic
void SetupProjection( void );	        // Initiaza matricea de proiectie
void DrawScene( void );			        // Deseneaza pe ecran

void quit_menu();
void init_vars();
void game_over();
void DebugMode();
void show_highscore();
time_t time ( time_t * timer );         // ***** hard fix - nu mai apare warning la compilare (a se verifica cauza)
//sfarsit functii

//declarare variabile
void *dList;		// display List, folosit de sceGUStart
void *fbp0;		// frame buffer

int fps = 0;		// variabile pentru calcularea FPS-ului
int fpsDisplay = 0;
int fpsMode = 1;
int RenderFreq = 1;
u32 tickResolution;
u32 HPRM_input = -1;
u64 fpsTickNow;
u64 fpsTickLast;

SceCtrlData pad;	// variabila pentru citirea tastelor
float SpeedX = 0;	//variabile pentru miscarea obiectului pe axele X si Y
float SpeedY = 0;
float SpeedCircle = 0.050f;
float PlayerHP = 100, PlayerX = -3.60f, PlayerY = 0.00f, 
      CircleX = 5.00f, CircleY = 0.00f, 
      CircleRadius = 0.5f, RenderCircle = 1,
      RocketX, RocketY, RocketFired = 0,
      BackgroundX = 0.0f, mod = 1,
      menu_select = 1, quit_select = 2, debug_init = -1, useCam = -1,
      HPRM_inv = 1, distance;
float time_now = 0,time_last = 0;

SceKernelUtilsMt19937Context ctx;
int low = -200, high = 200;
u32 rand_val;

SceUID file;
int j,print_highscore=0;
char data[5];
struct rec
      {
             int pos;
             char name[26];
             int score;
      } record[10];

unsigned short intext[NUM_INPUT_FIELDS][TEXT_LENGTH];
unsigned short outtext[NUM_INPUT_FIELDS][TEXT_LENGTH];
unsigned short desc[NUM_INPUT_FIELDS][TEXT_LENGTH];
SceUtilityOskData osk_data[NUM_INPUT_FIELDS];
SceUtilityOskParams params;

typedef struct {
    float u, v;
	unsigned int color;
	float x, y, z;
} Vertex;

CTGATexture ship, meteorite, background, texture_rocket;

Vertex __attribute__((aligned(16))) triangle[6] = 
{
       //jos
    { 0.4f, 0, GU_COLOR( 1.0f, 0.0f, 0.0f, 1.0f ),  -0.1f, -0.5f, 0.0f },
	{ 0, 0, GU_COLOR( 1.0f, 0.0f, 0.0f, 1.0f ),  -0.5f, -0.5f, 0.0f },
	
	  //sus
    { 0, 1, GU_COLOR( 1.0f, 0.0f, 0.0f, 1.0f ),  -0.5f, 0.5f, 0.0f },
    { 0.4f, 1, GU_COLOR( 1.0f, 0.0f, 0.0f, 1.0f ),  -0.1f, 0.5f, 0.0f },
	
	  //varf
    { 0.9f, 0.5f, GU_COLOR( 1.0f, 0.0f, 0.0f, 1.0f ),  0.4f, 0, 0.0f }
};

Vertex __attribute__((aligned(16))) circle[120];

Vertex __attribute__((aligned(16))) quad[4] = 
{
	{ 0, 0, GU_COLOR( 0.0f, 0.0f, 1.0f, 1.0f ), -6, -6, 0.0f },
	{ 0, 1, GU_COLOR( 0.0f, 0.0f, 1.0f, 1.0f ), -6,  6, 0.0f },
	{ 1, 1, GU_COLOR( 0.0f, 0.0f, 1.0f, 1.0f ),  6,  6, 0.0f },
	{ 1, 0, GU_COLOR( 0.0f, 0.0f, 1.0f, 1.0f ),  6, -6, 0.0f }
};

Vertex __attribute__((aligned(16))) rocket[4] =
{
    { 0, 0, GU_COLOR( 1.0f, 0.0f, 0.0f, 1.0f ), -0.4f, -0.2f, 0.0f },
	{ 0, 1, GU_COLOR( 0.0f, 0.0f, 1.0f, 1.0f ), -0.4f,  0.2f, 0.0f },
	{ 1, 1, GU_COLOR( 0.0f, 0.0f, 1.0f, 1.0f ),  0.4f,  0.2f, 0.0f },
	{ 1, 0, GU_COLOR( 0.0f, 0.0f, 1.0f, 1.0f ),  0.4f, -0.2f, 0.0f }
};

OSL_SOUND *BGM, *SFXNavigate, *SFXConfirm, *SFXNavigateErr, *SFXComet, *SFXExplosion, *SFXLaunch, *SFXDamage;

int sfx_flag = 1, Score = 0;
//sfarsit declarare variabile
