#include "Include.h"

OpenGLRenderer::OpenGLRenderer()
{
	this->resolution = 40;
}

void OpenGLRenderer::setWindow(Window* w)
{
	this->window = w;
}

void OpenGLRenderer::background(int grey)
{
	background(grey, grey, grey, 255);
}

void OpenGLRenderer::background(int grey, int a)
{
	background(grey, grey, grey, a);
}


void OpenGLRenderer::background(int r, int g, int b)
{
	background(r, g, b, 255);
}



void OpenGLRenderer::background(int r, int g, int b, int a)
{
	glClearColor((float)(r) / 255, (float)(g) / 255, (float)(b) / 255, (float)(a) / 255);
	glClear(GL_COLOR_BUFFER_BIT);
}



void OpenGLRenderer::fillCircle(float x, float y, float r1, float r2)
{
	shader->Bind();


	float in[2] = { x, y };
	float out[2];
	toNDC(in, out);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(out[0], out[1]);

	for (int i = 0; i <= resolution; i++)
	{
		in[0] = sinf(2 * M_PI / resolution * i) * r1 + x;
		in[1] = cosf(2 * M_PI / resolution * i) * r2 + y;
		toNDC(in, out);
		glVertex2f(out[0], out[1]);
	}

	glEnd();

}





void OpenGLRenderer::fillCircle(float x, float y, float r)
{
	fillCircle(x, y, r, r);
}

void OpenGLRenderer::drawCircle(float x, float y, float r)
{
	drawCircle(x, y, r, r);
}


void OpenGLRenderer::drawCircle(float x, float y, float r1, float r2)
{

	float in[2] = { x, y };
	float out[2];
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i <= resolution; i++)
	{
		in[0] = sinf(2 * M_PI / resolution * i) * r1 + x;
		in[1] = cosf(2 * M_PI / resolution * i) * r2 + y;
		toNDC(in, out);
		glVertex2f(out[0], out[1]);
	}

	glEnd();

}

void OpenGLRenderer::drawTri(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float in[2] = {x1, y1}, out[2];
	glBegin(GL_LINE_LOOP);
	toNDC(in, out);
	glVertex2f(out[0], out[1]);
	in[0] = x2; in[1] = y2;
	toNDC(in, out);
	glVertex2f(out[0], out[1]);
	in[0] = x3; in[1] = y3;
	toNDC(in, out);
	glVertex2f(out[0], out[1]);
	glEnd();
}

void OpenGLRenderer::fillTri(float x1, float y1, float x2, float y2, float x3, float y3)
{
	float in[2] = { x1, y1 }, out[2];
	glBegin(GL_TRIANGLES);
	toNDC(in, out);
	glVertex2f(out[0], out[1]);
	in[0] = x2; in[1] = y2;
	toNDC(in, out);
	glVertex2f(out[0], out[1]);
	in[0] = x3; in[1] = y3;
	toNDC(in, out);
	glVertex2f(out[0], out[1]);
	glEnd();
}

void OpenGLRenderer::setColor(int grey)
{
	setColor(grey, grey, grey, 255);
}


void OpenGLRenderer::setColor(int grey, int a)
{
	setColor(grey, grey, grey, a);
}


void OpenGLRenderer::setColor(int r, int g, int b)
{
	setColor(r, g, b, 255);
}


void OpenGLRenderer::setColor(int r, int g, int b, int a)
{
	glColor4f((float)(r)/255, (float)(g) / 255, (float)(b) / 255, (float)(a) / 255);
}

void OpenGLRenderer::setLineWidth(float w)
{
	glLineWidth(w);
}

void OpenGLRenderer::line(float x1, float y1, float x2, float y2)
{
	float in[2] = { x1, y1 };
	float out[2];
	toNDC(in, out);
	glBegin(GL_LINES);
	glVertex2f(out[0], out[1]);
	in[0] = x2, in[1] = y2;
	toNDC(in, out);
	glVertex2f(out[0], out[1]);
	glEnd();
}

void OpenGLRenderer::fillRect(float x, float y, float w, float h)
{
	float in[2] = { x, y };
	float out1[2], out2[2], out3[2], out4[2];
	toNDC(in, out1);
	in[1] = y + h;
	toNDC(in, out2);
	in[0] = x + w;
	in[1] = y;
	toNDC(in, out3);
	in[0] = x + w;
	in[1] = y + h;
	toNDC(in, out4);
	glBegin(GL_TRIANGLES);
	glVertex2f(out1[0], out1[1]);
	glVertex2f(out2[0], out2[1]);
	glVertex2f(out3[0], out3[1]);
	glVertex2f(out3[0], out3[1]);
	glVertex2f(out2[0], out2[1]);
	glVertex2f(out4[0], out4[1]);
	glEnd();
}

void OpenGLRenderer::fillRect(float x, float y, float s)
{
	fillRect(x, y, s, s);
}

void OpenGLRenderer::drawRect(float x, float y, float w, float h)
{
	float in[2] = { x, y };
	float out1[2], out2[2], out3[2], out4[2];
	toNDC(in, out1);
	in[1] = y + h;
	toNDC(in, out2);
	in[0] = x + w;
	in[1] = y;
	toNDC(in, out3);
	in[0] = x + w;
	in[1] = y + h;
	toNDC(in, out4);
	glBegin(GL_LINE_LOOP);
	glVertex2f(out1[0], out1[1]);
	glVertex2f(out2[0], out2[1]);
	glVertex2f(out4[0], out4[1]);
	glVertex2f(out3[0], out3[1]);
	glEnd();

}

void OpenGLRenderer::drawRect(float x, float y, float s)
{
	drawRect(x, y, s, s);
}

void OpenGLRenderer::loadTexture(std::string path)
{

}

void OpenGLRenderer::texture(CTexture& texture, double x, double y, double w, double h)
{
	
	shader->Bind();
	texture.bind(0);
	float in[2] = { x, y };
	float out1[2], out2[2], out3[2], out4[2];
	toNDC(in, out1);
	in[1] = y + h;
	toNDC(in, out2);
	in[0] = x + w;
	in[1] = y;
	toNDC(in, out3);
	in[0] = x + w;
	in[1] = y + h;
	toNDC(in, out4);
	
	shader->setUniform1i("u_texture", 0);
	
	unsigned int vbID, vaID;
	float vertices[] = {
		out1[0], out1[1], 0.0f, 0.0f,
		out2[0], out2[1], 0.0f, 1.0f,
		out3[0], out3[1], 1.0f, 0.0f,
		out3[0], out3[1], 1.0f, 0.0f,
		out2[0], out2[1], 0.0f, 1.0f,
		out4[0], out4[1], 1.0f, 1.0f
		
		
	};
	glGenVertexArrays(1, &vaID);
	glBindVertexArray(vaID);

	glGenBuffers(1, &vbID);
	glBindBuffer(GL_ARRAY_BUFFER, vbID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(2 * sizeof(float)));
	glDrawArrays(GL_TRIANGLES, 0, 6);
}



void OpenGLRenderer::render()
{
}

void OpenGLRenderer::prepareFrame() // kann eigentlich echt weg
{
	//glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::refreshFramebuffer(int width, int height)
{
	glViewport(0, 0, width, height);
}

void OpenGLRenderer::init()
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(errorCallback, nullptr);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	std::cout << "init\n";
	shader = new Shader("res/shaders/Basic.shader");
	shader->Bind();
	glColor4f(0.8f, 0.7f, 0.0f, 1.0f);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
}



void OpenGLRenderer::toNDC(float* in, float* out)
{
	out[0] = in[0] / getWindowWidth() * 2 - 1;
	out[1] = in[1] / getWindowHeight() * -2 + 1;
		
}



void OpenGLRenderer::errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{

	std::cout << "OpenGL Debug Message:" << std::endl;
	std::cout << "Source: " << source << std::endl;
	std::cout << "Type: " << type << std::endl;
	std::cout << "ID: " << id << std::endl;
	std::cout << "Severity: " << severity << std::endl;
	std::cout << "Message: " << message << std::endl;

}


