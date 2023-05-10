#include "Include.h"


//using vertex arrays COULD be slower than just use one vertex array for the entire programm and bind vertex buffer and glVertexAttribPointer bevore every drawcall

VertexArray::VertexArray() {
	m_RendererID = 5;
	glGenVertexArrays(1, &m_RendererID);

}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RendererID);
}


void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		unsigned int offset = 0;
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}


void VertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
}


void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}