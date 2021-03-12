#include "RenderCore.h"

void RenderCore::beginScene()
{
}

void RenderCore::endScene()
{
}

void RenderCore::submit(const std::shared_ptr<VertexArray>& vertexArray)
{
	vertexArray->bind();
	if (vertexArray->getIndexBuffer() != nullptr)
		RenderCommand::drawIndexed(vertexArray);	//can be array draw or index draw
	else
		RenderCommand::drawTriangles(vertexArray);	//can be array draw or index draw

}


void RenderCore::submit(const std::shared_ptr<VertexArray>& vertexArray, uint32 instanceCount)
{
	vertexArray->bind();
	RenderCommand::drawInstancedTriangles(vertexArray, instanceCount);
}