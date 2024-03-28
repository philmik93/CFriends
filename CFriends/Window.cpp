#include "Include.h"


Window* Window::mainWindow = nullptr;

Window::~Window()
{
	delete app;
	delete renderer;
	delete[] title;
}

Window::Window(int width, int height, const char* title, Renderer* r, App* app) : width(width), height(height), title(title), renderer(r), app(app)
{	
	if (Window::mainWindow == nullptr) Window::mainWindow = this;
	r->setWindow(this);
	app->setWindow(this);
}
