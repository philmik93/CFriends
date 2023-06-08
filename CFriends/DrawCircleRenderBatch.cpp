
#include "Include.h"



DrawCircleRenderBatch::DrawCircleRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader) : RenderBatch(maxBatchSize, renderer, shader)
{
	circleCount = 0;
	resolution = 25;
	vertexFloatCount = 6;
	vertexSize = vertexFloatCount * sizeof(float);
	circleVertexCount = resolution *2;
	circleIndexCount = 2 * resolution;

	indices = new unsigned int[maxBatchSize * circleIndexCount];
	vertices = new float[maxBatchSize * vertexFloatCount * circleVertexCount];

	va = new VertexArray();
	va->Bind();
	vb = new VertexBuffer(nullptr, maxBatchSize * circleVertexCount * vertexSize);


	layout = new VertexBufferLayout();
	layout->Push<float>(2);
	layout->Push<float>(4);
	va->AddBuffer(*vb, *layout);
	generateIndices(indices);
	ib = new IndexBuffer(indices, maxBatchSize * circleIndexCount);



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

	int floatsPerLine = 2 * vertexFloatCount;

	for (int i = 0; i < resolution; i++)
	{
		in[0] = sinf(2 * M_PI / resolution * i) * r1 + x;
		in[1] = cosf(2 * M_PI / resolution * i) * r2 + y;
		toNDC(in, out);
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine] = out[0];
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 1] = out[1];
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 2] = (float)(renderer->color.r)/255.0;
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 3] = (float)(renderer->color.g)/255.0;
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 4] = (float)(renderer->color.b)/255.0;
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 5] = (float)(renderer->color.a)/255.0;


		in[0] = sinf(2 * M_PI / resolution * (i+1)) * r1 + x;
		in[1] = cosf(2 * M_PI / resolution * (i+1)) * r2 + y;
		toNDC(in, out);
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 6] = out[0];
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 7] = out[1];
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 8] = (float)(renderer->color.r) / 255.0;
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 9] = (float)(renderer->color.g) / 255.0;
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 10] = (float)(renderer->color.b) / 255.0;
		vertices[circleCount * circleVertexCount * vertexFloatCount + i * floatsPerLine + 11] = (float)(renderer->color.a) / 255.0;

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
	vb->rebuffer(vertices, circleCount * circleVertexCount * vertexSize);

	shader->Bind();

	va->Bind();
	ib->Bind();

	glDrawElements(GL_LINES, circleCount * circleIndexCount, GL_UNSIGNED_INT, nullptr);
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
