#pragma once
#include "Include.h"

class VertexBuffer {
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind()const;
	void Unbind()const;
	void rebuffer(const void* data, unsigned int size);
};