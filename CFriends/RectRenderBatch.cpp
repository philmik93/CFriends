#include "Include.h"





RectRenderBatch::RectRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader) : RenderBatch(maxBatchSize, renderer, shader)
{
	rectCount = 0;
	vertices = new float[maxBatchSize * 4 * VERTEX_FLOAT_COUNT];
	indices = new unsigned int[maxBatchSize * 6];

	generateIndices(indices);


	va = new VertexArray();
	vb = new VertexBuffer(nullptr, maxBatchSize * 4 * VERTEX_FLOAT_COUNT * sizeof(float));
	layout = new VertexBufferLayout();
	layout->Push<float>(2);
	layout->Push<float>(4);
	va->AddBuffer(*vb, *layout);
	ib = new IndexBuffer(indices, maxBatchSize * 6);

	shader->Bind();


	va->Unbind();
	vb->Unbind();
	ib->Unbind();
	shader->Unbind();
}







void RectRenderBatch::render()
{


// 	std::cout << "---------------------------------------\n";
// 	for (int i = 0; i < rectCount*4*VERTEX_FLOAT_COUNT; i++)
// 	{
// 		if (i %  VERTEX_FLOAT_COUNT == 0) std::cout << "\n";
// 		std::cout << vertices[i] << std::endl;
// 	}
// 	std::cout << "---------------------------------------\n";


	vb->Bind();
	vb->rebuffer(vertices, rectCount * 4 * VERTEX_FLOAT_COUNT * sizeof(float));
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

	//std::cout << (float)(renderer->color.r) / 255 << "|" << (float)(renderer->color.g) / 255 << "|" << (float)(renderer->color.b) / 255 << "|" << (float)(renderer->color.a) / 255 << "\n";

	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 0] = out1[0];
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 1] = out1[1];
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 2] =  (float)renderer->color.r / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 3] =  (float)renderer->color.g / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 4] =  (float)renderer->color.b / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 5] =  (float)renderer->color.a / 255;
															   
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 6] = out2[0];
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 7] = out2[1];
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 8] =  (float)renderer->color.r / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 9] =  (float)renderer->color.g / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 10] = (float)renderer->color.b / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 11] = (float)renderer->color.a / 255;
															  
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 12] = out3[0];
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 13] = out3[1];
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 14] = (float)renderer->color.r / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 15] = (float)renderer->color.g / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 16] = (float)renderer->color.b / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 17] = (float)renderer->color.a / 255;
															  
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 18] = out4[0];
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 19] = out4[1];
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 20] = (float)renderer->color.r / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 21] = (float)renderer->color.g / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 22] = (float)renderer->color.b / 255;
	vertices[rectCount * 4 * VERTEX_FLOAT_COUNT + 23] = (float)renderer->color.a / 255;

	rectCount++;
}








bool RectRenderBatch::hasRoom()
{
	if (rectCount >= maxBatchSize) return false;
	else return true;
}


