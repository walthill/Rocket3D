#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../util/EngineUtils.h"

class Texture
{
	public:
		enum WrapType { REPEAT = 0, MIRRORED_REPEAT, CLAMP_EDGE };
	
		enum MinifyFilter 
		{ 
			MIN_LINEAR = 0, MIN_NEAREST,
			NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR
		};

		enum MagnifyFilter { MAG_LINEAR = 0, MAG_NEAREST };

	public:
		virtual ~Texture() {};
		virtual uint32 getWidth()	const PURE_VIRTUAL;
		virtual uint32 getHeight()	const PURE_VIRTUAL;
		virtual uint32 getId()		const PURE_VIRTUAL;

		virtual void bind()			const PURE_VIRTUAL;

	private:
};

class Texture2D : public Texture
{
	public:
		static Texture2D* create(const std::string& path, int sWrapParam = WrapType::REPEAT, int tWrapParam = WrapType::REPEAT,
			int miniFilter = MinifyFilter::MIN_LINEAR, int magFilter = MagnifyFilter::MAG_LINEAR, int detailReductionLevel = 0);

	private:
};

#endif // !TEXTURE_H
