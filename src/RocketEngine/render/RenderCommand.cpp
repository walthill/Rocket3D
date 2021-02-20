#include "RenderCommand.h"

#include "platform/OpenGL/OpenGLRenderer.h"

Renderer* RenderCommand::spRendererAPI = new OpenGLRenderer;