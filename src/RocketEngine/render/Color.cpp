#include "Color.h"

Color Color::black(0, 0, 0);
Color Color::white(255, 255, 255);
Color Color::grey(127.5f, 127.5f, 127.5f);

Color Color::red(255, 0, 0); 
Color Color::green(0, 255, 0);
Color Color::blue(0, 0, 255); 

Color Color::clear(0, 0, 0, 0);

Color::Color()
{
	mColorValue = rkm::Vector4(0,0,0,255);
}


Color::Color(float r, float g, float b, float a)
{
	mColorValue = rkm::Vector4(r, g, b, a);
}


Color::~Color()
{
}

void Color::setColor(rkm::Vector3 rgb, float a)
{
	mColorValue = rkm::Vector4(rgb, a);
}

void Color::setColor(rkm::Vector4 color)
{
	mColorValue = color;
}


void Color::setColor(float r, float g, float b, float a)
{
	mColorValue = rkm::Vector4(r, g, b, a);
}


void Color::setColor(float setRGB)
{
	mColorValue = rkm::Vector4(setRGB, setRGB, setRGB, setRGB);
}


float Color::getRedValue()
{
	return mColorValue.getX();
}


float Color::getGreenValue()
{
	return mColorValue.getY();
}


float Color::getBlueValue()
{
	return mColorValue.getZ();
}


float Color::getAlphaValue()
{
	return mColorValue.getW();
}