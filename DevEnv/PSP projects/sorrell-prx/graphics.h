#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <psptypes.h>
#include <png.h>

#define	PSP_LINE_SIZE 512
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

typedef u32 Color;
#define A(color) ((u8)(color >> 24 & 0xFF))
#define B(color) ((u8)(color >> 16 & 0xFF))
#define G(color) ((u8)(color >> 8 & 0xFF))
#define R(color) ((u8)(color & 0xFF))

typedef struct
{
	int textureWidth;  // the real width of data, 2^n with n>=0
	int textureHeight;  // the real height of data, 2^n with n>=0
	int imageWidth;  // the image width
	int imageHeight;
	Color* data;
} Image;


extern Image* loadImage(const char* filename);
extern Image* loadPngImage(const char* filename);
extern Image* loadJpegImage(const char* filename);
extern Image* loadImageFromMemory(const unsigned char* data, int len);
extern void blitImageToImage(int sx, int sy, int width, int height, Image* source, int dx, int dy, Image* destination);
extern void blitAlphaImageToImage(int sx, int sy, int width, int height, Image* source, int dx, int dy, Image* destination);
extern Image* createImage(int width, int height);
extern void freeImage(Image* image);
extern void clearImage(Color color, Image* image);
extern void clearScreen(Color color);
extern void fillImageRect(Color color, int x0, int y0, int width, int height, Image* image);
extern void fillScreenRect(Color color, int x0, int y0, int width, int height); 
extern void putPixelScreen(Color color, int x, int y);

/**
 * Set a pixel in an image to the specified color.
 *
 * @pre x >= 0 && x < image->imageWidth && y >= 0 && y < image->imageHeight && image != NULL
 * @param color - new color for the pixels
 * @param x - left position of the pixel
 * @param y - top position of the pixel
 */
extern void putPixelImage(Color color, int x, int y, Image* image);
extern Color getPixelScreen(int x, int y);

/**
 * Get the color of a pixel of an image.
 *
 * @pre x >= 0 && x < image->imageWidth && y >= 0 && y < image->imageHeight && image != NULL
 * @param x - left position of the pixel
 * @param y - top position of the pixel
 * @return the color of the pixel
 */
extern Color getPixelImage(int x, int y, Image* image);
extern void printTextScreen(int x, int y, const char* text, Color color);
extern void printTextImage(int x, int y, const char* text, Color color, Image* image);
extern void saveImage(const char* filename, Color* data, int width, int height, int lineSize, int saveAlpha);
extern void savePngImage(const char* filename, Color* data, int width, int height, int lineSize, int saveAlpha);
extern void saveJpegImage(const char* filename, Color* data, int width, int height, int lineSize);
extern void flipScreen();
extern Color* getVramDrawBuffer();
extern Color* getVramDisplayBuffer();

#endif
