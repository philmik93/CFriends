#pragma once
#include "Include.h"


enum Graphics
{
	LEGACY_OPENGL,
	MODERN_OPENGL,
	VULCAN

};

Graphics const currentGraphics = LEGACY_OPENGL;

void run(App* a);

void setSize(int width, int height);
void setTitle(const char* title);
void background(int grey);
void background(int grey, int a);
void background(int r, int g, int b, int a);
void background(int r, int g, int b);
void fillCircle(float x, float y, float r1, float r2);
void fillCircle(float x, float y, float r);
void drawCircle(float x, float y, float r);
void drawCircle(float x, float y, float r1, float r2);
void drawTri(float x1, float y1, float x2, float y2, float x3, float y3);
void fillTri(float x1, float y1, float x2, float y2, float x3, float y3);
void setColor(int grey);
void setColor(int grey, int a);
void setColor(int r, int g, int b);
void setColor(int r, int g, int b, int a);
void setLineWidth(float w);
void line(float x1, float y1, float x2, float y2);
void fillRect(float x, float y, float w, float h);
void fillRect(float x, float y, float s);
void drawRect(float x, float y, float w, float h);
void drawRect(float x, float y, float s);
void rotate(float radiant);
float radians(float degree);
CTexture* loadTexture(std::string path);
void texture(CTexture* texture, double x, double y, double w, double h);
float getWidth();
float getHeight();
bool isKeyPressed(int keycode);
float getMouseX();
float getMouseY();
bool isMousePressed();
bool isButtonPressed(int button);
void enableWindowTransparency(bool b);

float randf(float min, float max);
int randi(int min, int max);
float map(float value, float fromA, float fromB, float toA, float toB);
