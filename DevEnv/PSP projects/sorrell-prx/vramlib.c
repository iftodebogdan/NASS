/*
Hello World v1 for PSP v2.0
(w) 24/09/2005 by Groepaz/Hitmen
http://www.hitmen-console.org

greets to Skylark, Niacin, Skywalker, xor37h, Tyranid

this is a simple example on how to use the C compiler from pspsdk for creating 
a binary that works with the exploit/loader released by someone else the other day.

its VERY basic, some C features will not work, C++ most definetly wont. you will need
to call syscalls directly (not via kernel stubs/NIDs). your program can be max 64k big.

*/
#include <stdlib.h>
#include <pspkernel.h>
#include <stdio.h>


#include <stdlib.h>
#include <pspdisplay.h>
#include <pspdebug.h> 
#include <pspctrl.h>
#include <time.h>
#include <pspaudiolib.h>

#include <math.h>
#include "main.h"
#include "vramlib.h"
#include "graphics.h"
#include "font.h"

unsigned char *vramtop=(unsigned char *)0x04000000;
unsigned long drawframe;

char *pg_vramtop=(char *)0x44000000;
int fbp = 0;

u8 *drawBuffer;
u32* pVRAM ;//= (u32*)(0x04000000+0x40000000);	
u32* pBufferPointer[2];

u8* PixelPointer(int x,int y) {
	return (u8 *) drawBuffer+0x04000000+(x+y*512)*4;
}

u8 *PixelPointerFlat() {
	return (u8 *) drawBuffer+0x04000000;
}


/*void GetpVRAM(int x , int y) {
	return (u8 *) drawBuffer+0x04000000+(x+y*512)*4;//(u32 *)vramtop+(drawframe?512*272*4:0);  
}*/

// get vram address for character position
unsigned char *Getfbp1Addr(unsigned long x,unsigned long y) {
	return vramtop+(drawframe?512*272*4:0)+x*4+y*LINESIZE*4;  
}

// print a single character
void PutChar(unsigned long x,unsigned long y,unsigned long color,unsigned long bgcolor,unsigned char ch,char drawfg,char drawbg,char mag)
{
	unsigned char *vptr0;		//pointer to vram
	unsigned char *vptr;		//pointer to vram
	const unsigned char *cfont;		//pointer to font
	unsigned long cx,cy;
	unsigned long b;
	char mx,my;

	cfont=font+ch*8;

	//vptr0=GetVramAddr(x,y);
	vptr0=PixelPointer(x,y);

	for (cy=0; cy<8; cy++) {
		for (my=0; my<mag; my++) {
			vptr=vptr0;
			b=0x80;
			for (cx=0; cx<8; cx++) {
				for (mx=0; mx<mag; mx++) {
					if ((*cfont&b)!=0) {
						if (drawfg) *(unsigned long *)vptr=color;
					} else {
						//if (drawbg) *(unsigned long *)vptr=bgcolor;
					}
					vptr+=4; // PIXELSIZE*2;
				}
				b=b>>1;
			}
			vptr0+=LINESIZE*4; // 2
		}
		cfont++;
	}
}

// print a string
void Print(unsigned long x,unsigned long y,unsigned long color,const char *str) {
	while (*str!=0 && x<CMAX_X && y<CMAX_Y) {
		PutChar(x*8,y*8,color,0,*str,1,1,1);
		str++;
		x++;
		if (x>=CMAX_X) {
			x=0;
			y++;
		}
	}
}

// ------------------------------------------------------------------------
// Fill a rectangular area with a specific color on screen without boundary check
// ------------------------------------------------------------------------
void FillRect(int x, int y, int width, int height, u32 color) {
	// get starting addr of the 1st pixel
	//       = pVRAM + y * FRAME_BUFFER_WIDTH + x;
	unsigned char *vptr0 = (unsigned char *)PixelPointer(FRAME_BUFFER_WIDTH + x,y); 
	u32* p ;
	int i, j;
	p = (u32 *)vptr0;
	for (j=0; j<height; j++) {
		for (i=0; i<width; i++)         // plot one row
			*(unsigned long *)(p+i) += color;
		p += FRAME_BUFFER_WIDTH;        // move pointer to the next row
	}       
}

//-----------------------------------------------------------------------------------
// Fill a rectangular area with a specific color on screen rotated 90 degree without boundary check 
//-----------------------------------------------------------------------------------
void FillRect2(int x, int y, int width, int height, u32 color) {
	unsigned char *vptr0; 
	u32* p; 
	// get starting addr of the 1st pixel
	vptr0  = (unsigned char *)PixelPointerFlat();
	vptr0 += x,FRAME_BUFFER_WIDTH + SCREEN_WIDTH - y - height ;
	int i, j;
	p = (u32 *)vptr0;
	for (j=0; j<width; j++) {
		for (i=0; i<height; i++)       
			*(unsigned long *)(p+i) += color;
		p += FRAME_BUFFER_WIDTH;        // move pointer to the next row
	}
}

// clear video ram
void Fillvram(Color color) {
	Color *vptr0;		//pointer to vram
	unsigned long i;

//	vptr0=getVramDisplayBuffer();
//	for(i=0; i<FRAMEBUFFER_SIZE/sizeof(Color); i++) {
	vptr0=PixelPointerFlat;
	for(i=0; i<(FRAMESIZE/4)*2; i++) {
		*vptr0=color;
		vptr0++;
	}
}
