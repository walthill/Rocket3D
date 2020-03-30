#ifndef OPENGL_BUFFER_H
#define OPENGL_BUFFER_H

#include "../../render/Buffer.h"

//Vertex Buffer - OpenGL VBO
class OpenGLVertexBuffer : public VertexBuffer
{
	public:
		OpenGLVertexBuffer(VertexData* vertices, uint32 size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32 mRendererId = -1;
};

//Index Buffer - OpenGL EBO
class OpenGLIndexBuffer : public IndexBuffer
{
	public:
		OpenGLIndexBuffer(uint32* indices, uint32 count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32 getCount() const { return mCount; };
	private:
		uint32 mRendererId = -1;
		uint32 mCount;
};

#endif // !OPENGL_BUFFER_H
