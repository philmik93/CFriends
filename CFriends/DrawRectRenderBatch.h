#include "Include.h"
#pragma once
class DrawRectRenderBatch : public RenderBatch
{
public:
	int rectCount;
	const int VERTEX_FLOAT_COUNT = 6;
	const int RECT_FLOAT_COUNT = VERTEX_FLOAT_COUNT * 4;

public:
	DrawRectRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader);
	void add(float x, float y, float w, float h);
	void render() override;
	bool hasRoom() override;
	void generateIndices(unsigned int*) override;

};

