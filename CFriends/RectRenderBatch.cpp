#include "Include.h"





RectRenderBatch::RectRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader) : RenderBatch(maxBatchSize, renderer, shader)
{
	rectCount = 0;
	vertices = new float[maxBatchSize * 4 * 2];
	indices = new unsigned int[maxBatchSize * 6];

	generateIndices(indices);


	va = new VertexArray();
	vb = new VertexBuffer(nullptr, maxBatchSize * 4 * 2 * sizeof(float));
	layout = new VertexBufferLayout();
	layout->Push<float>(2);
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(indices, maxBatchSize * 6);

	shader->Bind();
	

	for (int i = 0; i < 10; i++)
	{
		std::cout << vertices[i] << std::endl;
	}


	va->Unbind();
	vb->Unbind();
	ib->Unbind();
	shader->Unbind();
}







void RectRenderBatch::render()
{
	vb->Bind();
	vb->rebuffer(vertices, rectCount * 4 * 2 * sizeof(float));
	shader->Bind();



	va->Bind();
	ib->Bind();



	glDrawElements(GL_TRIANGLES, rectCount * 6, GL_UNSIGNED_INT, nullptr);   // where the nullptr is normaly the pointer of the indices array but we already loaded it in so we pass just the nullptr

	rectCount = 0;


}

void RectRenderBatch::generateIndices(unsigned int* buffer)
{

	for (int i = 0; i < maxBatchSize; i++)
	{
		buffer[6 * i + 0] = 4 * i + 0;
		buffer[6 * i + 1] = 4 * i + 1;
		buffer[6 * i + 2] = 4 * i + 2;
		buffer[6 * i + 3] = 4 * i + 1;
		buffer[6 * i + 4] = 4 * i + 3;
		buffer[6 * i + 5] = 4 * i + 2;
	}

}






void RectRenderBatch::add(float x, float y, float w, float h)
{
	float in[2] = { x, y };
	float out1[2], out2[2], out3[2], out4[2];
	toNDC(in, out1);
	in[1] = y + h;
	toNDC(in, out2);
	in[0] = x + w;
	in[1] = y;
	toNDC(in, out3);
	in[0] = x + w;
	in[1] = y + h;
	toNDC(in, out4);

	vertices[rectCount*8 + 0] = out1[0];
	vertices[rectCount*8 + 1] = out1[1];
	vertices[rectCount*8 + 2] = out2[0];
	vertices[rectCount*8 + 3] = out2[1];
	vertices[rectCount*8 + 4] = out3[0];
	vertices[rectCount*8 + 5] = out3[1];
	vertices[rectCount*8 + 6] = out4[0];
	vertices[rectCount*8 + 7] = out4[1];

	rectCount++;
}








bool RectRenderBatch::hasRoom()
{
	if (rectCount >= maxBatchSize) return false;
	else return true;
}


