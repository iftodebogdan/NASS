#include <stdlib.h>
#include <malloc.h>
#include <pspdisplay.h>
#include <psputils.h>
#include <png.h>
#include <pspgu.h>

#include <jpeglib.h>
#include <jerror.h>

#include "graphics.h"
#include "blit.h"

#define IS_ALPHA(color) (((color)&0xff000000)==0xff000000?0:1)
#define FRAMEBUFFER_SIZE (PSP_LINE_SIZE*SCREEN_HEIGHT*4)
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))



extern u8 msx[];

//unsigned int __attribute__((aligned(16))) list[262144];
static int dispBufferNumber;
static int initialized = 0;

static int getNextPower2(int width)
{
	int b = width;
	int n;
	for (n = 0; b != 0; n++) b >>= 1;
	b = 1 << n;
	if (b == 2 * width) b >>= 1;
	return b;
}

Color *g_vram_base = (Color*) (0x40000000 | 0x04000000);

Color* getVramDrawBuffer()
{
	Color* vram = (Color*) g_vram_base;
	if (dispBufferNumber == 0) vram += FRAMEBUFFER_SIZE / sizeof(Color);
	return vram;
}

Color* getVramDisplayBuffer()
{
	Color* vram = (Color*) g_vram_base;
	if (dispBufferNumber == 1) vram += FRAMEBUFFER_SIZE / sizeof(Color);
	return vram;
}

void user_warning_fn(png_structp png_ptr, png_const_charp warning_msg)
{
}

static int isJpegFile(const char* filename)
{
	char* suffix = strrchr(filename, '.');
	if (suffix) {
		if (stricmp(suffix, ".jpg") == 0 || stricmp(suffix, ".jpeg") == 0) return 1;
	}
	return 0;
}

Image* loadImage(const char* filename)
{
	if (isJpegFile(filename)) {
		return loadJpegImage(filename);
	} else {
		return loadPngImage(filename);
	}
}


Image* loadPngImageImpl(png_structp png_ptr) {
	unsigned int sig_read = 0;
	png_uint_32 width, height, x, y;
	int bit_depth, color_type, interlace_type;
	u32* line;
	png_infop info_ptr;
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		fprintf(stderr,"error:%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	png_set_sig_bytes(png_ptr, sig_read);
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, int_p_NULL, int_p_NULL);
	if (width > 512 || height > 512) {
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		fprintf(stderr,"error:%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	Image *image = (Image*) malloc(sizeof(Image));
	image->imageWidth = width;
	image->imageHeight = height;
	image->textureWidth = getNextPower2(width);
	image->textureHeight = getNextPower2(height);
	png_set_strip_16(png_ptr);
	png_set_packing(png_ptr);
	if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_gray_1_2_4_to_8(png_ptr);
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png_ptr);
	png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
	image->data = (Color*) memalign(16, image->textureWidth * image->textureHeight * sizeof(Color));
	if (!image->data) {
		perror("memalign()");
		free(image);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		fprintf(stderr,"error:%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	line = (u32*) malloc(width * 4);
	if (!line) {
		free(image->data);
		free(image);
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		fprintf(stderr,"error:%s:%d\n",__FILE__,__LINE__);
		return NULL;
	}
	for (y = 0; y < height; y++) {
		png_read_row(png_ptr, (u8*) line, png_bytep_NULL);
		for (x = 0; x < width; x++) {
			u32 color = line[x];
			image->data[x + y * image->textureWidth] =  color;
		}
	}
	free(line);
	png_read_end(png_ptr, info_ptr);
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
	return image;
}

Image* loadPngImage(const char* filename)
{
	png_structp png_ptr;
	FILE *fp;

	if ((fp = fopen(filename, "rb")) == NULL) return NULL;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fclose(fp);
		return NULL;;
	}
	png_init_io(png_ptr, fp);
	Image* image = loadPngImageImpl(png_ptr);
	fclose(fp);
	return image;
}

Image* loadJpegImageImpl(struct jpeg_decompress_struct dinfo)
{
	jpeg_read_header(&dinfo, 1);
	int width = dinfo.image_width;
	int height = dinfo.image_height;
	jpeg_start_decompress(&dinfo);
	Image* image = (Image*) malloc(sizeof(Image));
	if (!image) {
		jpeg_destroy_decompress(&dinfo);
		return NULL;
	}
	if (width > 512 || height > 512) {
		jpeg_destroy_decompress(&dinfo);
		return NULL;
	}
	image->imageWidth = width;
	image->imageHeight = height;
	image->textureWidth = getNextPower2(width);
	image->textureHeight = getNextPower2(height);
	image->data = (Color*) memalign(16, image->textureWidth * image->textureHeight * sizeof(Color));
	u8* line = (u8*) malloc(width * 3);
	if (!line) {
		jpeg_destroy_decompress(&dinfo);
		return NULL;
	}
	if (dinfo.jpeg_color_space == JCS_GRAYSCALE) {
		while (dinfo.output_scanline < dinfo.output_height) {
			int y = dinfo.output_scanline;
			jpeg_read_scanlines(&dinfo, &line, 1);
			int x;
			for (x = 0; x < width; x++) {
				Color c = line[x];
				image->data[x + image->textureWidth * y] = c | (c << 8) | (c << 16) | 0xff000000;;
			}
		}
	} else {
		while (dinfo.output_scanline < dinfo.output_height) {
			int y = dinfo.output_scanline;
			jpeg_read_scanlines(&dinfo, &line, 1);
			u8* linePointer = line;
			int x;
			for (x = 0; x < width; x++) {
				Color c = *(linePointer++);
				c |= (*(linePointer++)) << 8;
				c |= (*(linePointer++)) << 16;
				image->data[x + image->textureWidth * y] = c | 0xff000000;
			}
		}
	}
	jpeg_finish_decompress(&dinfo);
	jpeg_destroy_decompress(&dinfo);
	free(line);
	return image;
}

Image* loadJpegImage(const char* filename)
{
	struct jpeg_decompress_struct dinfo;
	struct jpeg_error_mgr jerr;
	dinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&dinfo);
	FILE* inFile = fopen(filename, "rb");
	if (!inFile) {
		jpeg_destroy_decompress(&dinfo);
		return NULL;
	}
	jpeg_stdio_src(&dinfo, inFile);
	Image* image = loadJpegImageImpl(dinfo);
	fclose(inFile);
	return image;
}


// code for jpeg memory source
typedef struct {
	struct jpeg_source_mgr pub;	/* public fields */

	const unsigned char* membuff;	/* The input buffer */
	int location;			/* Current location in buffer */ 
	int membufflength;            /* The length of the input buffer */
	JOCTET * buffer;		/* start of buffer */
	boolean start_of_buff;	/* have we gotten any data yet? */
} mem_source_mgr;

typedef mem_source_mgr* mem_src_ptr;

#define INPUT_BUF_SIZE  4096	/* choose an efficiently fread'able size */


METHODDEF(void) mem_init_source (j_decompress_ptr cinfo) {
	mem_src_ptr src;

	src = (mem_src_ptr) cinfo->src;

	/* We reset the empty-input-file flag for each image,
	* but we don't clear the input buffer.
	* This is correct behavior for reading a series of images from one source.
	*/
	src->location = 0;
	src->start_of_buff = 1;
}


METHODDEF(boolean) mem_fill_input_buffer (j_decompress_ptr cinfo) {
	mem_src_ptr src;
	size_t bytes_to_read;
	size_t nbytes;

	src = (mem_src_ptr) cinfo->src;

	if((src->location)+INPUT_BUF_SIZE >= src->membufflength)
		bytes_to_read = src->membufflength - src->location;
	else
		bytes_to_read = INPUT_BUF_SIZE;

	memcpy(src->buffer, (src->membuff)+(src->location), bytes_to_read);
	nbytes = bytes_to_read;
	src->location += (int) bytes_to_read;

	if (nbytes <= 0) {
		if (src->start_of_buff)	/* Treat empty input file as fatal error */
			ERREXIT(cinfo, JERR_INPUT_EMPTY);
		WARNMS(cinfo, JWRN_JPEG_EOF);
		/* Insert a fake EOI marker */
		src->buffer[0] = (JOCTET) 0xFF;
		src->buffer[1] = (JOCTET) JPEG_EOI;
		nbytes = 2;
	}

	src->pub.next_input_byte = src->buffer;
	src->pub.bytes_in_buffer = nbytes;
	src->start_of_buff = 0;

	return 1;
}


METHODDEF(void) mem_skip_input_data (j_decompress_ptr cinfo, long num_bytes) {
	mem_src_ptr src;

	src = (mem_src_ptr) cinfo->src;

	if (num_bytes > 0) {
		while (num_bytes > (long) src->pub.bytes_in_buffer) {
			num_bytes -= (long) src->pub.bytes_in_buffer;
			mem_fill_input_buffer(cinfo);
		}
		src->pub.next_input_byte += (size_t) num_bytes;
		src->pub.bytes_in_buffer -= (size_t) num_bytes;
	}
}


METHODDEF(void) mem_term_source (j_decompress_ptr cinfo) {
}


GLOBAL(void) jpeg_mem_src (j_decompress_ptr cinfo, const unsigned char *mbuff, int mbufflen) {
	mem_src_ptr src;

	if (cinfo->src == NULL) {	/* first time for this JPEG object? */
		cinfo->src = (struct jpeg_source_mgr *)
			(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
			sizeof(mem_source_mgr));
		src = (mem_src_ptr) cinfo->src;
		src->buffer = (JOCTET *)
			(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
			INPUT_BUF_SIZE * sizeof(JOCTET));
	}

	src = (mem_src_ptr) cinfo->src;
	src->pub.init_source = mem_init_source;
	src->pub.fill_input_buffer = mem_fill_input_buffer;
	src->pub.skip_input_data = mem_skip_input_data;
	src->pub.resync_to_restart = jpeg_resync_to_restart;
	src->pub.term_source = mem_term_source;
	src->membuff = mbuff;
	src->membufflength = mbufflen;
	src->pub.bytes_in_buffer = 0;    /* forces fill_input_buffer on first read */
	src->pub.next_input_byte = NULL; /* until buffer loaded */
}

typedef struct {
	const unsigned char *data;
	png_size_t size;
	png_size_t seek;
} PngData;
	
static void ReadPngData(png_structp png_ptr, png_bytep data, png_size_t length)
{
	PngData *pngData = (PngData*) png_get_io_ptr(png_ptr);
	if (pngData) {
                png_size_t i;
		for (i = 0; i < length; i++) {
			if (pngData->seek >= pngData->size) break;
			data[i] = pngData->data[pngData->seek++];
		}
	}
}

Image* loadImageFromMemory(const unsigned char* data, int len)
{
	if (len < 8) return NULL;
	
	// test for PNG
	if (data[0] == 137 && data[1] == 80 && data[2] == 78 && data[3] == 71
		&& data[4] == 13 && data[5] == 10 && data[6] == 26 && data[7] ==10)
	{
		png_structp png_ptr;
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (png_ptr == NULL) {
			fprintf(stderr,"error:%s:%d\n",__FILE__,__LINE__);
			return NULL;
		}
		PngData pngData;
		pngData.data = data;
		pngData.size = len;
		pngData.seek = 0;
		png_set_read_fn(png_ptr, (void *) &pngData, ReadPngData);
		Image* image = loadPngImageImpl(png_ptr);
		return image;
	} else {
		// assume JPG
		struct jpeg_decompress_struct dinfo;
		struct jpeg_error_mgr jerr;
		dinfo.err = jpeg_std_error(&jerr);
		jpeg_create_decompress(&dinfo);
		jpeg_mem_src(&dinfo, data, len);
		Image* image = loadJpegImageImpl(dinfo);
		return image;
	}
}

void freeImage(Image* image)
{
	free(image->data);
	free(image);
}

void fillScreenRect(Color color, int x0, int y0, int width, int height)
{
	if (!initialized) return;
	int skipX = PSP_LINE_SIZE - width;
	int x, y;
	Color* data = getVramDrawBuffer() + x0 + y0 * PSP_LINE_SIZE;
	for (y = 0; y < height; y++, data += skipX) {
		for (x = 0; x < width; x++, data++) *data = color;
	}
}

/*
void saveImage(const char* filename, Color* data, int width, int height, int lineSize, int saveAlpha)
{
	if (isJpegFile(filename)) {
		saveJpegImage(filename, data, width, height, lineSize);
	} else {
		savePngImage(filename, data, width, height, lineSize, saveAlpha);
	}
}
void savePngImage(const char* filename, Color* data, int width, int height, int lineSize, int saveAlpha)
{
	png_structp png_ptr;
	png_infop info_ptr;
	FILE* fp;
	int i, x, y;
	u8* line;
	
	if ((fp = fopen(filename, "wb")) == NULL) return;
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) return;
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		return;
	}
	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr, width, height, 8,
		saveAlpha ? PNG_COLOR_TYPE_RGBA : PNG_COLOR_TYPE_RGB,
		PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_write_info(png_ptr, info_ptr);
	line = (u8*) malloc(width * (saveAlpha ? 4 : 3));
	for (y = 0; y < height; y++) {
		for (i = 0, x = 0; x < width; x++) {
			Color color = data[x + y * lineSize];
			u8 r = color & 0xff; 
			u8 g = (color >> 8) & 0xff;
			u8 b = (color >> 16) & 0xff;
			u8 a = saveAlpha ? (color >> 24) & 0xff : 0xff;
			line[i++] = r;
			line[i++] = g;
			line[i++] = b;
			if (saveAlpha) line[i++] = a;
		}
		png_write_row(png_ptr, line);
	}
	free(line);
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	fclose(fp);
}

void saveJpegImage(const char* filename, Color* data, int width, int height, int lineSize)
{
	FILE* outFile = fopen(filename, "wb");
	if (!outFile) return;
	struct jpeg_error_mgr jerr;
	struct jpeg_compress_struct cinfo;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outFile);
	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 100, 1);
	jpeg_start_compress(&cinfo, 1);
	u8* row = (u8*) malloc(width * 3);
	if (!row) return;
	int y;
	for (y = 0; y < height; y++) {
		u8* rowPointer = row;
		int x;
                for (x = 0; x < width; x++) {
			Color c = data[x + cinfo.next_scanline * lineSize];
			*(rowPointer++) = c & 0xff;
			*(rowPointer++) = (c >> 8) & 0xff;
			*(rowPointer++) = (c >> 16) & 0xff;
		}
		jpeg_write_scanlines(&cinfo, &row, 1);
	}
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(outFile);
	free(row);
}
*/

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4) /* change this if you change to another screenmode */
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define ZBUF_SIZE (BUF_WIDTH SCR_HEIGHT * 2) /* zbuffer seems to be 16-bit? */

void blitImageToVram(int x,int y, int w,int h,int mag, Image *img) {
	Color *vptr0;           //pointer to vram
	Color *vptr;            //pointer to vram
	Color *d;
	Color *dd;
	u8 *ddd;
	int xx,yy,mx,my;

	d=img->data;
	vptr0=PixelPointer(x,y);

	for (yy=0; yy<h; yy++) {
		for (my=0; my<mag; my++) {
			vptr=vptr0;
			dd=d;
			for (xx=0; xx<w; xx++) {
				for (mx=0; mx<mag; mx++) {
					ddd=(u8*)dd;
					if (ddd[3] == 255) {
						*vptr=*dd;
					}
					vptr++;
				}
				dd++;
			}
			vptr0+=PSP_LINE_SIZE; //LINESIZE;
		}
		d+=w;
	}
}

