#pragma once
#include "Include.h"




class ModernOpenGLRenderer : public Renderer
{

public:
	int maxBatchSize = 1000000;
	std::vector<RectRenderBatch*> rectBatches;
	Shader* shader;

public:
	~ModernOpenGLRenderer();

	void setWindow(Window* w) override;
	void background(int grey) override;
	void background(int grey, int a) override;
	void background(int r, int g, int b) override;
	void background(int r, int g, int b, int a) override;
	void fillCircle(float x, float y, float r1, float r2) override;
	void fillCircle(float x, float y, float r) override;
	void drawCircle(float x, float y, float r) override;
	void drawCircle(float x, float y, float r1, float r2) override;
	void setColor(int grey) override;
	void setColor(int grey, int a) override;
	void setColor(int r, int g, int b) override;
	void setColor(int r, int g, int b, int a) override;
	void setLineWidth(float w) override;
	void line(float x1, float y1, float x2, float y2) override;
	void fillRect(float x, float y, float w, float h) override;
	void fillRect(float x, float y, float s) override;
	void drawRect(float x, float y, float w, float h) override;
	void drawRect(float x, float y, float s) override;



	void render();
	void prepareFrame() override;
	void refreshFramebuffer(int width, int height) override;
	void init() override;


	static void GLAPIENTRY errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);


private:
	void toNDC(float* in, float* out);
};

