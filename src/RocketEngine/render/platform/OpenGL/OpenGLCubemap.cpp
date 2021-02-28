#include "OpenGLCubemap.h"
#include <glad/glad.h>
#include <stb_image.h>

OpenGLCubemap::OpenGLCubemap(std::vector<std::string> faces, int sWrapParam, int tWrapParam, int rWrapParam, 
							 int miniFilter, int magFilter, int detailReductionLevel)
{
	glGenTextures(1, &mRendererId);
	bind();

	int width, height, channels;
	for (uint32 i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
		if (data)
		{
			GLenum format = GL_RGB;
			if (channels == 1)
				format = GL_RED;
			else if (channels == 3)
				format = GL_RGB;
			else if (channels == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, detailReductionLevel, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
				RK_CORE_ERROR_ALL("Cubemap texture failed to load at path" + faces[i]);
				stbi_image_free(data);
		}
	}

	//Set texture parameters
	GLint sWrap = -1, tWrap = -1, rWrap = -1, minificationFilter = -1, magnificationFilter = -1;

	switch (sWrapParam)
	{
		case WrapType::REPEAT:						sWrap = GL_REPEAT;				break;
		case WrapType::MIRRORED_REPEAT:				sWrap = GL_MIRRORED_REPEAT;		break;
		case WrapType::CLAMP_EDGE:					sWrap = GL_CLAMP_TO_EDGE;		break;
	}

	switch (tWrapParam)
	{
		case WrapType::REPEAT:						tWrap = GL_REPEAT;				break;
		case WrapType::MIRRORED_REPEAT:				tWrap = GL_MIRRORED_REPEAT;		break;
		case WrapType::CLAMP_EDGE:					tWrap = GL_CLAMP_TO_EDGE;		break;
	}

	switch (rWrapParam)
	{
		case WrapType::REPEAT:						rWrap = GL_REPEAT;				break;
		case WrapType::MIRRORED_REPEAT:				rWrap = GL_MIRRORED_REPEAT;		break;
		case WrapType::CLAMP_EDGE:					rWrap = GL_CLAMP_TO_EDGE;		break;
	}

	switch (miniFilter)
	{
		case MinifyFilter::MIN_LINEAR:				minificationFilter = GL_LINEAR;				break;
		case MinifyFilter::MIN_NEAREST:				minificationFilter = GL_NEAREST;			break;
		case MinifyFilter::LINEAR_MIPMAP_NEAREST:	minificationFilter = GL_CLAMP_TO_EDGE;		break;
		case MinifyFilter::LINEAR_MIPMAP_LINEAR:	minificationFilter = GL_MIRRORED_REPEAT;	break;
		case MinifyFilter::NEAREST_MIPMAP_NEAREST:	minificationFilter = GL_CLAMP_TO_EDGE;		break;
		case MinifyFilter::NEAREST_MIPMAP_LINEAR:	minificationFilter = GL_MIRRORED_REPEAT;	break;
	}

	switch (magFilter)
	{
		case MagnifyFilter::MAG_LINEAR:				magnificationFilter = GL_LINEAR;		break;
		case MagnifyFilter::MAG_NEAREST:			magnificationFilter = GL_NEAREST;		break;
	}

	//Texture wrapping
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, tWrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, rWrap);
	//Minification
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minificationFilter);
	//Magnification
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, magnificationFilter);
}

OpenGLCubemap::~OpenGLCubemap()
{
}

void OpenGLCubemap::bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, mRendererId);
}
