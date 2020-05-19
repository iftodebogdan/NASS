void init_vars()
{
	SpeedX = 0;
	SpeedY = 0;
	SpeedCircle = 0.050f;
	PlayerHP = 100;
	PlayerX = -3.60f;
	PlayerY = 0.00f;
	CircleX = 5.00f;
	CircleY = 0.00f;
	CircleRadius = 0.5f;
	menu_select = 1;
	quit_select = 2;
	time_now = 0;
	time_last = 0;
	fpsMode = 1;
	fpsDisplay = 0;
    RenderFreq = 1;
	InitCircle();
	sceRtcGetCurrentTick( &fpsTickLast );
}

void LoadData()
{
	dList = malloc( 262144 );
	fbp0  = 0;
	if( !ship.LoadTGA( (char*)"res/tex/ship.tga" ) )
		{
		   pspDebugScreenSetXY ( 15, 10 );
		   printf("Failed to load ship.tga");
		   sceKernelDelayThread(1000000);
		   sceKernelExitGame();
		}
	ship.Swizzle();
	
	if( !meteorite.LoadTGA( (char*)"res/tex/meteorite.tga" ) )
		{
		   pspDebugScreenSetXY ( 15, 10 );
		   printf("Failed to load meteorite.tga");
		   sceKernelDelayThread(1000000);
		   sceKernelExitGame();
		}
	meteorite.Swizzle();
	
	if( !background.LoadTGA( (char*)"res/tex/background.tga" ) )
		{
		   pspDebugScreenSetXY ( 15, 10 );
		   printf("Failed to load background.tga");
		   sceKernelDelayThread(1000000);
		   sceKernelExitGame();
		}
	background.Swizzle();
	
	if( !texture_rocket.LoadTGA( (char*)"res/tex/rocket.tga" ) )
		{
		   pspDebugScreenSetXY ( 15, 10 );
		   printf("Failed to load rocket.tga");
		   sceKernelDelayThread(1000000);
		   sceKernelExitGame();
		}
	texture_rocket.Swizzle();
}	