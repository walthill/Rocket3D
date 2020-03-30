#include "Buffer.h"

#include "window/Window.h"
#include "platform/OpenGL/OpenGLBuffer.h"

VertexBuffer* VertexBuffer::Create(VertexData* vertices, uint32 size)
{
	switch (Window::getAPI())
	{
		case WindowAPI::NONE:		return nullptr;
		case WindowAPI::OPENGL:		return new OpenGLVertexBuffer(vertices, size);
	}
	return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32* indicies, uint32 count)
{
	switch (Window::getAPI())
	{
		case WindowAPI::NONE:		return nullptr;
		case WindowAPI::OPENGL:		return new OpenGLIndexBuffer(indicies, count * sizeof(indicies));
	}
	return nullptr;
}
