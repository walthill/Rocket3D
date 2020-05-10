#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../util/EngineUtils.h"

class Texture
{
	public:
		virtual ~Texture() {};
		virtual uint32 getWidth()	const PURE_VIRTUAL;
		virtual uint32 getHeight()	const PURE_VIRTUAL;

		virtual void bind()			const PURE_VIRTUAL;

	private:
};

class Texture2D : public Texture
{
	public:
		static Texture2D* create(const std::string& path);
		virtual void bind()			const PURE_VIRTUAL;

	private:
};

#endif // !TEXTURE_H
