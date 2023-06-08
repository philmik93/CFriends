#pragma once
#include "Include.h"


class LineRenderBatch : public RenderBatch
{
public:
	int lineCount;
	int lineVertexCount;
	int vertexFloatCount;
	int vertexSize;
	int lineIndexCount;


public:
	LineRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader);
	void add(float x1, float y1, float x2, float y2);
	void render() override;
	bool hasRoom() override;
	void generateIndices(unsigned int*) override;

};

