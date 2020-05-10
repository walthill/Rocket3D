#include "Texture.h"
#include <string>

#include "../../core/RenderCore.h"
#include "../platform/OpenGL/OpenGLTexture.h"

Texture2D* Texture2D::create(const std::string& path)
{
	switch (RenderCore::getAPI())
	{
		case Renderer::API::NONE:		return nullptr;
		case Renderer::API::OPENGL:		return new OpenGLTexture2D(path);
	}

	return nullptr;
}
