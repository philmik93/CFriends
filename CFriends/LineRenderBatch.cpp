#include "Include.h"


LineRenderBatch::LineRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader) : RenderBatch(maxBatchSize, renderer, shader)
{
	lineCount = 0;
	vertices = new float[maxBatchSize * 2];
	indices = new unsigned int[maxBatchSize * 2];
	generateIndices(indices);
	va = new VertexArray();
	vb = new VertexBuffer(nullptr, maxBatchSize * 2);
	layout = new VertexBufferLayout();
	layout->Push<float>(2);
	ib = new IndexBuffer(indices, maxBatchSize * 2);
	va->AddBuffer(*vb, *layout);

}

void LineRenderBatch::add(float x1, float y1, float x2, float y2)
{
	float in[2] = { x1, y1 };
	float out[2];
	toNDC(in, out);
	
	vertices[lineCount * 2 + 0] = out[0];
	vertices[lineCount * 2 + 1] = out[1];

	in[0] = x2, in[1] = y2;
	toNDC(in, out);
	
	vertices[lineCount * 2 + 2] = out[0];
	vertices[lineCount * 2 + 3] = out[1];

	lineCount++;
}


void LineRenderBatch::render()
{
	va->Bind();
	vb->Bind();
	vb->rebuffer(vertices, lineCount * 2);
	ib->Bind();
	shader->Bind();

	glDrawElements(GL_LINES, lineCount * 2, GL_UNSIGNED_INT, nullptr);

	lineCount = 0;
}

bool LineRenderBatch::hasRoom()
{
	if (lineCount >= maxBatchSize) return false;
	else return true;
}

void LineRenderBatch::generateIndices(unsigned int* in)
{
	for (int i = 0; i < maxBatchSize; i++)
	{
		in[i] = i;
	}
}
