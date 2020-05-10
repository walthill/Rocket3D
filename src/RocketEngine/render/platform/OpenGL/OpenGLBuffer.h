#ifndef OPENGL_BUFFER_H
#define OPENGL_BUFFER_H

#include "../../buffers/Buffer.h"

//Vertex Buffer - OpenGL VBO
class OpenGLVertexBuffer : public VertexBuffer
{
	public:
		OpenGLVertexBuffer(float* vertices, uint32 size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void setLayout(const BufferLayout& layout) override { mLayout = layout; }
		virtual const BufferLayout& getLayout() const override { return mLayout; }
	
	private:
		uint32 mRendererId = -1;
		BufferLayout mLayout;
};

//Index Buffer - OpenGL EBO
class OpenGLIndexBuffer : public IndexBuffer
{
	public:
		OpenGLIndexBuffer(uint32* indices, uint32 count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;

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

	virtual void bind() const;
	virtual void bindTexture() const;
	virtual void unbind() const;

	virtual uint32 getTexture() const { return mTextureColorBuffer; };
private:
	int mTexWidth, mTexHeight;		// move to texture class
	uint32 mTextureColorBuffer;		//TODO: texture class
	uint32 mFramebufferId = -1;
	uint32 mRenderBufferId;			//TODO: render buffer class
};

#endif // !OPENGL_BUFFER_H
