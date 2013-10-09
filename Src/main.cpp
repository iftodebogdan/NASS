/*
 * main.cpp
 *
 *  Created on: Feb 18, 2013
 *      Author: Bogdan
 */

#include "../Includes/Game.hpp"

//The callbacks
PSP_MODULE_INFO("NASS", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
/*
   Since malloc uses the heap defined at compile time, we should use a negative value such as PSP_HEAP_SIZE_KB(-1024)
   instead of a hardcoded value. So you'll have 23MB on Phat and 55MB on the Slim with 1MB for stacks etc in either case.
*/
PSP_HEAP_SIZE_KB(-1024);

int main()
{
	Game* App = new Game();
	App->Run();

	return 0;
}
