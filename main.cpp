/*
 * main.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: Bogdan
 */

//The main library OSLib
#include <oslib/oslib.h>

//The callbacks
PSP_MODULE_INFO("OSLib Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
/*
   Since malloc uses the heap defined at compile time, we should use a negative value such as PSP_HEAP_SIZE_KB(-1024)
   instead of a hardcoded value. So you'll have 23MB on Phat and 55MB on the Slim with 1MB for stacks etc in either case.
*/
PSP_HEAP_SIZE_KB(-1024);

int main()
{
	//Initialization of the library
	oslInit(0);

	//Initialization of the graphic mode
	oslInitGfx(OSL_PF_8888, 1);

	//Show our splash screen
	oslShowSplashScreen(1);

	//Wait a keystroke
	oslWaitKey();

	//Leaving the program
	oslEndGfx();
	oslQuit();
	return 0;
}
