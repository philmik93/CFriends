
#include "Include.h"



App::~App()
{
	delete window;
}


void App::setWindow(Window* w)
{
	window = w;
}
