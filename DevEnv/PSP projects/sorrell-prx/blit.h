#ifndef __BLIT_H__
#define __BLIT_H__

#define COLOR_CYAN    0x00ffff00
#define COLOR_MAGENDA 0x00ff00ff
#define COLOR_YELLOW  0x0000ffff

#define RGB(R,G,B)    (((B)<<16)|((G)<<8)|(R))
#define RGBT(R,G,B,T) (((T)<<24)|((B)<<16)|((G)<<8)|(R))

#define CENTER(num) ((480/2)-(num*(8/2)))

static unsigned int* vram32;
int blit_setup(void);
void blit_set_color(int fg_col,int bg_col);
int blit_string(int sx,int sy,const char *msg);
int blit_string_ctr(int sy,const char *msg);

////////////////////////////////////////////////////////////////////////////
//FROM VRAM.H
#define SCREEN_WIDTH 			480
#define SCREEN_HEIGHT 			272
#define LINESIZE 512	
#define CMAX_X 60
#define CMAX_Y 38
#define	FRAME_BUFFER_WIDTH		512
#define FRAMESIZE 0xAA000			

int blit_string46(int sx,int sy,const char *msg,int fg_col,int bg_col);
u8* PixelPointer(int x,int y); 
u8 *PixelPointerFlat(); 
void PutChar(unsigned long x,unsigned long y,unsigned long color,unsigned long bgcolor,unsigned char ch,char drawfg,char drawbg,char mag);

void Print(unsigned long x,unsigned long y,unsigned long color,const char *str);
void FillRect(int x, int y, int width, int height, u32 color); 
void FillRect2(int x, int y, int width, int height, u32 color) ;
void Fillvram(u32 color) ;
void FillvramPlus(u32 color) ;

#endif
