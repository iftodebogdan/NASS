#include "uht.h"

 u32* B_Text;
 u32* B_Fram;
void* B_Trac;

void* trac_Mem;
void* rend_Mem;
void* text_Mem;

Uht *myUht;

void InitCamera()
{
    //Direct Render 0x22240 else 0x34E40
	trac_Mem = memalign(64, 0x34E40);
	rend_Mem = memalign(16, 3*1024*1024);
	text_Mem = memalign(32, 512*274*4);
    	
	myUht = new Uht();
	myUht->fm_activated();
	myUht->initBuffer(trac_Mem, false, false);

	vec3i *grid = new vec3i[1];
	grid[0].x = 10; grid[0].y = 10; grid[0].z = 40;
	myUht->setGrid(1, grid);

	myUht->setMinDim(20, 20);
	myUht->checkAmbientLight = true;

	myUht->initCam();
}

void TrackCamera()
{
		if(myUht->fm_isWaiting())
        {
        		sceGuCopyImage(GU_PSM_8888,0,0,WW,HH,WW,
		        (void*)myUht->FB_MPEG,0,0,WW, (void*)B_Fram);

                      /*
                      printf("%3d %3d %3d %3d",
			          myUht->pOut.x, myUht->pOut.y, myUht->pOut.z, myUht->pOut.w);
                      */
                      
			    myUht->fm_nextFrame();
		}
}
