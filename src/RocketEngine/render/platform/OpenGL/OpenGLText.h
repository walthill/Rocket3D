#ifndef OPENGL_TEXT_H
#define OPENGL_TEXT_H

#include "../../Text.h"
#include <map>

#include "../../buffers/VertexArray.h"

class OpenGLText : public Text
{
	public:
		OpenGLText(std::string fontName, RK_Shader* shader);
		~OpenGLText();

		virtual void renderText() override;
		virtual void renderText(TextData data) override;

	private:
		struct Character
		{
			uint32 textureId;
			rkm::Vector2 size;
			rkm::Vector2 bearing;
			uint32 advance;
		};

		const char* mTEXT_COLOR_UNIFORM = "textColor";

		RK_Shader* mpShader;
		std::shared_ptr<IndexBuffer> glyphIB;
		std::shared_ptr<VertexBuffer> glyphVB;
		std::shared_ptr<VertexArray> glyphVA;

		std::map<char, Character> characters;
};

#endif // !OPENGL_TEXT_H

