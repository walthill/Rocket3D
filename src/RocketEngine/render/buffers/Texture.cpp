#include "Texture.h"
#include <string>

#include "../../core/RenderCore.h"
#include "../platform/OpenGL/OpenGLTexture.h"
#include "../platform/OpenGL/OpenGLCubemap.h"

Texture2D* Texture2D::create(const std::string& path, int sWrapParam, int tWrapParam, int miniFilter, int magFilter, int detailReductionLevel)
{
	switch (RenderCore::getAPI())
	{
		case Renderer::API::NONE:		return nullptr;
		case Renderer::API::OPENGL:		return new OpenGLTexture2D(path, sWrapParam, tWrapParam, miniFilter, magFilter, detailReductionLevel);
	}

	return nullptr;
}

CubemapTexture* CubemapTexture::create(std::vector<std::string> faces, int sWrapParam, int tWrapParam, int rWrapParam,
									  int miniFilter, int magFilter, int detailReductionLevel)
{
	switch (RenderCore::getAPI())
	{
		case Renderer::API::NONE:		return nullptr;
		case Renderer::API::OPENGL:		return new OpenGLCubemap(faces, sWrapParam, tWrapParam, rWrapParam, miniFilter, magFilter, detailReductionLevel);
	}

	return nullptr;
}
