#include "Include.h"

static Window* mainWindow = nullptr;






void run(App* a)
{
	switch(currentGraphics)
	{
	case LEGACY_OPENGL:
		mainWindow = new GLFWWindow(600, 400, "CFriends App", new OpenGLRenderer(), a);
		break;
	case MODERN_OPENGL:
		break;
	case VULCAN:
		break;
	}
	
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

void drawTri(float x1 ,float y1, float x2, float y2, float x3, float y3)
{
	mainWindow->renderer->drawTri(x1, y1, x2, y2, x3, y3);
}

void fillTri(float x1, float y1, float x2, float y2, float x3, float y3)
{
	mainWindow->renderer->fillTri(x1, y1, x2, y2, x3, y3);
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

CTexture* loadTexture(std::string path)
{
	return mainWindow->renderer->loadTexture(path);
}

void texture(CTexture* texture, double x, double y, double w, double h)
{
	mainWindow->renderer->texture(texture, x, y, w, h);
}

float getWidth()
{
	if (mainWindow != nullptr) return mainWindow->width;
	else
	{
		std::cout << "\nCFRIENDS WAS NOT INITIALIZED. getWidth CANT BE USED\n";
		return NULL;
	}
}

float getHeight()
{
	if (mainWindow != nullptr) return mainWindow->height;
	else
	{
	std::cout << "\nCFRIENDS WAS NOT INITIALIZED. getWidth CANT BE USED\n";
	return NULL;
	}
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

float map(float value, float fromA, float fromB, float toA, float toB)         // maybe not working...
{
	return ((fromB - fromA) - fromB + value) / (fromB - fromA) * (toB-toA) + toA;
}



