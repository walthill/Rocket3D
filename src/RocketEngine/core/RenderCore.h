#ifndef RENDER_CORE_H
#define RENDER_CORE_H

#include <rkutil/Trackable.h>
#include "../render/buffers/VertexArray.h"
#include "../render/RenderCommand.h"
#include <map>

struct VertexRenderData
{
	std::shared_ptr<VertexArray> mVertexArray;
	uint32 mInstanceCount = 0;
	
	VertexRenderData() : mVertexArray(nullptr), mInstanceCount(1) {};
	VertexRenderData(const std::shared_ptr<VertexArray>& vertexArray, uint32 instanceCount = 1) : 
		mVertexArray(vertexArray), mInstanceCount(instanceCount) {};
};

class RenderCore : public rkutil::Trackable
{
	public:
		static void beginScene();
		static void endScene();
		static void submit(const std::shared_ptr<VertexArray>& vertexArray);
		static void submit(const std::shared_ptr<VertexArray>& vertexArray, uint32 instanceCount);

		static void submitInstanced(std::shared_ptr<VertexArray> vertexArray, uint32 instanceCount);

		static void flush();

		inline static Renderer::API getAPI() { return Renderer::getAPI(); }
		
	private:
		static std::map<uint32, VertexRenderData> mVertexArrays;
		static std::map<uint32, VertexRenderData> mTransparentVAs;
};

#endif // !RENDER_CORE_H
