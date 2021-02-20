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
		inline float getR() { return mColorValue.getX(); }
		inline float getG() { return mColorValue.getY(); }
		inline float getB() { return mColorValue.getZ(); }
		inline float getA() { return mColorValue.getW(); }
		
		//Get rgb values normalized btwn 0,1
		inline float getR01() { return mColorValue.getX() * RGB01_CONVERSION; }
		inline float getG01() { return mColorValue.getY() * RGB01_CONVERSION; }
		inline float getB01() { return mColorValue.getZ() * RGB01_CONVERSION; }
		inline float getA01() { return mColorValue.getW() * RGB01_CONVERSION; }


		static Color black; // (0, 0, 0)
		static Color white; // (255,255,255)
		static Color grey; // (127.5, 127.5,127.5)

		static Color red; // (255,0,0)
		static Color green; // (0,255,0)
		static Color blue; // (0,0,255)

		static Color clear; // (0, 0, 0, 0)

	private:
		rkm::Vector4 mColorValue;
		static const float RGB01_CONVERSION; 


};

#endif // !COLOR_H