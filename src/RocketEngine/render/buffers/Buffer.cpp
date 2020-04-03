#include "Buffer.h"

#include "../../window/Window.h"
#include "../platform/OpenGL/OpenGLBuffer.h"

VertexBuffer* VertexBuffer::create(float* vertices, uint32 size)
{
	switch (Window::getAPI())
	{
		case WindowAPI::NONE:		return nullptr;
		case WindowAPI::OPENGL:		return new OpenGLVertexBuffer(vertices, size);
	}
	return nullptr;
}

IndexBuffer* IndexBuffer::create(uint32* indicies, uint32 count)
{
	switch (Window::getAPI())
	{
		case WindowAPI::NONE:		return nullptr;
		case WindowAPI::OPENGL:		return new OpenGLIndexBuffer(indicies, count * sizeof(indicies));
	}
	return nullptr;
}


FrameBuffer* FrameBuffer::create(int width, int height)
{
	switch (Window::getAPI())
	{
		case WindowAPI::NONE:		return nullptr;
		case WindowAPI::OPENGL:		return new OpenGLFrameBuffer(width, height);
	}
	return nullptr;
}
