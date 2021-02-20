#ifndef OPENGL_RENDERER_API_H
#define OPENGL_RENDERER_API_H

#include "../../Renderer.h"

class OpenGLRenderer : public Renderer
{
	public:
		virtual void clearColor(Color clearColor) override;
		virtual void clearBuffer(int bufferClearFlags) override;

		virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	private:
};

#endif // !OPENGL_RENDERER_API_H
