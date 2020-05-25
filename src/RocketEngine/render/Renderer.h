#ifndef RENDERER_API_H
#define RENDERER_API_H

#include "buffers/VertexArray.h"
#include "Color.h"

class Renderer
{
	public:
		enum class API { NONE = 0, OPENGL = 1 };	
		enum BufferType { COLOR_BUFFER = 1, DEPTH_BUFFER = 2, ACCUM_BUFFER = 4, STENCIL_BUFFER = 8 };

		/***
			* Draw a color to the screen
		****/
		virtual void clearColor(Color clearColor) PURE_VIRTUAL;
		
		/***
			* Clear OpenGL render buffers based on specified bit parameter
		****/		
		virtual void clearBuffer(int bufferClearFlags) PURE_VIRTUAL;

		virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) PURE_VIRTUAL;

		inline static Renderer::API getAPI() { return msAPI; };

	private:
		static Renderer::API msAPI;
};

#endif // !RENDERER_API_H