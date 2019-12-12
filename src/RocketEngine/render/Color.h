#ifndef COLOR_H
#define COLOR_H

#include <rkutil/Trackable.h>
#include <rkm/Vector4.h>

class Color : public rkutil::Trackable
{
		
	public:
		Color();
		Color(float r, float g, float b, float a = 255);

		~Color();

		void setColor(rkm::Vector3 rgb, float a = 255);
		void setColor(rkm::Vector4 color);
		void setColor(float setAllRGB);
		void setColor(float r, float g, float b, float a = 255);

		//Get individual rgb values
		float getRedValue();
		float getGreenValue();
		float getBlueValue();
		float getAlphaValue();

	private:
		rkm::Vector4 mColorValue;

};

#endif // !COLOR_H