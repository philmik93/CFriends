#include "Include.h"

static Window* mainWindow = nullptr;





void run(App* a)
{
	mainWindow = new GLFWWindow(600, 400, "CFriends App", new OpenGLRenderer(), a);
	mainWindow->run();
}

void setSize(int width, int height)
{
	mainWindow->setSize(width, height);
	
}

void setTitle(const char* title)
{
	mainWindow->setTitle(title);
}

void background(int grey)
{
	mainWindow->renderer->background(grey);
}

void background(int grey, int a)
{
	mainWindow->renderer->background(grey, a);
}

void background(int r, int g, int b, int a)
{
	mainWindow->renderer->background(r, g, b, a);
}

void background(int r, int g, int b)
{
	mainWindow->renderer->background(r, g, b);
}

void fillCircle(float x, float y, float r1, float r2)
{
	mainWindow->renderer->fillCircle(x, y, r1, r2);
}

void fillCircle(float x, float y, float r)
{
	mainWindow->renderer->fillCircle(x, y, r);
}

void drawCircle(float x, float y, float r)
{
	mainWindow->renderer->drawCircle(x, y, r);
}

void drawCircle(float x, float y, float r1, float r2)
{
	mainWindow->renderer->drawCircle(x, y, r1, r2);
}

void setColor(int grey)
{
	mainWindow->renderer->setColor(grey);
}

void setColor(int grey, int a)
{
	mainWindow->renderer->setColor(grey, a);
}

void setColor(int r, int g, int b)
{
	mainWindow->renderer->setColor(r, g, b);
}

void setColor(int r, int g, int b, int a)
{
	mainWindow->renderer->setColor(r, g, b, a);
}

void setLineWidth(float w)
{
	mainWindow->renderer->setLineWidth(w);
}

void line(float x1, float y1, float x2, float y2)
{
	mainWindow->renderer->line(x1, y1, x2, y2);
}

void fillRect(float x, float y, float w, float h)
{
	mainWindow->renderer->fillRect(x, y, w, h);
}

void fillRect(float x, float y, float s)
{
	mainWindow->renderer->fillRect(x, y, s);
}

void drawRect(float x, float y, float w, float h)
{
	mainWindow->renderer->drawRect(x, y, w, h);
}

void drawRect(float x, float y, float s)
{
	mainWindow->renderer->drawRect(x, y, s);
}

float getWidth()
{
	return mainWindow->width;
}

float getHeight()
{
	return mainWindow->height;
}

bool isKeyPressed(int keycode)
{
	return mainWindow->isKeyPressed(keycode);
}

float getMouseX()
{
	return mainWindow->getMouseX();
}

float getMouseY()
{
	return mainWindow->getMouseY();
}

bool isMousePressed()
{
	return mainWindow->isMousePressed();
}

bool isButtonPressed(int button)
{
	return mainWindow->isButtonPressed(button);
}

void enableWindowTransparency(bool b)
{
	mainWindow->enableTransparency(b);
}

float randf(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

int randi(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

float map(float value, float fromA, float fromB, float toA, float toB)
{
	return value / (fromB - fromA) * (toB-toA) + toA;
}



