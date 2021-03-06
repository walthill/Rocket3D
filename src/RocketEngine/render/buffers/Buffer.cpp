#include "Buffer.h"

#include "../../core/RenderCore.h"
#include "../platform/OpenGL/OpenGLBuffer.h"

VertexBuffer* VertexBuffer::create(const float* vertices, uint32 size, DataType usage)
{
	switch (RenderCore::getAPI())
	{
		case Renderer::API::NONE:		return nullptr;
		case Renderer::API::OPENGL:		return new OpenGLVertexBuffer(vertices, size, usage);
	}
	return nullptr;
}

VertexBuffer* VertexBuffer::create(const void* data, uint32 size, DataType usage)
{
	switch (RenderCore::getAPI())
	{
	case Renderer::API::NONE:		return nullptr;
	case Renderer::API::OPENGL:		return new OpenGLVertexBuffer(data, size, usage);
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

FrameBuffer* FrameBuffer::create(int width, int height, int aaSamples)
{
	switch (RenderCore::getAPI())
	{
		case Renderer::API::NONE:		return nullptr;
		case Renderer::API::OPENGL:		return new OpenGLFrameBuffer(width, height, aaSamples);
	}
	return nullptr;
}
