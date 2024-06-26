#pragma once
#include "Include.h"

class Batch;

class OpenGLRenderer : public Renderer
{





public:

	struct Color
	{
		int r;
		int g;
		int b;
		int a;
	};

	unsigned int vbID, vaID;
	Color color = { 255, 255, 255, 255 };
	float rotation;
	float translationX;
	float translationY;
private:
	static const int resolution = 25;
	std::vector<Batch*> batches;
	float lineWidth;

public:
	Shader* shader;

	OpenGLRenderer();

	void setWindow(Window* w);
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
	CTexture* loadTexture(std::string path);
	void texture(CTexture* texture, double x, double y, double w, double h);

	void render();
	void prepareFrame();
	void refreshFramebuffer(int width, int height);
	void init();
	void resizeWindow(int width, int height);

	static void GLAPIENTRY errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
		
private:
	void toNDC(float* in, float* out);
};

