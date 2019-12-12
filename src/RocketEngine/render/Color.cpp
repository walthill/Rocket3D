#include "Color.h"

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