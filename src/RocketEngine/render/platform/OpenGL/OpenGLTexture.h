#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "../../buffers/Texture.h"

class OpenGLTexture2D : public Texture2D 
{
	public:
		OpenGLTexture2D(const std::string& path, int detailReductionLevel = 0);
		~OpenGLTexture2D();

		virtual uint32 getWidth()	const override { return mWidth; }
		virtual uint32 getHeight()	const override { return mHeight; }

		virtual void bind()			const override;

	private:
		uint32 mWidth, mHeight;
		std::string mPath;
		uint32 mRendererId;
		static const int BORDER_DEFAULT; //"this value must be zero"
};


#endif // !OPENGL_TEXTURE_H
