#include "OpenGLRenderer.h"

#include <glad/glad.h>

void OpenGLRenderer::clearColor(Color clearColor)
{
	glClearColor(clearColor.getR01(), clearColor.getG01(), clearColor.getB01(), clearColor.getA01());
}

void OpenGLRenderer::clearBuffer(int bufferClearFlags)
{
	if (bufferClearFlags & COLOR_BUFFER)
		glClear(GL_COLOR_BUFFER_BIT);
	if (bufferClearFlags & DEPTH_BUFFER)
		glClear(GL_DEPTH_BUFFER_BIT);
	/*if (buffersToClear & ACCUM_BUFFER)	//Seems to be deprecated in current glfw/OpenGL
		glClear(GL_ACCUM_BUFFER);*/			// http://stackoverflow.com/questions/23990366/ddg#23995804
	if (bufferClearFlags & STENCIL_BUFFER)
		glClear(GL_STENCIL_BUFFER_BIT);
}

void OpenGLRenderer::setDepthBuffer(int depthBufferType)
{
	GLenum depthComparisonType{};
	switch (depthBufferType)
	{
		case NEVER:				depthComparisonType = GL_NEVER;		break;
		case LESS:				depthComparisonType = GL_LESS;		break;
		case LESS_OR_EQUAL:		depthComparisonType = GL_LEQUAL;	break;
		case EQUAL:				depthComparisonType = GL_EQUAL;		break;
		case NOT_EQUAL:			depthComparisonType = GL_NOTEQUAL;	break;
		case GREATER:			depthComparisonType = GL_GREATER;	break;
		case GREAT_OR_EQUAL:	depthComparisonType = GL_GEQUAL;	break;
		case ALWAYS:			depthComparisonType = GL_ALWAYS;	break;
	}

	glDepthFunc(depthComparisonType);
}

void OpenGLRenderer::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
}

void OpenGLRenderer::drawTriangles(const std::shared_ptr<VertexArray>& vertexArray)
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}