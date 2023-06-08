#pragma once
#include "Include.h"
class CircleRenderBatch : public RenderBatch
{



public:
	int circleCount;
	int resolution;
	int circleVertexCount;
	int cirlceIndexCount;
	int vertexFloatCount;
	int vertexSize;

public:
	CircleRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader);
	void add(float x, float y, float r1, float r2);
	void generateIndices(unsigned int*) override;
	bool hasRoom() override;
	void render() override;
};

