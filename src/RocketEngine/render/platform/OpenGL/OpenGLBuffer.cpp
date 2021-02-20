#include "OpenGLBuffer.h"
#include <glad/glad.h>

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32 size, DataType usage) //size in bytes
{
	glGenBuffers(1, &mRendererId);
	glBindBuffer(GL_ARRAY_BUFFER, mRendererId);

	switch (usage)
	{
		case VertexBuffer::DataType::STATIC:
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
			break;
		case VertexBuffer::DataType::DYNAMIC:
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
			break;
		case VertexBuffer::DataType::STREAM:
			glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STREAM_DRAW);
			break;
	}
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &mRendererId);
}

void OpenGLVertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
}

void OpenGLVertexBuffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::updateBufferData(float* vertices, uint32 size, int offset)
{
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices); 
}

/*********************************************************************

Index Buffer for OpenGL -- aka Element Buffer Object (EBO)

**********************************************************************/

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, uint32 count) : //count = number of elements
	mCount(count)
{
	glGenBuffers(1, &mRendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &mRendererId);
}

void OpenGLIndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId);
}

void OpenGLIndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*********************************************************************

Frame Buffer for OpenGL -- aka Frame Buffer Object (FBO)

**********************************************************************/

OpenGLFrameBuffer::OpenGLFrameBuffer(int texWidth, int texHeight) :
	mTexWidth(texWidth), 
	mTexHeight(texHeight)
{
	glGenFramebuffers(1, &mFramebufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferId);

	// create a color attachment texture
	glGenTextures(1, &mTextureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, mTextureColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mTexWidth, mTexHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureColorBuffer, 0);

	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mTexWidth, mTexHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it

	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		RK_ERROR_ALL("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	}
}

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
	glDeleteFramebuffers(1, &mFramebufferId);
}

void OpenGLFrameBuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFramebufferId);
}

void OpenGLFrameBuffer::bindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, mTextureColorBuffer);
}

void OpenGLFrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}