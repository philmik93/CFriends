#pragma once
#include "Include.h"

class ModernOpenGLRenderer;
class Shader;

class RenderBatch
{
public:
	float* vertices;
	int maxBatchSize;
	unsigned int* indices;

	ModernOpenGLRenderer* renderer;
	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout* layout;
	IndexBuffer* ib;
	Shader* shader;

public:
	RenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader);
	~RenderBatch();
	virtual void render() = 0;
	virtual bool hasRoom() = 0;
	virtual void generateIndices(unsigned int*) = 0;
	virtual void toNDC(float* in, float* out);
};

