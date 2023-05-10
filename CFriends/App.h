#pragma once
#include "Include.h"
class Renderer;
class Window;




class App
{
private:
	Window* window;

public:
	~App();
	virtual void setup() = 0;
	virtual void process(double dt) = 0;

	void setWindow(Window* w);
	
};

