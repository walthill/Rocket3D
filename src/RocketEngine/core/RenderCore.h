#ifndef RENDER_CORE_H
#define RENDER_CORE_H

#include <rkutil/Trackable.h>
#include "../render/buffers/VertexArray.h"
#include "../render/RenderCommand.h"

class RenderCore : public rkutil::Trackable
{
	public:
		static void beginScene();
		static void endScene();
		static void submit(const std::shared_ptr<VertexArray>& vertexArray);
		static void submit(const std::shared_ptr<VertexArray>& vertexArray, uint32 instanceCount);

		inline static Renderer::API getAPI() { return Renderer::getAPI(); }
	
	private:

};

#endif // !RENDER_CORE_H
