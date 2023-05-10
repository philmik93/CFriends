
#include "Include.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}



VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_RendererID);
}


void VertexBuffer::Bind()const {
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}


void VertexBuffer::Unbind()const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::rebuffer(const void* data, unsigned int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


