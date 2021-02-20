#include "VertexArray.h"
#include "../../core/RenderCore.h"
#include "../platform/OpenGL/OpenGLVertexArray.h"

VertexArray* VertexArray::create()
{
	switch (RenderCore::getAPI())
	{
		case Renderer::API::NONE:		/*assert(false);*/ return nullptr; //not supported
		case Renderer::API::OPENGL:		return new OpenGLVertexArray();
	}
	
	assert(false);	//unknown api
	return nullptr;
}
