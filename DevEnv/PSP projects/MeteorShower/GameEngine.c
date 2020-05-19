void MoveTriangle()
{	
	sceCtrlReadBufferPositive(&pad, 1);
    
    //control de pe analog
	SpeedX = ( (float)pad.Lx - ( 255 / 2 ) ) / 2000;
	SpeedY = -1 * ( ( (float)pad.Ly - ( 255 / 2 ) ) / 2000 );
		
	//control de pe telecomanda
	if( (sceHprmIsRemoteExist() && (int)HPRM_input == -1) || (!sceHprmIsRemoteExist() && (int)HPRM_input != -1) )
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
                                            if( !RocketFired )
                                                {
                                                             RocketX = PlayerX;
                                                             RocketY = PlayerY;
                                                             RocketFired = 1;
                                                }
                                   }
        }
    else HPRM_input = -1;
     
    //control folosind camera
    if( useCam == 1 )
         {
                TrackCamera();
                
                int CoordY = myUht->pOut.z;
                if( CoordY >= 10 && CoordY <= 110 )
                    {
                           CoordY = CoordY / 10 - 6;
                           PlayerY = 1.8f * ( (float)CoordY / -5 );
                    }
         }
                
                
	if( SpeedY >= 0.01f || SpeedY <= -0.01f )
		{
			if( PlayerY > 1.8f && SpeedY < 0 )
				PlayerY += SpeedY;
			if( PlayerY < -1.8f && SpeedY > 0 )
				PlayerY += SpeedY;
			if( PlayerY <= 1.8f && PlayerY >= -1.8f )
				PlayerY += SpeedY;
		}

	//alte optiuni
	if( pad.Buttons != 0 )
		{
			if (pad.Buttons & PSP_CTRL_START)
				{
					oslPlaySound(SFXConfirm, 1);
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
			if(pad.Buttons & PSP_CTRL_CIRCLE)
						{
							while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
							useCam *= (-1);
							time_last = time_now;
						}
			if(pad.Buttons & PSP_CTRL_LEFT)
			       if(fpsMode > 1)
			            {
                            while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
                            fpsMode--;
                            time_last = time_now;
                        }
            if(pad.Buttons & PSP_CTRL_RIGHT)
                   if(fpsMode < 4)
                        {
                            while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
                            fpsMode++;
                            time_last = time_now;
                        }
            if(pad.Buttons & PSP_CTRL_CROSS)
                           if( !RocketFired )
                               {
                                            RocketX = PlayerX;
                                            RocketY = PlayerY;
                                            RocketFired = 1;
											Score -= 10;
											oslPlaySound(SFXLaunch, 2);
                               }
		}
}

void MoveCircle()
{
	if( CircleX < -4.50f )
		{
			oslPlaySound(SFXComet, 3);
			CircleX = 5.00f;
			SpeedCircle += 0.001f;
			
            rand_val = sceKernelUtilsMt19937UInt(&ctx);
            rand_val = low + rand_val % (high-low);
			
			CircleY = (float)( (int)rand_val ) / 100;
			
			RenderCircle = 1;
		}
	else CircleX -= SpeedCircle;
}

void MoveBackground()
{
     if( BackgroundX <= -12.00f )
         {
                     BackgroundX = 12.00f;
                     mod = -1;
         }
     else if( BackgroundX <= 0.50f )
              mod = 1;
              
     BackgroundX -= 0.01f;
}

void MoveRocket()
{
            if( RocketX >= 5.00f )
                RocketFired = 0;
            else RocketX += 0.1f;
}

void Collision_Detection()
{
	distance = sqrt( pow( CircleX - PlayerX , 2 ) + pow( CircleY - PlayerY , 2 ) );
	if( ( distance <= CircleRadius + 0.4f || ( PlayerX >= CircleX && abs( PlayerY - CircleY ) < 1.0f ) ) && RenderCircle ) //0.288f
		{
            RocketFired = 0;
			if(sfx_flag)
				{
					oslPlaySound(SFXDamage, 4);
					sfx_flag = 0;
				}
            
			if( PlayerHP > 10 * SpeedCircle )
					PlayerHP -= 10 * SpeedCircle;
			else PlayerHP = 0;
			sceKernelDelayThread( 1000000 / 30 );
			if( PlayerHP == 0 )
				{
                    fbp0 = sceGuSwapBuffers();
                    DrawScene();
					DebugMode();
					sceKernelDelayThread( 2 * 1000000 );
					game_over();
				}
		}
	else
		sfx_flag = 1;
		
	if( RocketFired && RenderCircle )
        {
         distance = sqrt( pow( CircleX - RocketX , 2 ) + pow( CircleY - RocketY , 2 ) );
         if( distance <= CircleRadius )
             {
				 oslPlaySound(SFXExplosion, 5);
                 RenderCircle = 0;
                 RocketFired = 0;
				 Score += 50;
                 if( PlayerHP + 5 >= 100)
                     PlayerHP = 100;
                 else PlayerHP += 5;
             }
         }
}
