#include "Include.h"


Batch::Batch(OpenGLRenderer* renderer, Shader* shader) : renderer(renderer), shader(shader), currentTriangleCount(0)
{
	glGenVertexArrays(1, &vaID);
	glBindVertexArray(vaID);

	glGenBuffers(1, &vbID);
	glBindBuffer(GL_ARRAY_BUFFER, vbID);
	glBufferData(GL_ARRAY_BUFFER, MAX_TRIANGLES * 3 * VERTEX_SIZE, NULL, GL_DYNAMIC_DRAW);
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

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * VERTEX_ELEMENT_COUNT, 0);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glDrawArrays(GL_TRIANGLES, 0, currentTriangleCount*3);

	currentTriangleCount = 0;
}

void Batch::add(float x1, float y1, float x2, float y2, float x3, float y3)
{
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT    ] = x1;
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 1] = y1;
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 2] = x2;
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 3] = y2;
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 4] = x3;
	vertices[currentTriangleCount * 3 * VERTEX_ELEMENT_COUNT + 5] = y3;
	currentTriangleCount++;
}
