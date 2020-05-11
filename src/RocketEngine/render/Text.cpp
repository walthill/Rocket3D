#include "Text.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>
#include "../shader/RK_Shader.h"
#include <glfw3.h>

Text::Text(std::string fontName, RK_Shader * shader)
{
	init(fontName, shader);
}

Text::~Text()
{
	destroy();
}

void Text::init(std::string fontName, RK_Shader *shader)
{
	mpShader = shader;

	// FreeType
	FT_Library ft;

	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, (mFONT_ASSET_PATH + fontName).c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			rkm::Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			rkm::Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(uint32)face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// Configure VAO/VBO for texture quads
	glyphVA.reset(VertexArray::create());

	glyphVB.reset(VertexBuffer::create(nullptr, sizeof(GLfloat) * 6 * 4, VertexBuffer::DataType::DYNAMIC));

	BufferLayout layout = {
		{ ShaderDataType::Float4, "vertex" }
	};

	glyphVB->setLayout(layout);
	glyphVA->addVertexBuffer(glyphVB);

	glyphVB->unbind();
	glyphVA->unbind();
}

void Text::initTextData(TextData data)
{
	mTextData.text = data.text;
	mTextData.position = data.position;
	mTextData.scale = data.scale;
	mTextData.color = data.color;
}

void Text::destroy()
{
	mpShader = nullptr;
}

void Text::renderText()
{
	renderText(mTextData);
}

void Text::renderText(TextData data)
{
	// Activate corresponding render state	
	mpShader->use();

	//shader.setVec3("textColor", color);
	int val = glGetUniformLocation(mpShader->shaderID, mTEXT_COLOR_UNIFORM);

	//allow for values from 0 to 255
	glUniform3f(val, data.color.getR01(), 
					 data.color.getG01(), 
					 data.color.getB01());

	glActiveTexture(GL_TEXTURE0);
	glyphVA->bind();

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = data.text.begin(); c != data.text.end(); c++)
	{
		Character ch = characters[*c];

		GLfloat xpos = data.position.getX() + ch.bearing.getX() * data.scale;
		GLfloat ypos = data.position.getY() - (ch.size.getY() - ch.bearing.getY()) * data.scale;

		GLfloat w = ch.size.getX() * data.scale;
		GLfloat h = ch.size.getY() * data.scale;
		// Update VBO for each character
		float vertices[] = {
			 xpos,     ypos + h,   0.0, 0.0 ,
			 xpos,     ypos,       0.0, 1.0 ,
			 xpos + w, ypos,       1.0, 1.0 ,

			 xpos,     ypos + h,   0.0, 0.0 ,
			 xpos + w, ypos,       1.0, 1.0 ,
			 xpos + w, ypos + h,   1.0, 0.0 
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureId);
		// Update content of VBO memory
		//glyphVB.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		glyphVB->bind();//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glyphVB->updateBufferData(vertices, sizeof(vertices), 0);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
		glyphVB->unbind();

		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		float x = (ch.advance >> 6) * data.scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		data.position = rkm::Vector2(data.position.getX() + x, data.position.getY());
	}
	glyphVA->unbind();
	glBindTexture(GL_TEXTURE_2D, 0);
}


