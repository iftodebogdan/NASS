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
	sceGuEnable( GU_TEXTURE_2D );
	sceGuTexMode( GU_PSM_8888, 0, 0, ship.Swizzled() );	
	sceGuTexMode( GU_PSM_8888, 0, 0, meteorite.Swizzled() );
	sceGuTexMode( GU_PSM_8888, 0, 0, background.Swizzled() );
	sceGuTexMode( GU_PSM_8888, 0, 0, texture_rocket.Swizzled() );
    sceGuTexFunc( GU_TFX_DECAL, GU_TCC_RGB );
	sceGuTexFilter( GU_LINEAR, GU_LINEAR );
	sceGuTexScale( 1.0f, 1.0f );
	sceGuTexOffset( 0.0f, 0.0f );
	//sceGuAlphaFunc(GU_GEQUAL, 1.0f, 0xff);
    //sceGuEnable(GU_ALPHA_TEST);
    //sceGuEnable(GU_BLEND);
    //sceGuBlendFunc(GU_MAX, GU_SRC_COLOR, GU_DST_COLOR, 0, 0);
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
	for(i=0;i<=119;i++)
		{
			//coordonatele X
			circle[i].x = CircleRadius * sin(3*i);
			
			//coordonatele Y
			circle[i].y = CircleRadius * cos(3*i);
			
			//culoarea
			//circle[i].color = GU_COLOR( 1.0f, 1.0f, 1.0f, 1.0f );
			
			//textura
			circle[i].u = 0.5f * sin(3*i) + 0.5f;
			circle[i].v = 0.5f * cos(3*i) + 0.5f;
		}
}

void DrawScene( void )
{
	sceGuStart( GU_DIRECT, dList );
	
	// clr scr
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	sceGumMatrixMode(GU_MODEL);
    
	//deseneaza background1
	sceGumLoadIdentity();
	{
	ScePspFVector3 move = { BackgroundX, 0.0f, -4.0f };
	sceGumTranslate( &move );
	}
	
    //sceGuEnable(GU_TEXTURE_2D);
	sceGuTexImage( 0, background.Width(), background.Height(), background.Width(), background.Image() ); 
	sceGumDrawArray( GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,
			4, 0, quad );
	//sceGuDisable(GU_TEXTURE_2D);
	
	//deseneaza background2
	sceGumLoadIdentity();
	{
	ScePspFVector3 move = { BackgroundX + mod * 12.0f, 0.0f, -4.0f };
	sceGumTranslate( &move );
	}

    //sceGuEnable(GU_TEXTURE_2D);
	sceGuTexImage( 0, background.Width(), background.Height(), background.Width(), background.Image() ); 
	sceGumDrawArray( GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,
			4, 0, quad );
	//sceGuDisable(GU_TEXTURE_2D);

	//deseneaza triunghi
	sceGumLoadIdentity();
	{
	ScePspFVector3 move = { PlayerX, PlayerY, -3.0f };
	sceGumTranslate( &move );
	}
	
    //sceGuEnable(GU_TEXTURE_2D);
	sceGuTexImage( 0, ship.Width(), ship.Height(), ship.Width(), ship.Image() ); 
	sceGumDrawArray( GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,
			5, 0, triangle );
	//sceGuDisable(GU_TEXTURE_2D);
	
	//deseneaza cerc
	if( RenderCircle )
	    {
                     sceGumLoadIdentity();
	                 {
	                 ScePspFVector3 move = { CircleX, CircleY, -3.0f };
	                 sceGumTranslate( &move );
                     }
	
	                 //sceGuEnable(GU_TEXTURE_2D);
                     sceGuTexImage( 0, meteorite.Width(), meteorite.Height(), meteorite.Width(), meteorite.Image() ); 
	                 sceGumDrawArray( GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,
	                 120, 0, circle );
	                 //sceGuDisable(GU_TEXTURE_2D);
        }
	
	//deseneaza racheta
	if( RocketFired )
	    {
        	sceGumLoadIdentity();
            ScePspFVector3 move = { RocketX, RocketY, -3.1f };
            sceGumTranslate( &move );
  	        
       	   	//sceGuEnable(GU_TEXTURE_2D);
            sceGuTexImage( 0, texture_rocket.Width(), texture_rocket.Height(), texture_rocket.Width(), texture_rocket.Image() ); 
            sceGumDrawArray( GU_TRIANGLE_FAN, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF|GU_TRANSFORM_3D,
	        4, 0, rocket );
	        //sceGuDisable(GU_TEXTURE_2D);
        }
	
	sceGuFinish();
	sceGuSync(0,0);
}
