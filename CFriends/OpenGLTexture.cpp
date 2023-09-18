#include "Include.h"


OpenGLTexture::OpenGLTexture()
{
}

OpenGLTexture::OpenGLTexture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	std::cout << "drinne\n";
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);    // 4 because rgba
	
	//glActiveTexture(GL_TEXTURE0);
	//glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	

	//for any parameters of the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer); //internal format(first format) is how opengl will sotre the texture data, format is how you provide the texture data to opengl
	glBindTexture(GL_TEXTURE_2D, 0);																		// GL_RGBA and every channel is than an GL_UNSIGNED_BYTE with those arguments

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
		std::cout << "RICHTIG\n";
	}


}

OpenGLTexture::~OpenGLTexture()
{
	glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void OpenGLTexture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
