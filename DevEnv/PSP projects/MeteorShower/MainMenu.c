void main_menu()
{
	while( 1 )
		{            
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
			
			pspDebugScreenSetXY ( 2, 4 );
			if( menu_select == 3 ) printf( "->" );
			else printf( "  " );
			printf( "Use Go!Cam          " );
			if( useCam == 1 ) printf( "Enabled  " );
			if( useCam == -1 ) printf( "Disabled" );
            
            pspDebugScreenSetXY ( 2, 5 );
			if( menu_select == 4 ) printf( "->" );
			else printf( "  " );
			printf( "HPRM inverse        " );
            if( HPRM_inv == 1 ) printf( "PREV - move up  &  NEXT - move down" );
			if( HPRM_inv == -1 ) printf( "NEXT - move up  &  PREV - move down" );
			
			pspDebugScreenSetXY ( 2, 6 );
			if( menu_select == 5 ) printf( "->" );
			else printf( "  " );
			printf( "Highscores" );
			
			pspDebugScreenSetXY ( 2, 7 );
			if( menu_select == 6 ) printf( "->" );
			else printf( "  " );
			printf( "Exit" );
	
			pspDebugScreenSetXY ( 32, 32 );


					sceCtrlReadBufferPositive(&pad, 1);
			
					if (pad.Buttons != 0)
						{
							if (pad.Buttons & PSP_CTRL_UP)
								{
									if( menu_select > 1 )
										{
											menu_select--;
											oslPlaySound(SFXNavigate, 1);
										}
									else
										oslPlaySound(SFXNavigateErr, 1);
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									//break;
								} 
							if (pad.Buttons & PSP_CTRL_DOWN)
								{
									if( menu_select < 6 )
										{
											menu_select++;
											oslPlaySound(SFXNavigate, 1);
										}
									else
										oslPlaySound(SFXNavigateErr, 1);
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									//break;
								}
							if (pad.Buttons & PSP_CTRL_CROSS)
								{
									oslPlaySound(SFXConfirm, 1);
									if( menu_select == 1 )
										{
											while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											Score = 0;
											return;
										}
									if( menu_select == 2 )
										{
											debug_init *= (-1);
											time_last = time_now;
											while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											//break;
										}
									if( menu_select == 3 )
										{
											useCam *= (-1);
											while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											//break;
										}
									if( menu_select == 4 )
										         {
										         	HPRM_inv *= (-1);
									                while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											        //break;
										         }
	                                if( menu_select == 5 )
										         {
			                                        while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											        show_highscore();
											        return;
										         }
									if( menu_select == 6 )
										         {
			                                        while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											        sceKernelExitGame();
											        return;
										         }
								}
						}
					sceDisplayWaitVblankStart();
		}
}

void quit_menu()
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
			
			while( 1 )
				{
					sceCtrlReadBufferPositive(&pad, 1);
			
					if (pad.Buttons != 0)
						{
							if (pad.Buttons & PSP_CTRL_LEFT)
								{
									if( quit_select == 2 )
										{
											quit_select--;
											oslPlaySound(SFXNavigate, 1);
										}
									else
										oslPlaySound(SFXNavigateErr, 1);
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									break;
								}
							if (pad.Buttons & PSP_CTRL_RIGHT)
								{
									if( quit_select == 1 )
										{
											quit_select++;
											oslPlaySound(SFXNavigate, 1);
										}
									else
										oslPlaySound(SFXNavigateErr, 1);
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									break;
								}
							if (pad.Buttons & PSP_CTRL_CROSS)
								{
									oslPlaySound(SFXConfirm, 1);
									if( quit_select == 1 )
										{
											while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											init_vars();
											main_menu();
										}
									if( quit_select == 2 )
										{
											while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
											return;
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
     int i;
      
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
                            
                            record[i].score = 0;
                            for(sceIoRead(file, data, 1) ; data[0] != '\n' ; sceIoRead(file, data, 1))
                                                record[i].score = record[i].score * 10 + atoi(data); //timpul
                       }
     sceIoClose(file);
}

void highscore_write(int x)
{
     int i;
     
     do
       {
                      on_screen_keyboard();
                      sceKernelDelayThread(1000000);
       }
     while(osk_data[0].result == PSP_UTILITY_OSK_RESULT_CANCELLED);
     
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
                                      
                                      sprintf(itoa, "%d", record[i].score);
                                      sceIoWrite(file, itoa, strlen(itoa));
                                      
                                      sceIoWrite(file, "\n", 1);
                     }
                     
     sprintf(itoa, "%d", x);
     sceIoWrite(file, itoa, 1);
                                      
     sceIoWrite(file, " ", 1);
     
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
                                      
     sceIoWrite(file, " ", 1);
                                      
     sprintf(itoa, "%d", Score);
     sceIoWrite(file, itoa, strlen(itoa));
                                      
     sceIoWrite(file, "\n", 1);
     
     for(i=x;i<=8;i++)
                        {
                            sprintf(itoa, "%d", record[i].pos + 1);
                            sceIoWrite(file, itoa, 1);
                                      
                            sceIoWrite(file, " ", 1);
                                      
                            sceIoWrite(file, record[i].name, strlen(record[i].name));
                                      
                            sceIoWrite(file, " ", 1);
                                      
                            sprintf(itoa, "%d", record[i].score);
                            sceIoWrite(file, itoa, strlen(itoa));
                                      
                            sceIoWrite(file, "\n", 1);
                        }
     sceIoClose(file);
}

void game_over()
{
    int i;
     
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
                     if(Score > record[i].score)
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
	printf( "Score: %d", Score );
	if(print_highscore)
	                   {
                              pspDebugScreenSetXY ( 15, 14 );
                              printf("New High-Score!!!");
                              print_highscore = 0;
                       }
	pspDebugScreenSetXY ( 32, 32 );
    
    for(i=1;i<=9;i++)
                     {
                          pspDebugScreenSetXY ( 35, 2*i );
                          if(record[i].score)
                                printf("%d. %s %d", record[i].pos, record[i].name, record[i].score);
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
									oslPlaySound(SFXConfirm, 1);
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									break;
								}
                        }
                }
	
	pspDebugScreenClear();
	init_vars();
	main_menu();
}

void show_highscore()
{
    int i;
	
	pspDebugScreenClear();
	
	pspDebugScreenSetXY ( 0, 0 );
    highscore_read();

    pspDebugScreenClear();
	pspDebugScreenSetXY ( 32, 32 );
    
    for(i=1;i<=9;i++)
                     {
                          pspDebugScreenSetXY ( 35, 2*i );
                          if(record[i].score)
                                printf("%d. %s %d", record[i].pos, record[i].name, record[i].score);
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
									oslPlaySound(SFXConfirm, 1);
									while ( pad.Buttons != 0 ) sceCtrlReadBufferPositive(&pad, 1);
									break;
								}
                        }
                }
	
	pspDebugScreenClear();
	init_vars();
	main_menu();
}