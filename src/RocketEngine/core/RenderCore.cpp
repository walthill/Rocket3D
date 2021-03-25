#include "RenderCore.h"

std::map<uint32, VertexRenderData> RenderCore::mVertexArrays = std::map<uint32, VertexRenderData>();
std::map<uint32, VertexRenderData> RenderCore::mTransparentVAs = std::map<uint32, VertexRenderData>();

void RenderCore::beginScene()
{
}

void RenderCore::endScene()
{
	flush();
}

void RenderCore::submit(const std::shared_ptr<VertexArray>& vertexArray)
{
	//TODO: submit to render list. encountering a bug where planet verts break if rendered second
	//mVertexArrays[vertexArray->getId()] = { vertexArray };

	vertexArray->bind();
	if (vertexArray->getIndexBuffer() != nullptr)
		RenderCommand::drawIndexed(vertexArray);	
	else
		RenderCommand::drawTriangles(vertexArray);
}


void RenderCore::submit(const std::shared_ptr<VertexArray>& vertexArray, uint32 instanceCount)
{
	vertexArray->bind();
	RenderCommand::drawInstancedTriangles(vertexArray, instanceCount);
}

void RenderCore::submitInstanced(std::shared_ptr<VertexArray> vertexArray, uint32 instanceCount)
{
	mVertexArrays[vertexArray->getId()] = { vertexArray, instanceCount };
}

void RenderCore::flush()
{
	//render opaque objects & remove from render list
	for (auto& va : mVertexArrays)
	{
		if (va.second.mInstanceCount > 1)
		{
			auto& vert = va.second.mVertexArray;
			vert->bind();
			RenderCommand::drawInstanced(vert, va.second.mInstanceCount);
			vert->unbind();
		}
		else
		{
			auto& vert = va.second.mVertexArray;
			vert->bind();

			if (vert->getIndexBuffer() != nullptr)
				RenderCommand::drawIndexed(vert);
			else
				RenderCommand::drawTriangles(vert);
			
			vert->unbind();
		}
	}


	//render transparent objects
	for (auto& transparentVA : mTransparentVAs)
	{
		if (transparentVA.second.mInstanceCount > 1)
		{
			auto& vert = transparentVA.second.mVertexArray;
			vert->bind();
			RenderCommand::drawInstanced(vert, transparentVA.second.mInstanceCount);
			vert->unbind();
		}
		else
		{
			auto& vert = transparentVA.second.mVertexArray;
			vert->bind();
			
			if (vert->getIndexBuffer() != nullptr)
				RenderCommand::drawIndexed(vert);	
			else
				RenderCommand::drawTriangles(vert);	
			
			vert->unbind();
		}
	}

	mVertexArrays.clear();
	mTransparentVAs.clear();
}