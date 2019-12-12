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


		static Color black; // (0, 0, 0)
		static Color white; // (255,255,255)
		static Color grey; // (127.5, 127.5,127.5)

		static Color red; // (255,0,0)
		static Color green; // (0,255,0)
		static Color blue; // (0,0,255)

		static Color clear; // (0, 0, 0, 0)

	private:
		rkm::Vector4 mColorValue;

};

#endif // !COLOR_H