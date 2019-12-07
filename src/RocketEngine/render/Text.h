#ifndef TEXT_H
#define TEXT_H

#include <rkutil/Trackable.h>
#include <RocketMath/Vector2.h>
#include <RocketMath/Vector3.h>
#include "Color.h"
#include "../util/EngineUtils.h"
#include <map>

struct TextData
{
	std::string text;
	Color color;
	Vector2 position;
	float scale;
};

class RK_Shader;

class Text : public rkutil::Trackable
{
	public:
		Text();
		Text(std::string fontName, RK_Shader *shader);
		~Text();

		void init(std::string fontName, RK_Shader *shader);
		void initTextData(TextData data);
		void destroy();

		void renderText();
		void renderText(TextData data);

		void setText(std::string newText) { mTextData.text = newText; }
		std::string getText() { return mTextData.text; }

	private:
		struct Character 
		{
			uint32 textureId;
			Vector2 size;
			Vector2 bearing;
			uint32 advance;
		};

		const float RGB01_CONVERSION = 0.00392156863f;
		const char* mTEXT_COLOR_UNIFORM = "textColor";
		const std::string mFONT_ASSET_PATH = "../../assets/fonts/";
		
		TextData mTextData;
		RK_Shader* mpShader;
		uint32 VAO, VBO;
		std::map<char, Character> characters;
};

#endif // !TEXT_H
