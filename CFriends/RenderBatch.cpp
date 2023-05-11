#include "Include.h"

RenderBatch::RenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader) : maxBatchSize(maxBatchSize), renderer(renderer), shader(shader)
{
	ib = nullptr;
	vb = nullptr;
	va = nullptr;
	layout = nullptr;
	vertices = nullptr;
	indices = nullptr;

}

RenderBatch::~RenderBatch()
{
	delete[] vertices;
	delete va;
	delete vb;
	delete layout;
	delete ib;
}

void RenderBatch::toNDC(float* in, float* out)
{
	out[0] = in[0] / renderer->getWindowWidth() * 2 - 1;
	out[1] = in[1] / renderer->getWindowHeight() * -2 + 1;
}
