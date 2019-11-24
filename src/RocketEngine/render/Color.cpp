#include "Color.h"

Color::Color()
{
	mColorValue = Vector4(0,0,0,255);
}


Color::Color(float r, float g, float b, float a)
{
	mColorValue = Vector4(r, g, b, a);
}


Color::~Color()
{
}

void Color::setColor(Vector3 rgb, float a)
{
	mColorValue = Vector4(rgb, a);
}

void Color::setColor(Vector4 color)
{
	mColorValue = color;
}


void Color::setColor(float r, float g, float b, float a)
{
	mColorValue = Vector4(r, g, b, a);
}


void Color::setColor(float setRGB)
{
	mColorValue = Vector4(setRGB, setRGB, setRGB, setRGB);
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