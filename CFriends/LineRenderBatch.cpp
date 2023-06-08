#include "Include.h"


LineRenderBatch::LineRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader) : RenderBatch(maxBatchSize, renderer, shader)
{
	lineCount = 0;

	lineVertexCount = 2;
	vertexFloatCount = 6;
	vertexSize = vertexFloatCount * sizeof(float);
	lineIndexCount = 2;

	vertices = new float[maxBatchSize * lineVertexCount * vertexFloatCount];
	indices = new unsigned int[maxBatchSize * lineIndexCount];
	generateIndices(indices);
	va = new VertexArray();
	vb = new VertexBuffer(nullptr, maxBatchSize * lineVertexCount * vertexSize);
	layout = new VertexBufferLayout();
	layout->Push<float>(2);
	layout->Push<float>(4);
	ib = new IndexBuffer(indices, maxBatchSize * lineIndexCount);
	va->AddBuffer(*vb, *layout);

}

void LineRenderBatch::add(float x1, float y1, float x2, float y2)
{
	float in[2] = { x1, y1 };
	float out[2];
	toNDC(in, out);
	
	vertices[lineCount * lineVertexCount * vertexFloatCount + 0] = out[0];
	vertices[lineCount * lineVertexCount * vertexFloatCount + 1] = out[1];
	vertices[lineCount * lineVertexCount * vertexFloatCount + 2] = (float)(renderer->color.r) / 255.0;
	vertices[lineCount * lineVertexCount * vertexFloatCount + 3] = (float)(renderer->color.g) / 255.0;
	vertices[lineCount * lineVertexCount * vertexFloatCount + 4] = (float)(renderer->color.b) / 255.0;
	vertices[lineCount * lineVertexCount * vertexFloatCount + 5] = (float)(renderer->color.a) / 255.0;

	in[0] = x2, in[1] = y2;
	toNDC(in, out);
	
	vertices[lineCount * lineVertexCount * vertexFloatCount + 6] = out[0];
	vertices[lineCount * lineVertexCount * vertexFloatCount + 7] = out[1];
	vertices[lineCount * lineVertexCount * vertexFloatCount + 8] = (float)(renderer->color.r) / 255.0;
	vertices[lineCount * lineVertexCount * vertexFloatCount + 9] = (float)(renderer->color.g) / 255.0;
	vertices[lineCount * lineVertexCount * vertexFloatCount + 10] = (float)(renderer->color.b) / 255.0;
	vertices[lineCount * lineVertexCount * vertexFloatCount + 11] = (float)(renderer->color.a) / 255.0;

	lineCount++;


}


void LineRenderBatch::render()
{

	va->Bind();
	vb->Bind();
	vb->rebuffer(vertices, lineCount * lineVertexCount * vertexSize);
	ib->Bind();
	shader->Bind();

	glDrawElements(GL_LINES, lineCount * lineIndexCount, GL_UNSIGNED_INT, nullptr);
	
	lineCount = 0;
}

bool LineRenderBatch::hasRoom()
{
	if (lineCount >= maxBatchSize) return false;
	else return true;
}

void LineRenderBatch::generateIndices(unsigned int* in)
{
	for (int i = 0; i < maxBatchSize*2; i++)
	{
		in[i] = i;
	}
}
