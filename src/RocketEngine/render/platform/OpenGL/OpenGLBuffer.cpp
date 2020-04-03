#include "OpenGLBuffer.h"
#include <glad/glad.h>

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32 size) //size in bytes
{
	glGenBuffers(1, &mRendererId);
	glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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
}

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
	glDeleteFramebuffers(1, &mFramebufferId);
}

void OpenGLFrameBuffer::bind() const
{
	glBindFramebuffer(1, mFramebufferId);
}

void OpenGLFrameBuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}