
#include "Include.h"



DrawCircleRenderBatch::DrawCircleRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader) : RenderBatch(maxBatchSize, renderer, shader)
{
	circleCount = 0;
	resolution = 25;
	indices = new unsigned int[maxBatchSize * resolution * 2];
	vertices = new float[(maxBatchSize * resolution * 2) * 2];

	va = new VertexArray();
	va->Bind();
	vb = new VertexBuffer(nullptr, (maxBatchSize * resolution * 2) * 2 * sizeof(float));


	layout = new VertexBufferLayout();
	layout->Push<float>(2);
	va->AddBuffer(*vb, *layout);
	generateIndices(indices);
	ib = new IndexBuffer(indices, maxBatchSize * resolution * 2);



	shader->Bind();
	va->Unbind();
	vb->Unbind();
	ib->Unbind();
	shader->Unbind();


}








void DrawCircleRenderBatch::add(float x, float y, float r1, float r2)
{

	float in[2];
	float out[2];

	for (int i = 0; i < resolution; i++)
	{
		in[0] = sinf(2 * M_PI / resolution * i) * r1 + x;
		in[1] = cosf(2 * M_PI / resolution * i) * r2 + y;
		toNDC(in, out);
		vertices[(circleCount * resolution*2) * 2 + i * 4] = out[0];
		vertices[(circleCount * resolution*2) * 2 + i * 4 + 1] = out[1];


		in[0] = sinf(2 * M_PI / resolution * (i+1)) * r1 + x;
		in[1] = cosf(2 * M_PI / resolution * (i+1)) * r2 + y;
		toNDC(in, out);
		vertices[(circleCount * resolution*2) * 2 + i * 4 + 2] = out[0];
		vertices[(circleCount * resolution*2) * 2 + i * 4 + 3] = out[1];


	}


	// 	vertices[0] = 0.0f;
	// 	vertices[1] = 0.0f;
	// 
	// 	vertices[2] = 1.0f;
	// 	vertices[3] = 1.0f;
	// 
	// 	vertices[4] = -0.9f;
	// 	vertices[5] = 1.0f;
	// 
	// 
	// 	vertices[6] = -0.9f;
	// 	vertices[7] = -1.0f;

	circleCount++;


}






void DrawCircleRenderBatch::render()
{
	vb->Bind();
	vb->rebuffer(vertices, (circleCount * resolution * 2) * 2 * sizeof(float));

	shader->Bind();

	va->Bind();
	ib->Bind();

	glDrawElements(GL_LINES, circleCount * resolution * 2, GL_UNSIGNED_INT, nullptr);
	circleCount = 0;
}








bool DrawCircleRenderBatch::hasRoom()
{
	if (circleCount >= maxBatchSize) return false;
	else return true;
}







void DrawCircleRenderBatch::generateIndices(unsigned int* in)
{
	for (int i = 0; i < maxBatchSize * resolution; i++)
	{
		in[i * 2] = i * 2;
		in[i * 2 + 1] = i * 2 + 1;
		//std::cout << in[i * 3 + 0] << "|" << in[i * 3 + 1] << "|" << in[i * 3 + 2] << std::endl;
	}
}
