#pragma once
#include "Include.h"



class Window
{

public:
	friend class App;
	friend class Renderer;
	App* app;
	Renderer* renderer;
	int width, height;
	const char* title;
	
protected:
	static Window* mainWindow;



public:
	~Window();
	Window(int width, int height, const char* title, Renderer* r, App* app);
	virtual void run() = 0;
	virtual bool isKeyPressed(int keycode) = 0;
	virtual float getMouseX() = 0;
	virtual float getMouseY() = 0;
	virtual bool isMousePressed() = 0;
	virtual bool isButtonPressed(int button) = 0;
	virtual void setSize(int width, int height) = 0;
	virtual void setTitle(const char* title) = 0;
	virtual void enableTransparency(bool b) = 0;
	virtual float getFPS() = 0;

	
};

