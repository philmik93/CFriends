#include "Include.h"
#pragma once
class DrawCircleRenderBatch : public RenderBatch
{
public:
	int circleCount;
	int resolution;
public:
	DrawCircleRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader);
	void add(float x, float y, float r1, float r2);
	void render() override;
	bool hasRoom() override;
	void generateIndices(unsigned int*) override;

};

