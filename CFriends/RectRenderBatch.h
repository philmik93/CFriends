#pragma once
#include "Include.h"

class ModernOpenGLRenderer;

class RectRenderBatch
{
public:
	int maxBatchSize;
	float* vertices;
	unsigned int* indices;


	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;
	Shader* shader;
	int rectCount = 0;
	ModernOpenGLRenderer* renderer;
	

public:
	void render();
	RectRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader);
	void generateIndicecs(unsigned int* buffer);
	void add(float x, float y, float w, float h);
	bool hasRoom();
	void toNDC(float* in, float* out);
};

