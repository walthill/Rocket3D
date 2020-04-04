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
	RenderCommand::drawIndexed(vertexArray);	//can be array draw or index draw
}
