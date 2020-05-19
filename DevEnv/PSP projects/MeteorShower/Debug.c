void DebugMode()
{
	pspDebugScreenSetOffset( (int)fbp0 );
	pspDebugScreenSetXY( 1, 1 );
	printf( "HP: %1.0f %c", PlayerHP , 37 );
	
	sceRtcGetCurrentTick( &fpsTickNow );
	fps++;
	if( (fpsTickNow - fpsTickLast) /  (float)sceRtcGetTickResolution() >= 1 )
		{
			time_now++;
			Score += 10;
			fpsTickLast = fpsTickNow;
			fpsDisplay = fps;
			fps = 0;
		}
	
	pspDebugScreenSetXY( 55, 1 );
	printf( "FPS: %2d f/s", fpsDisplay );
	pspDebugScreenSetXY( 55, 2 );
	printf( "Time: %2d:%02d", (int)time_now / 60, (int)time_now % 60 );
	pspDebugScreenSetXY( 55, 3 );
	printf( "Score: %5d", Score );
	
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
			printf( "PlayerY: %f u.m.", PlayerY );
			pspDebugScreenSetXY( 1, 5 );
			printf( "SpeedX: %f u.m./s", SpeedX );
			pspDebugScreenSetXY( 1, 6 );
			printf( "SpeedY: %f u.m./s", SpeedY );
			pspDebugScreenSetXY( 1, 7 );
			printf( "CircleX: %f u.m.", CircleX );
			pspDebugScreenSetXY( 1, 8 );
		    printf( "CircleY: %f u.m.", CircleY );
			pspDebugScreenSetXY( 1, 9 );
			printf( "CircleRadius: %f u.m.", CircleRadius );
			pspDebugScreenSetXY( 1, 10 );
			printf( "SpeedCircle: %f u.m./s", SpeedCircle * 60 );
			pspDebugScreenSetXY( 1, 11 );
			printf( "Distance: %f u.m.", distance );
            pspDebugScreenSetXY( 1, 12 );
			printf( "HPRM input: %x", (unsigned int)HPRM_input );
			pspDebugScreenSetXY( 1, 13 );
			printf( "Camera input Y: %3d", myUht->pOut.z );
		}
	if(time_now - time_last <= 5)
				{
					if( debug_init == 1 )
						pspDebugScreenSetXY( 1, 15 );
					else pspDebugScreenSetXY( 1, 2 );
                    printf( "Press SQUARE to enable/disable Debug Mode" );
                    if( debug_init == 1 )
    					pspDebugScreenSetXY( 1, 16 );
					else pspDebugScreenSetXY( 1, 3 );
                    printf( "Press TRIANGLE to invert HPRM input" );
                    if( debug_init == 1 )
						pspDebugScreenSetXY( 1, 17 );
					else pspDebugScreenSetXY( 1, 4 );
					printf( "Press D-Pad <- or -> to change FPS Mode" );
					pspDebugScreenSetXY( 55, 4 );
	                printf( "FPS Mode %d", fpsMode);
	                if( debug_init == 1 )
						pspDebugScreenSetXY( 1, 18 );
					else pspDebugScreenSetXY( 1, 5 );
					printf( "Press CIRCLE to enable/disable Camera Tracking" );
				}
	pspDebugScreenSetXY ( 1, 32 );
	printf("Press START to quit");
	pspDebugScreenSetXY ( 32, 32 );
}