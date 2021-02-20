#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include "Renderer.h"

class RenderCommand
{
	public:
		inline static void clearColor(Color color)
		{
			spRendererAPI->clearColor(color);
		}

		inline static void clearBuffer(int bufferClearFlags)
		{
			spRendererAPI->clearBuffer(bufferClearFlags);
		}

		inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			spRendererAPI->drawIndexed(vertexArray);
		}

	private:
		static Renderer* spRendererAPI;
};

#endif // !RENDER_COMMAND_H
