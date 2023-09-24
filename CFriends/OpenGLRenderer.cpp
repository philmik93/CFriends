#include "Include.h"

OpenGLRenderer::OpenGLRenderer() : lineWidth(1), shader(nullptr), vaID(-1), vbID(-1), translationX(0), translationY(0), rotation(0)
{
	
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
	shader->setUniform1i("DRAW", SHAPE_DRAW);
	shader->Bind();

	float vertices[resolution * 2 + 4];
	int index = 0;

	vertices[index] = x;
	index++;
	vertices[index] = y;
	index++;

	for (int i = 0; i <= resolution; i++)
	{
		vertices[index] = sinf(2 * M_PI / resolution * i) * r1 + x;
		index++;
		vertices[index] = cosf(2 * M_PI / resolution * i) * r2 + y;
		index++;
		
	}
	
	
	glBindVertexArray(vaID);
	glBindBuffer(GL_ARRAY_BUFFER, vbID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, resolution+2);

	
	

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
	shader->setUniform1i("DRAW", SHAPE_DRAW);


	float vertices[resolution * 2 + 2];
	int index = 0;

	for (int i = 0; i <= resolution; i++)
	{
		vertices[index] = sinf(2 * M_PI / resolution * i) * r1 + x;
		index++;
		vertices[index] = cosf(2 * M_PI / resolution * i) * r2 + y;
		index++;
	}

	
	glBindVertexArray(vaID);
	glBindBuffer(GL_ARRAY_BUFFER, vbID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);
	
	glDrawArrays(GL_LINE_LOOP, 0, resolution+1);

}

void OpenGLRenderer::drawTri(float x1, float y1, float x2, float y2, float x3, float y3)
{
	
	shader->setUniform1i("DRAW", SHAPE_DRAW);
	shader->Bind();

	float vertices[] = {
		x1, y1,
		x2, y2,
		x3, y3
	};


	glBindVertexArray(vaID);
	glBindBuffer(GL_ARRAY_BUFFER, vbID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glDrawArrays(GL_LINE_LOOP, 0, 3);
}

void OpenGLRenderer::fillTri(float x1, float y1, float x2, float y2, float x3, float y3)
{
	shader->setUniform1i("DRAW", SHAPE_DRAW);
	shader->Bind();

	float vertices[] = {
		x1, y1,
		x2, y2,
		x3, y3
	};

	bool added = false;
	for (Batch* batch : batches)
	{
		if (batch->hasRoom())
		{
			batch->add(x1, y1, x2, y2, x3, y3);
			added = true;
			break;
		}
	}
	if (!added)
	{
		Batch* batch = new Batch(this, shader);
		batches.push_back(batch);
		batch->add(x1, y1, x2, y2, x3, y3);
	}
	
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
	//glColor4f((float)(r)/255, (float)(g) / 255, (float)(b) / 255, (float)(a) / 255);   only for the default shader ("Fixed Function Pipeline" and not "Programmable Pipeline")
	color = {r,g,b,a};
}




void OpenGLRenderer::setLineWidth(float w)
{
	lineWidth = w;
	//glLineWidth(w);        only for the default shader ("Fixed Function Pipeline" and not "Programmable Pipeline") 
}




void OpenGLRenderer::line(float x1, float y1, float x2, float y2)
{
	shader->Bind();
	shader->setUniform1i("DRAW", SHAPE_DRAW);





	CVector<float> a(x1, y1);
	CVector<float> b(x2, y2);
	CVector<float> vec;
	CVector<float> xAchse(1, 0);
	CVector<float>::sub(&a, &b, &vec);

	float theta = std::acosf(CVector<float>::dot(&vec, &xAchse) / vec.getMag());
	std::cout << "\n" << theta << "\n";

	
	if (y2 < y1) theta = M_PI - theta;
	else theta += M_PI;
	float rotArr[4] = { cosf(theta), sinf(theta), -sinf(theta), cosf(theta) };
	CMatrix<float> rotMat(2, 2);
	rotMat = CMatrix<float>::fromArray(rotArr, 2, 2);

	//std::cout << "rotation matrix\n" << rotMat;

	CMatrix<float> vert1(2, 1);
	vert1.set(-lineWidth / 2, 1, 1);
	vert1.set(-lineWidth / 2, 2, 1);

	CMatrix<float> vert2(2, 1);
	vert2.set(-lineWidth / 2, 1, 1);
	vert2.set(+lineWidth / 2, 2, 1);

	CMatrix<float> vert3(2, 1);
	vert3.set(+lineWidth / 2, 1, 1);
	vert3.set(+lineWidth / 2, 2, 1);

	CMatrix<float> vert4(2, 1);
	vert4.set(-lineWidth / 2, 1, 1);
	vert4.set(-lineWidth / 2, 2, 1);

	CMatrix<float> vert5(2, 1);
	vert5.set(+lineWidth / 2, 1, 1);
	vert5.set(+lineWidth / 2, 2, 1);

	CMatrix<float> vert6(2, 1);
	vert6.set(+lineWidth / 2, 1, 1);
	vert6.set(-lineWidth / 2, 2, 1);

	CMatrix<float> rvert1 = CMatrix<float>::mult(rotMat, vert1);
	//vert1.print();
	//rvert1.print();
	CMatrix<float> rvert2 = CMatrix<float>::mult(rotMat, vert2);
	//vert2.print();
	//rvert2.print();
	CMatrix<float> rvert3 = CMatrix<float>::mult(rotMat, vert3);
	//vert3.print();
	//rvert3.print();
	CMatrix<float> rvert4 = CMatrix<float>::mult(rotMat, vert4);
	//vert4.print();
	//rvert4.print();
	CMatrix<float> rvert5 = CMatrix<float>::mult(rotMat, vert5);
	//vert5.print();
	//rvert5.print();
	CMatrix<float> rvert6 = CMatrix<float>::mult(rotMat, vert6);
	//vert6.print();
	//rvert6.print();


	

/*
	fillTri(
		x1 - lineWidth / 2, y1 - lineWidth / 2,
		x1 - lineWidth / 2, y1 + lineWidth / 2,
		x2 + lineWidth / 2, y2 + lineWidth / 2 
		);
	fillTri(
		x1 - lineWidth / 2, y1 - lineWidth / 2,
		x2 + lineWidth / 2, y2 + lineWidth / 2,
		x2 + lineWidth / 2, y2 - lineWidth / 2
	);
*/



	fillTri(
		x1 + rvert1.get(1, 1), y1 + rvert1.get(2, 1),
		x1 + rvert2.get(1, 1), y1 + rvert2.get(2, 1),
		x2 + rvert3.get(1, 1), y2 + rvert3.get(2, 1)
	);
	fillTri(
		x1 + rvert4.get(1, 1), y1 + rvert4.get(2, 1),
		x2 + rvert5.get(1, 1), y2 + rvert5.get(2, 1),
		x2 + rvert6.get(1, 1), y2 + rvert6.get(2, 1)
	);



}




void OpenGLRenderer::fillRect(float x, float y, float w, float h)
{
	shader->Bind();
	shader->setUniform1i("DRAW", SHAPE_DRAW);
	

	fillTri(x, y, x + w, y, x + w, y + h);
	fillTri(x, y, x+w, y+h, x, y+h);
}




void OpenGLRenderer::fillRect(float x, float y, float s)
{
	fillRect(x, y, s, s);
}




void OpenGLRenderer::drawRect(float x, float y, float w, float h)
{
	
	shader->Bind();
	shader->setUniform1i("DRAW", SHAPE_DRAW);
	
	float vertices[] = {
		x, y,
		x, y + h,
		x + w, y + h,
		x + w, y
		
						};

	line(x, y, x + w, y);
	line(x + w, y, x + w, y + h);
	line(x + w, y + h, x, y + h);
	line(x, y + h, x , y);
}





void OpenGLRenderer::drawRect(float x, float y, float s)
{
	drawRect(x, y, s, s);
}





CTexture* OpenGLRenderer::loadTexture(std::string path)
{
	return new OpenGLTexture(path);
}





void OpenGLRenderer::texture(CTexture* texture, double x, double y, double w, double h)
{
	shader->setUniform1i("DRAW", TEXTURE_DRAW);
	shader->Bind();
	texture->bind(0);
	
	
	shader->setUniform1i("u_texture", 0);
	
	float vertices[] = {
		x,   y,   0.0f, 0.0f,
		x,   y+h, 0.0f, 1.0f,
		x+w, y,   1.0f, 0.0f,
		x+w, y,   1.0f, 0.0f,
		x,   y+h, 0.0f, 1.0f,
		x+w, y+h, 1.0f, 1.0f
		
		
	};
	
	glBindVertexArray(vaID);
	glBindBuffer(GL_ARRAY_BUFFER, vbID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const void*)(2 * sizeof(float)));
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void OpenGLRenderer::rotate(float radiant)
{
	rotation = radiant;
}






void OpenGLRenderer::render()
{
	for (Batch* batch : batches) batch->render();
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
	shader->setUniform1i("DRAW", SHAPE_DRAW);
	setColor(240,225,40,200);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	
	glGenVertexArrays(1, &vaID);
	glBindVertexArray(vaID);

	glGenBuffers(1, &vbID);
	glBindBuffer(GL_ARRAY_BUFFER, vbID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*(resolution * 2 + 4), NULL, GL_DYNAMIC_DRAW);

	
}





void OpenGLRenderer::toNDC(float* in, float* out)
{
	out[0] = in[0] / getWindowWidth() * 2 - 1;
	out[1] = in[1] / getWindowHeight() * -2 + 1;
		
}





void OpenGLRenderer::errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	if (type == 33361) return;
	std::cout << "OpenGL Debug Message:" << std::endl;
	std::cout << "Source: " << source << std::endl;
	std::cout << "Type: " << type << std::endl;
	std::cout << "ID: " << id << std::endl;
	std::cout << "Severity: " << severity << std::endl;
	std::cout << "Message: " << message << std::endl;

}


