#include "Include.h"




ModernOpenGLRenderer::~ModernOpenGLRenderer()
{
	for (RectRenderBatch* b : rectBatches)
	{
		delete b;
	}
	delete shader;
}






void ModernOpenGLRenderer::setWindow(Window* w)
{
	this->window = w;
}





void ModernOpenGLRenderer::background(int grey)
{
	background(grey, grey, grey, 255);
}




void ModernOpenGLRenderer::background(int grey, int a)
{
	background(grey, grey, grey, a);
}




void ModernOpenGLRenderer::background(int r, int g, int b)
{
	background(r, g, b, 255);
}




void ModernOpenGLRenderer::background(int r, int g, int b, int a)
{
	glClearColor((float)(r) / 255, (float)(g) / 255, (float)(b) / 255, (float)(a) / 255);
	glClear(GL_COLOR_BUFFER_BIT);
}






void ModernOpenGLRenderer::fillCircle(float x, float y, float r1, float r2)
{
	
	bool added = false;
	for (CircleRenderBatch* b : circleBatches)
	{
		if (b->hasRoom())
		{
			b->add(x, y, r1, r2);
			added = true;
			break;
		}
	}
	if (!added)
	{
		CircleRenderBatch* batch = new CircleRenderBatch(maxBatchSize, this, shader);
		batch->add(x, y, r1, r2);
		circleBatches.push_back(batch);
	}
}





void ModernOpenGLRenderer::fillCircle(float x, float y, float r)
{
	fillCircle(x, y, r, r);
}




void ModernOpenGLRenderer::drawCircle(float x, float y, float r)
{
	drawCircle(x, y, r, r);
}

void ModernOpenGLRenderer::drawCircle(float x, float y, float r1, float r2)
{
	bool added = false;
	for (DrawCircleRenderBatch* b : drawCircleBatches)
	{
		if (b->hasRoom())
		{
			b->add(x, y, r1, r2);
			added = true;
			break;
		}
	}
	if (!added)
	{
		DrawCircleRenderBatch* batch = new DrawCircleRenderBatch(maxBatchSize, this, shader);
		batch->add(x, y, r1, r2);
		drawCircleBatches.push_back(batch);
	}
}



void ModernOpenGLRenderer::setColor(int grey)
{
	setColor(grey, grey, grey, 255);
}



void ModernOpenGLRenderer::setColor(int grey, int a)
{
	setColor(grey, grey, grey, a);
}



void ModernOpenGLRenderer::setColor(int r, int g, int b)
{
	setColor(r, g, b, 255);
}




void ModernOpenGLRenderer::setColor(int r, int g, int b, int a)
{
	
	//shader->SetUniform4f("u_Color", (float)(r) / 255, (float)(g) / 255, (float)(b) / 255, (float)(a) / 255);
	color = {r, g, b, a};
	
}




void ModernOpenGLRenderer::setLineWidth(float w)
{
	glLineWidth(w);
}



void ModernOpenGLRenderer::line(float x1, float y1, float x2, float y2)
{
	bool added = false;
	for (LineRenderBatch* b : lineBatches)
	{
		if (b->hasRoom())
		{
			b->add(x1, y1, x2, y2);
			added = true;
			break;
		}
	}
	if (!added)
	{
		LineRenderBatch* batch = new LineRenderBatch(maxBatchSize, this, shader);
		batch->add(x1, y1, x2, y2);
		lineBatches.push_back(batch);
	}
}



void ModernOpenGLRenderer::fillRect(float x, float y, float w, float h)
{
	bool added = false;
	for (RectRenderBatch* b : rectBatches)
	{
		if (b->hasRoom())
		{
			b->add(x,y,w,h);
			added = true;
			break;
		}
	}
	if (!added)
	{
		RectRenderBatch* batch = new RectRenderBatch(maxBatchSize, this, shader);
		batch->add(x, y, w, h);
		rectBatches.push_back(batch);
	}

	
}

void ModernOpenGLRenderer::fillRect(float x, float y, float s)
{
	fillRect(x, y, s, s);
}

void ModernOpenGLRenderer::drawRect(float x, float y, float w, float h)
{
	bool added = false;
	for (DrawRectRenderBatch* b : drawRectBatches)
	{
		if (b->hasRoom())
		{
			b->add(x, y, w, h);
			added = true;
			break;
		}
	}
	if (!added)
	{
		DrawRectRenderBatch* batch = new DrawRectRenderBatch(maxBatchSize, this, shader);
		batch->add(x, y, w, h);
		drawRectBatches.push_back(batch);
	}
}

void ModernOpenGLRenderer::drawRect(float x, float y, float s)
{
	drawRect(x, y, s, s);
}





void ModernOpenGLRenderer::render()
{
	for (RectRenderBatch* b : rectBatches)
	{
		b->render();
	}

	for (CircleRenderBatch* b : circleBatches)
	{
		b->render();
	}


	for (DrawCircleRenderBatch* b : drawCircleBatches)
	{
		b->render();
	}


	for (LineRenderBatch* b : lineBatches)
	{
		b->render();
	}

	for (DrawRectRenderBatch* b : drawRectBatches)
	{
		b->render();
	}
	

}





void ModernOpenGLRenderer::prepareFrame()
{
	//glClear(GL_COLOR_BUFFER_BIT);
}





void ModernOpenGLRenderer::refreshFramebuffer(int width, int height)
{
	glViewport(0, 0, width, height);
}





void ModernOpenGLRenderer::init()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(errorCallback, nullptr);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shader = new Shader("res/shaders/Basic.shader");
}




void ModernOpenGLRenderer::toNDC(float* in, float* out)
{
	out[0] = in[0] / getWindowWidth() * 2 - 1;
	out[1] = in[1] / getWindowHeight() * -2 + 1;

}




void ModernOpenGLRenderer::errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{

	std::cout << "OpenGL Debug Message:" << std::endl;
	std::cout << "Source: " << source << std::endl;
	std::cout << "Type: " << type << std::endl;
	std::cout << "ID: " << id << std::endl;
	std::cout << "Severity: " << severity << std::endl;
	std::cout << "Message: " << message << std::endl;
	



}




