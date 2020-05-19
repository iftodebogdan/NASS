/*
 * Uht header class
 * Coded by mcidclan. April 2010
 * m.cid.clan@gmail.com
 *
 */

#define H_CAMSTREAMER
#define UHT_NECESSARY_H

#define YCBCR_RESTRICTIVE_THRESH 0
#define YCBCR_APPROPRIATE_THRESH 1
#define YCBCR_PERMISSIVE_THRESH 2

#define WW 160
#define HH 120

#define MAX_VIDEO_FRAME_SIZE (1024*34)

#include <psppower.h>
#include <psputility_usbmodules.h>
#include <psputility_avmodules.h>
#include <pspusb.h>
#include <pspusbacc.h>
#include <pspusbcam.h>
#include <pspjpeg.h>
#include <pspkernel.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

static const u32 SIZE_FBu8  = WW*HH;
static const u32 SIZE_FBu16 = SIZE_FBu8*2;
static const u32 SIZE_FBu32 = SIZE_FBu16*2;

typedef struct vec2i{
	int x, y;
} vec2i;

typedef struct vec3i{
	int x, y, z;
} vec3i;

typedef struct vec4i{
	int x, y, z, w;
} vec4i;

void getAbsPosition(const vec4i in, vec2i *out);
void getOrtPosition(const vec4i in, vec2i *out);

void getSqrDimension(const vec4i sqr, vec2i *out);
//float evalOpnHand(const vec4i sqr, u8 *buf);
float evalStdHand(const vec4i sqr);

class Uht{

	public:

	vec4i pOut;

	u32 *FB_MPEG;
	u32 *FB_8888;
	u16 *FB_565;
	u8 *B_WORK;

	bool run;
	bool direction;
	bool checkAmbientLight; 
	bool relativeClean;

	int thid;

	static Uht * myUhtPt;
	static int video_thread(SceSize args, void *argp);

	Uht();
	int initCam(const u8 prop = 0x10);
	void setGrid(const u8 gSize, vec3i *grids);
	void initBuffer(void *bWork, const bool dRender, const bool fb565);

	void setYcbcrThresh(u8 threshNum);

	void setMinDim(const u8 xMin, const u8 yMin);
	void setMaxMrg(const u8 xMrg, const u8 yMrg);
	
	void fm_activated();
	bool fm_isWaiting();
	void fm_nextFrame();

	~Uht();

	private:
	//Driver buffer workplace
	u8  work[1024*68] __attribute__((aligned(64)));
	//Frame jpeg buffer
	u8  buffer[MAX_VIDEO_FRAME_SIZE] __attribute__((aligned(64)));
};
