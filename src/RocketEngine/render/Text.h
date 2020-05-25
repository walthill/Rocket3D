#ifndef TEXT_H
#define TEXT_H

#include <rkutil/Trackable.h>
#include <rkm/Vector2.h>
#include "Color.h"
#include "../util/EngineUtils.h"

struct TextData
{
	std::string text;
	Color color;
	rkm::Vector2 position;
	float scale;
};

class RK_Shader;

class Text : public rkutil::Trackable
{
	public:
		virtual ~Text() {};

		static Text* create(std::string fontName, RK_Shader *shader);
		void initTextData(TextData data);

		virtual void renderText() PURE_VIRTUAL;
		virtual void renderText(TextData data) PURE_VIRTUAL;
		
		inline void setText(std::string newText) { mTextData.text = newText; }
		inline std::string getText() { return mTextData.text; }

	protected:
		const float RGB01_CONVERSION = 0.00392156863f;
		const std::string mFONT_ASSET_PATH = "../../assets/fonts/";

		TextData mTextData;		
};

#endif // !TEXT_H
