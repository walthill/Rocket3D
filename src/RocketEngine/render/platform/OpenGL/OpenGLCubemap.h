#ifndef OPENGL_CUBEMAP_H
#define OPENGL_CUBEMAP_H

#include "../../buffers/Texture.h"

class OpenGLCubemap : public CubemapTexture
{
	public:
		OpenGLCubemap(std::vector<std::string> faces, int sWrapParam = WrapType::CLAMP_EDGE, int tWrapParam = WrapType::CLAMP_EDGE,
					  int rWrapParam = WrapType::CLAMP_EDGE, int miniFilter = MinifyFilter::MIN_LINEAR, 
					  int magFilter = MagnifyFilter::MAG_LINEAR, int detailReductionLevel = 0);

		~OpenGLCubemap();

		virtual uint32 getWidth()	const override { return mWidth; }
		virtual uint32 getHeight()	const override { return mHeight; }
		virtual uint32 getId()		const override { return mRendererId; }

		virtual void bind()			const override;

	private:
		uint32 mWidth, mHeight;
		std::string mPath;
		uint32 mRendererId;
		static const int BORDER_DEFAULT; //"this value must be zero"
};


#endif // !OPENGL_CUBEMAP_H
