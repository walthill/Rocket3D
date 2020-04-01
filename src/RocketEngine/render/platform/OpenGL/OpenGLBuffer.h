#ifndef OPENGL_BUFFER_H
#define OPENGL_BUFFER_H

#include "../../buffers/Buffer.h"

//Vertex Buffer - OpenGL VBO
class OpenGLVertexBuffer : public VertexBuffer
{
	public:
		OpenGLVertexBuffer(float* vertices, uint32 size);
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

//Frame Buffer - OpenGL FBO
class OpenGLFrameBuffer : public FrameBuffer
{
public:
	OpenGLFrameBuffer(int texWidth, int texHeight);
	virtual ~OpenGLFrameBuffer();

	virtual void Bind() const;
	virtual void Unbind() const;

	virtual uint32 getTextureId() const { return mTextureColorBuffer; };
private:
	int mTexWidth, mTexHeight;		// move to texture class
	uint32 mTextureColorBuffer;		//TODO: texture class
	uint32 mFramebufferId = -1;
	uint32 mRenderBufferId;			//TODO: render buffer class
};

#endif // !OPENGL_BUFFER_H
