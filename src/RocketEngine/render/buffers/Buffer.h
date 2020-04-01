#ifndef BUFFER_H
#define BUFFER_H

#include "../../util/EngineUtils.h"

//abstract classes
class VertexBuffer
{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const PURE_VIRTUAL;
		virtual void Unbind() const PURE_VIRTUAL;

		static VertexBuffer* Create(float* vertices, uint32 size);
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

class FrameBuffer
{
	public:		
		virtual ~FrameBuffer() {}

		  virtual void Bind() const PURE_VIRTUAL;
		  virtual void Unbind() const PURE_VIRTUAL;

		  virtual uint32 getTextureId() const PURE_VIRTUAL;

		  static FrameBuffer* Create(int width, int height);
	private:
};

#endif