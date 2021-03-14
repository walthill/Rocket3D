#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "Buffer.h"

class VertexArray : public rkutil::Trackable
{
	public:
		virtual ~VertexArray() {}

		virtual void bind() const PURE_VIRTUAL;
		virtual void unbind() const PURE_VIRTUAL;

		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) PURE_VIRTUAL;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) PURE_VIRTUAL;

		virtual void processVertexBuffers() PURE_VIRTUAL;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() PURE_VIRTUAL;
		virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() PURE_VIRTUAL;

		static VertexArray* create();

	private:
};


#endif // !VERTEX_ARRAY_H
