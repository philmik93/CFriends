#pragma once
#include "Include.h"


class OpenGLTexture : public CTexture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	OpenGLTexture();
	OpenGLTexture(const std::string& path);
	~OpenGLTexture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

	

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }
};