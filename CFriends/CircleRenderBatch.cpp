#include "Include.h"


CircleRenderBatch::CircleRenderBatch(int maxBatchSize, ModernOpenGLRenderer* renderer, Shader* shader) : RenderBatch(maxBatchSize, renderer, shader)
{
	circleCount = 0;
	resolution = 24;
	indices = new unsigned int[maxBatchSize * resolution * 3];
	vertices = new float[(maxBatchSize * resolution + maxBatchSize * 2) * 2];



	va = new VertexArray();
	va->Bind();
	vb = new VertexBuffer(nullptr, (maxBatchSize * resolution + maxBatchSize * 2) * 2 * sizeof(float));
	

	layout = new VertexBufferLayout();
	layout->Push<float>(2);
	//layout->Push<float>(4);
	va->AddBuffer(*vb, *layout);
	generateIndices(indices);
	ib = new IndexBuffer(indices, maxBatchSize * resolution * 3);

	

	shader->Bind();
	va->Unbind();
	vb->Unbind();
	ib->Unbind();
	shader->Unbind();

	

}




void CircleRenderBatch::generateIndices(unsigned int* in)
{

	for (int j = 0; j < maxBatchSize; j++)
	{
		int offset = j * 3 * resolution;
		for (int i = 0; i < resolution; i++)
		{
			in[offset + i * 3 + 0] = j * resolution + 2 * j + 0;
			in[offset + i * 3 + 1] = j * resolution + 2 * j + i + 1;
			in[offset + i * 3 + 2] = j * resolution + 2 * j + i + 2;


		}
	}

	// 	for (int i = 0; i < maxBatchSize * resolution; i++)
	// 	{
	// 		std::cout << in[i*3 + 0] << "|" << in[i*3 + 1] << "|" << in[i*3 + 2] << "\n";
	// 	}


}





void CircleRenderBatch::add(float x, float y, float r1, float r2)
{

	float in[2] = { x, y };
	float out[2];
	toNDC(in, out);

	vertices[(2 * circleCount + circleCount * resolution) * 2 + 0] = out[0];
	vertices[(2 * circleCount + circleCount * resolution) * 2 + 1] = out[1];


	for (int i = 0; i <= resolution; i++)
	{
		in[0] = sinf(2 * M_PI / resolution * i) * r1 + x;
		in[1] = cosf(2 * M_PI / resolution * i) * r2 + y;
		toNDC(in, out);
		vertices[(2 * circleCount + circleCount * resolution) * 2 + 2 + i * 2] = out[0];
		vertices[(2 * circleCount + circleCount * resolution) * 2 + 3 + i * 2] = out[1];
	}


	// 		vertices[0] = 0.0f;
	// 		vertices[1] = 0.0f;
	// 	
	// 		vertices[2] = 1.0f;
	// 		vertices[3] = 1.0f;
	// 	
	// 		vertices[4] = -0.9f;
	// 		vertices[5] = 1.0f;

	// 		vertices[6] = -0.9f;
	// 		vertices[7] = -1.0f;

	circleCount++;


}





bool CircleRenderBatch::hasRoom()
{
	if (circleCount >= maxBatchSize) return false;
	else return true;
}




void CircleRenderBatch::render()
{
	
// 	std::cout << "---------------------------------------\n";
// 	for (int i = 0; i < (2*maxBatchSize + maxBatchSize * resolution) * 2; i++)
// 	{
// 		std::cout << vertices[i] << std::endl;
// 		if (i % 2 != 0) std::cout << std::endl;
// 	}
// 	std::cout << "---------------------------------------\n";





	
	vb->Bind();
	vb->rebuffer(vertices, (circleCount * resolution + circleCount * 2) * 2 * sizeof(float));
	


	shader->Bind();

	va->Bind();
	ib->Bind();
	

	glDrawElements(GL_TRIANGLES, circleCount * resolution * 3, GL_UNSIGNED_INT, nullptr);
	circleCount = 0;



}



