#ifndef BUFFER_H
#define BUFFER_H

#include "../util/EngineUtils.h"

struct VertexData;

//abstract classes
class VertexBuffer
{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const PURE_VIRTUAL;
		virtual void Unbind() const PURE_VIRTUAL;

		static VertexBuffer* Create(VertexData* vertices, uint32 size);
	private:
};

class IndexBuffer //Synonomous w/ EBOs
{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const PURE_VIRTUAL;
		virtual void Unbind() const PURE_VIRTUAL;

		virtual uint32 getCount() const PURE_VIRTUAL;

		static IndexBuffer* Create(uint32* indicies, uint32 size);
	private:
};

#endif