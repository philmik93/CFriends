#include "Include.h"


Batch::Batch(OpenGLRenderer* renderer, Shader* shader) : renderer(renderer), shader(shader), currentTriangleCount(0)
{
	glGenVertexArrays(1, &vaID);
	glBindVertexArray(vaID);

	glGenBuffers(1, &vbID);
	glBindBuffer(GL_ARRAY_BUFFER, vbID);
	glBufferData(GL_ARRAY_BUFFER, MAX_TRIANGLES * 3 * VERTEX_SIZE, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * VERTEX_ELEMENT_COUNT, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * VERTEX_ELEMENT_COUNT, (const void*)(sizeof(float)*2));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * VERTEX_ELEMENT_COUNT, (const void*)(sizeof(float)*3));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * VERTEX_ELEMENT_COUNT, (const void*)(sizeof(float)*5));
}





Batch::~Batch()
{
	glDeleteVertexArrays(1, &vaID);
	glDeleteBuffers(1, &vbID);
}




bool Batch::hasRoom()
{
	if (currentTriangleCount < MAX_TRIANGLES) return true;
	return false;
}




void Batch::render()
{	
	
	shader->Bind();
	glBindVertexArray(vaID);
	glBindBuffer(GL_ARRAY_BUFFER, vbID);


	glBufferSubData(GL_ARRAY_BUFFER, 0, currentTriangleCount*3*VERTEX_SIZE, vertices);
	glDrawArrays(GL_TRIANGLES, 0, currentTriangleCount*3);
	currentTriangleCount = 0;
}




void Batch::add(float x1, float y1, float x2, float y2, float x3, float y3)
{
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 0 + VERTEX_ELEMENT_COUNT * 0] = x1;
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 1 + VERTEX_ELEMENT_COUNT * 0] = y1;
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 0 + VERTEX_ELEMENT_COUNT * 1] = x2;
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 1 + VERTEX_ELEMENT_COUNT * 1] = y2;
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 0 + VERTEX_ELEMENT_COUNT * 2] = x3;
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 1 + VERTEX_ELEMENT_COUNT * 2] = y3;

	for (int i = 0; i < 3; i++)
	{
		vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 2 + VERTEX_ELEMENT_COUNT * i] = renderer->rotation;
		vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 3 + VERTEX_ELEMENT_COUNT * i] = renderer->translationX;
		vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 4 + VERTEX_ELEMENT_COUNT * i] = renderer->translationY;
		vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 5 + VERTEX_ELEMENT_COUNT * i] = renderer->color.r;
		vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 6 + VERTEX_ELEMENT_COUNT * i] = renderer->color.g;
		vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 7 + VERTEX_ELEMENT_COUNT * i] = renderer->color.b;
		vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 8 + VERTEX_ELEMENT_COUNT * i] = renderer->color.a;
	}

	
	currentTriangleCount++;
}
