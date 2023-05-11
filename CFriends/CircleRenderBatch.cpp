#include "Include.h"


CircleRenderBatch::CircleRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader) : RenderBatch(maxBatchSize, renderer, shader)
{
	circleCount = 0;
	resolution = 25;
	indices = new unsigned int[maxBatchSize * resolution * 3];
	vertices = new float[maxBatchSize + maxBatchSize * resolution];
	va = new VertexArray();
	vb = new VertexBuffer(nullptr, maxBatchSize + maxBatchSize * resolution);
	layout = new VertexBufferLayout();
	layout->Push<float>(2);
	va->AddBuffer(*vb, *layout);
	generateIndices(indices);
	ib = new IndexBuffer(indices, maxBatchSize * resolution * 3);
}




void CircleRenderBatch::generateIndices(unsigned int* in)
{

	for (int i = 0; i < maxBatchSize * resolution; i++)
	{
		in[i * 3 + 0] = 0;
		in[i * 3 + 1] = i + 1;
		in[i * 3 + 2] = i + 2;
	}

}



void CircleRenderBatch::add(float x, float y, float r1, float r2)
{
	float in[2] = { x, y };
	float out[2];
	toNDC(in, out);
	
	vertices[circleCount + circleCount * resolution + 0] = in[0];
	vertices[circleCount + circleCount * resolution + 1] = in[1];


	for (int i = 0; i <= resolution; i++)
	{
		in[0] = sinf(2 * M_PI / resolution * i) * r1 + x;
		in[1] = cosf(2 * M_PI / resolution * i) * r2 + y;
		toNDC(in, out);

		vertices[circleCount + circleCount * resolution + 2 + i * 2] = in[0];
		vertices[circleCount + circleCount * resolution + 3 + i * 2] = in[1];

	}

	circleCount++;

	
}



bool CircleRenderBatch::hasRoom()
{
	if (circleCount >= maxBatchSize) return false;
	else return true;
}




void CircleRenderBatch::render()
{
	va->Bind();
	shader->Bind();
	ib->Bind();
	vb->rebuffer(vertices, circleCount + circleCount * resolution);
	glDrawElements(GL_TRIANGLES, circleCount * resolution * 3, GL_UNSIGNED_INT, nullptr);
	circleCount = 0;
}



