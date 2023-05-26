#pragma once
#include "Include.h"

class ModernOpenGLRenderer;

class RectRenderBatch : public RenderBatch
{
public:
	int rectCount = 0;
	const int VERTEX_FLOAT_COUNT = 6;

public:
	RectRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader);
	void render() override;
	void generateIndices(unsigned int* buffer) override;
	void add(float x, float y, float w, float h);
	bool hasRoom() override;
};

