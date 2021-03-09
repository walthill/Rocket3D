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

		inline static void setDepthBuffer(int depthBufferSetting)
		{
			spRendererAPI->setDepthBuffer(depthBufferSetting);
		}

		inline static void setStencilBuffer(int bufferComparison, int refValue, int mask)
		{
			spRendererAPI->setStencilBuffer(bufferComparison, refValue, mask);
		}

		inline static void setStencilMask(int mask)
		{
			spRendererAPI->setStencilMask(mask);
		}

		inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			spRendererAPI->drawIndexed(vertexArray);
		}

		inline static void drawTriangles(const std::shared_ptr<VertexArray>& vertexArray)
		{
			spRendererAPI->drawTriangles(vertexArray);
		}

	private:
		static Renderer* spRendererAPI;
};

#endif // !RENDER_COMMAND_H
