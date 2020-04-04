#include "VertexArray.h"
#include "../../window/Window.h"
#include "../platform/OpenGL/OpenGLVertexArray.h"

VertexArray* VertexArray::create()
{
	switch (Window::getAPI())
	{
		case WindowAPI::NONE:		/*assert(false);*/ return nullptr; //not supported
		case WindowAPI::OPENGL:		return new OpenGLVertexArray();
	}
	
	assert(false);	//unknown api
	return nullptr;
}
