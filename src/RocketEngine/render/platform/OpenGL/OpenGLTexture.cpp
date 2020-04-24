#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <stb_image.h>

const int OpenGLTexture2D::BORDER_DEFAULT = 0;

OpenGLTexture2D::OpenGLTexture2D(const std::string& path, int detailReductionLevel)
	: mPath(path)
{
	int width, height, channels;
	
	//1 to flip
	//stbi_set_flip_vertically_on_load(1);

	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	assert(data);
	
	mWidth = width;
	mHeight = height;

	glGenTextures(1, &mRendererId);
	glBindTexture(GL_TEXTURE_2D, mRendererId);

	glTexImage2D(GL_TEXTURE_2D, detailReductionLevel, GL_RGB, mWidth, mHeight, BORDER_DEFAULT, GL_RGB, GL_UNSIGNED_BYTE, data);
	//Texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Minification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //TODO: Linear & nearest should be API-exposed
	//Magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &mRendererId);
}

void OpenGLTexture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, mRendererId);
}
