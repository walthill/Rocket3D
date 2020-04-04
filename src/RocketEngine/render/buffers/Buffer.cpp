#include "Buffer.h"

#include "../../core/RenderCore.h"
#include "../platform/OpenGL/OpenGLBuffer.h"

VertexBuffer* VertexBuffer::create(float* vertices, uint32 size)
{
	switch (RenderCore::getAPI())
	{
	case Renderer::API::NONE:		return nullptr;
		case Renderer::API::OPENGL:		return new OpenGLVertexBuffer(vertices, size);
	}
	return nullptr;
}

IndexBuffer* IndexBuffer::create(uint32* indicies, uint32 count)
{
	switch (RenderCore::getAPI())
	{
		case Renderer::API::NONE:		return nullptr;
		case Renderer::API::OPENGL:		return new OpenGLIndexBuffer(indicies, count * sizeof(indicies));
	}
	return nullptr;
}


FrameBuffer* FrameBuffer::create(int width, int height)
{
	switch (RenderCore::getAPI())
	{
		case Renderer::API::NONE:		return nullptr;
		case Renderer::API::OPENGL:		return new OpenGLFrameBuffer(width, height);
	}
	return nullptr;
}
