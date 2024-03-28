#pragma once
#include "Include.h"

class Window;


class Renderer
{

public:
	static const int SHAPE_DRAW = 0;
	static const int TEXTURE_DRAW = 1;

protected:
	Window* window;

public:
	~Renderer();
	virtual void setWindow(Window* w)=0;
	virtual void background(int grey) = 0;
	virtual void background(int grey, int a) = 0;
	virtual void background(int r, int g, int b) = 0;
	virtual void background(int r, int g, int b, int a) = 0;
	virtual void fillCircle(float x, float y, float r1, float r2) = 0;
	virtual void fillCircle(float x, float y, float r) = 0;
	virtual void drawCircle(float x, float y, float r) = 0;
	virtual void drawCircle(float x, float y, float r1, float r2) = 0;
	virtual void drawTri(float x1, float y1, float x2, float y2, float x3, float y3) = 0;
	virtual void fillTri(float x1, float y1, float x2, float y2, float x3, float y3) = 0;
	virtual void setColor(int grey) = 0;
	virtual void setColor(int grey, int a) = 0;
	virtual void setColor(int r, int g, int b) = 0;
	virtual void setColor(int r, int g, int b, int a) = 0;
	virtual void setLineWidth(float w) = 0;
	virtual void line(float x1, float y1, float x2, float y2) = 0;
	virtual void fillRect(float x, float y, float w, float h) = 0;
	virtual void fillRect(float x, float y, float s) = 0;
	virtual void drawRect(float x, float y, float w, float h) = 0;
	virtual void drawRect(float x, float y, float s) = 0;
	virtual void rotate(float radiant) = 0;
	virtual CTexture* loadTexture(std::string) = 0;
	virtual void texture(CTexture* texture, double x, double y, double w, double h) = 0;

	virtual void render() = 0;
	virtual void prepareFrame() = 0;
	virtual void refreshFramebuffer(int width, int height) = 0;
	virtual void init() = 0;
	virtual void resizeWindow(int width, int height) = 0;


	int getWindowWidth();
	int getWindowHeight();
};

