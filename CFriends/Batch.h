#pragma once
#include "Include.h"

class Batch
{
public:
	static const int MAX_TRIANGLES = 8000;
	static const int VERTEX_ELEMENT_COUNT = 7;
	static const int VERTEX_SIZE = VERTEX_ELEMENT_COUNT * sizeof(float);
	

private:
	Shader* shader;
	OpenGLRenderer* renderer;
	
	unsigned int vaID, vbID;
	int currentTriangleCount;
	
	float vertices[MAX_TRIANGLES * 3 * VERTEX_ELEMENT_COUNT];
public:
	Batch(OpenGLRenderer* renderer, Shader* shader);
	~Batch();

	bool hasRoom();
	void render();
	void add(float x1, float y1, float x2, float y2, float x3, float y3);
};