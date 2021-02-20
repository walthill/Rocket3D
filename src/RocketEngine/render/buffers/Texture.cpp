#include "Texture.h"
#include <string>

#include "../../core/RenderCore.h"
#include "../platform/OpenGL/OpenGLTexture.h"

Texture2D* Texture2D::create(const std::string& path, int sWrapParam, int tWrapParam, int miniFilter, int magFilter, int detailReductionLevel)
{
	switch (RenderCore::getAPI())
	{
		case Renderer::API::NONE:		return nullptr;
		case Renderer::API::OPENGL:		return new OpenGLTexture2D(path, sWrapParam, tWrapParam, miniFilter, magFilter, detailReductionLevel);
	}

	return nullptr;
}
