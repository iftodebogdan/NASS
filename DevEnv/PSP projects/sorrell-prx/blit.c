/*
	PSP VSH 24bpp text bliter
*/
#include "common.h"
#include "graphics.h"
#include "blit.h"

#define ALPHA_BLEND 1

extern unsigned char msx[];



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
static int pwidth, pheight, bufferwidth, pixelformat;
//static unsigned int* vram32;
u8 *drawBuffer;

static u32 fcolor = 0x00ffffff;
static u32 bcolor = 0xff000000;

#if ALPHA_BLEND
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
static u32 adjust_alpha(u32 col)
{
	u32 alpha = col>>24;
	u8 mul;
	u32 c1,c2;

	if(alpha==0)    return col;
	if(alpha==0xff) return col;

	c1 = col & 0x00ff00ff;
	c2 = col & 0x0000ff00;
	mul = (u8)(255-alpha);
	c1 = ((c1*mul)>>8)&0x00ff00ff;
	c2 = ((c2*mul)>>8)&0x0000ff00;
	return (alpha<<24)|c1|c2;
}
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//int blit_setup(int sx,int sy,const char *msg,int fg_col,int bg_col)
int blit_setup(void)
{
	int unk;
	sceDisplayGetMode(&unk, &pwidth, &pheight);
	sceDisplayGetFrameBuf((void*)&vram32, &bufferwidth, &pixelformat, &unk);
	drawBuffer = (u8 *)vram32;
	if( (bufferwidth==0) || (pixelformat!=3)) return -1;

	fcolor = 0x00ffffff;
	bcolor = 0xff000000;

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// blit text
/////////////////////////////////////////////////////////////////////////////
void blit_set_color(int fg_col,int bg_col)
{
	fcolor = fg_col;
	bcolor = bg_col;
}

/////////////////////////////////////////////////////////////////////////////
// blit text
/////////////////////////////////////////////////////////////////////////////
int blit_string(int sx,int sy,const char *msg)
{
	int x,y,p;
	int offset;
	char code;
	unsigned char font;
	u32 fg_col,bg_col;

#if ALPHA_BLEND
	u32 col,c1,c2;
	u32 alpha;

	fg_col = adjust_alpha(fcolor);
	bg_col = adjust_alpha(bcolor);
#else
	fg_col = fcolor;
	bg_col = bcolor;
#endif

//Kprintf("MODE %d WIDTH %d\n",pixelformat,bufferwidth);
	if( (bufferwidth==0) || (pixelformat!=3)) return -1;

	for(x=0;msg[x] && x<(pwidth/8);x++)
	{
		code = msg[x] & 0x7f; // 7bit ANK
		for(y=0;y<8;y++)
		{
			offset = (sy+y)*bufferwidth + sx+x*8;
			font = y>=7 ? 0x00 : msx[ code*8 + y ];
			for(p=0;p<8;p++)
			{
#if ALPHA_BLEND
				col = (font & 0x80) ? fg_col : bg_col;
				alpha = col>>24;
				if(alpha==0) vram32[offset] = col;
				else if(alpha!=0xff)
				{
					c2 = vram32[offset];
					c1 = c2 & 0x00ff00ff;
					c2 = c2 & 0x0000ff00;
					c1 = ((c1*alpha)>>8)&0x00ff00ff;
					c2 = ((c2*alpha)>>8)&0x0000ff00;
					vram32[offset] = (col&0xffffff) + c1 + c2;
				}
#else
				vram32[offset] = (font & 0x80) ? fg_col : bg_col;
#endif
				font <<= 1;
				offset++;
			}
		}
	}
	return x;
}
/////////////////////////////////////////////////////////////////////////////
// blit text
/////////////////////////////////////////////////////////////////////////////
int blit_string46(int sx,int sy,const char *msg,int fg_col,int bg_col)
{
	int x,y,p;
	int offset;
	char code;
	unsigned char font;
	int pwidth, pheight, bufferwidth, pixelformat, unk;
	unsigned int* vram32;

//	int unk;
	sceDisplayGetMode(&unk, &pwidth, &pheight);
	sceDisplayGetFrameBuf((void*)&vram32, &bufferwidth, &pixelformat, &unk);

	if( (bufferwidth==0) || (pixelformat!=3)) return -1;

	for(x=0;msg[x] && x<(pwidth/8);x++)
	{
		code = msg[x] & 0x7f; // 7bit ANK
		for(y=0;y<8;y++)
		{
			offset = (sy+y)*bufferwidth + (sx+x)*8;
			font = msx[ code*8 + y ];
			for(p=0;p<8;p++)
			{
				vram32[offset] = (font & 0x80) ? fg_col : bg_col;
				font <<= 1;
				offset++;
			}
		}
	}
	return x;
}
///CAP OFFSCREEN
int blit_string_ctr(int sy,const char *msg)
{
	int sx = 480/2-strlen(msg)*(8/2);
	return blit_string(sx,sy,msg);
}

///////////////////////////////////////////////////////////////////////////////////////
////////VRAM.C
///////////////////////////////////////////////////////////////////////////////////////
unsigned char *vramtop=(unsigned char *)0x04000000;
unsigned long drawframe;

char *pg_vramtop=(char *)0x44000000;
int fbp = 0;

u32* pVRAM ;//= (u32*)(0x04000000+0x40000000);	
u32* pBufferPointer[2];

u8* PixelPointer(int x,int y) {
	return (u8 *)vram32+(x+y*512)*4;//+0x04000000 //drawBuffer+(x+y*512)*4;//+0x04000000
}

u8 *PixelPointerFlat() {
	return (u8 *) vram32;//drawBuffer;//+0x04000000;
}

/*void GetpVRAM(int x , int y) {
	return (u8 *) drawBuffer+0x04000000+(x+y*512)*4;//(u32 *)vramtop+(drawframe?512*272*4:0);  
}*/
/*
// get vram address for character position
unsigned char *Getfbp1Addr(unsigned long x,unsigned long y) {
	return vramtop+(drawframe?512*272*4:0)+x*4+y*LINESIZE*4;  
}
*/

// print a single character
void PutChar(unsigned long x,unsigned long y,unsigned long color,unsigned long bgcolor,unsigned char ch,char drawfg,char drawbg,char mag)
{


	unsigned char *vptr0;		//pointer to vram
	unsigned char *vptr;		//pointer to vram
	const unsigned char *cfont;		//pointer to font
	unsigned long cx,cy;
	unsigned long b;
	char mx,my;

	cfont=msx+ch*8;

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
	p = vram32;//(u32 *)vptr0;
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
	vptr0 += x + FRAME_BUFFER_WIDTH + SCREEN_WIDTH - y - height ;
	int i, j;
	p = vram32+x + FRAME_BUFFER_WIDTH + SCREEN_WIDTH - y - height ;//(u32 *)vptr0;
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

void FillvramPlus(u32 color) {


	Color *vptr0;		//pointer to vram
	unsigned long i;

//	vptr0=getVramDisplayBuffer();
//	for(i=0; i<FRAMEBUFFER_SIZE/sizeof(Color); i++) {
	vptr0=PixelPointerFlat;
	for(i=0; i<(FRAMESIZE/4)*2; i++) {
		*vptr0 += color;
		vptr0++;
	}
}
