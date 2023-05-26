#include "Include.h"
#pragma once
class DrawRectRenderBatch : public RenderBatch
{
public:
	int rectCount;


public:
	DrawRectRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader);
	void add(float x, float y, float w, float h);
	void render() override;
	bool hasRoom() override;
	void generateIndices(unsigned int*) override;

};

