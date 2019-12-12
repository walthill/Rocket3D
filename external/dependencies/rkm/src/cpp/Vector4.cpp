#include "include/Vector4.h"

namespace rkm {

	Vector4::Vector4() 
	{ 
		mX = 0; 
		mY = 0; 
		mZ = 0; 
	}

	Vector4::Vector4(Vector3 vec, float w) 
	{ 
		mX = vec.getX(); 
		mX = vec.getX(); 
		mY = vec.getY(); 
		mZ = vec.getZ(); 
		mW = w; 
	}

	Vector4::Vector4(float x, float y, float z, float w) 
	{ 
		mX = x; mY = y; mZ = z; mW = w; 
	}

	Vector4::Vector4(int x, int y, int z, int w) 
	{ 
		mX = (float)x; 
		mY = (float)y; 
		mZ = (float)z; 
		mW = (float)w; 
	}

	Vector4::~Vector4() {};

	float Vector4::getMagnitude() { return sqrtf((mX*mX) + (mY*mY) + (mZ*mZ) + (mW*mW)); };
	float Vector4::getSqrMagnitude() { return getMagnitude() * getMagnitude(); };
	Vector4 Vector4::normalize() { return *this / getMagnitude(); };

	//Negation operators
	Vector4 Vector4::operator!()
	{
		Vector4 newVec;
		newVec.mX = -mX;
		newVec.mY = -mY;
		newVec.mZ = -mZ;
		newVec.mW = -mW;

		return newVec;
	}

	Vector4 Vector4::operator-()
	{
		Vector4 newVec;
		newVec.mX = -mX;
		newVec.mY = -mY;
		newVec.mZ = -mZ;
		newVec.mW = -mW;

		return newVec;
	}

	float Vector4::dot(Vector4 lhs, Vector4 rhs)
	{
		float x = lhs.getX() * rhs.getX();
		float y = lhs.getY() * rhs.getY();
		float z = lhs.getZ() * rhs.getZ();
		float w = lhs.getW() * rhs.getW();
		return acos(x + y + z + w);
	}

	//comparison
	bool Vector4::operator==(const Vector4& rhs) { return mX == rhs.mX && mY == rhs.mY && mZ == rhs.mZ; };
	bool Vector4::operator!=(const Vector4& rhs) { return (mX != rhs.mX) || (mY == rhs.mY) || (mZ != rhs.mZ); };

	//Component-wise overloads
	Vector4 Vector4::operator+(const Vector4& rhs)
	{
		Vector4 newVec;

		newVec.mX = mX + rhs.mX;
		newVec.mY = mY + rhs.mY;
		newVec.mZ = mZ + rhs.mZ;
		newVec.mW = mW + rhs.mW;

		return newVec;
	}

	Vector4 Vector4::operator-(const Vector4& rhs)
	{
		Vector4 newVec;

		newVec.mX = mX - rhs.mX;
		newVec.mY = mY - rhs.mY;
		newVec.mZ = mZ - rhs.mZ;
		newVec.mW = mW - rhs.mW;


		return newVec;
	}

	Vector4 Vector4::operator/(const Vector4& rhs)
	{
		Vector4 newVec;

		newVec.mX = mX / rhs.mX;
		newVec.mY = mY / rhs.mY;
		newVec.mZ = mZ / rhs.mZ;
		newVec.mW = mW / rhs.mW;

		return newVec;
	}

	//Scalar overloads
	Vector4 Vector4::operator+(const float& val)
	{
		Vector4 newVec;

		newVec.mX = mX + val;
		newVec.mY = mY + val;
		newVec.mZ = mZ + val;
		newVec.mW = mW + val;

		return newVec;
	}

	Vector4 Vector4::operator-(const float& val)
	{
		Vector4 newVec;

		newVec.mX = mX - val;
		newVec.mY = mY - val;
		newVec.mZ = mZ - val;
		newVec.mW = mW - val;

		return newVec;
	}

	Vector4 Vector4::operator*(const float& val)
	{
		Vector4 newVec;

		newVec.mX = mX * val;
		newVec.mY = mY * val;
		newVec.mZ = mZ * val;
		newVec.mW = mW * val;

		return newVec;
	}

	Vector4 Vector4::operator/(const float& val)
	{
		Vector4 newVec;

		newVec.mX = mX / val;
		newVec.mY = mY / val;
		newVec.mZ = mZ / val;
		newVec.mW = mW / val;

		return newVec;
	}

	//Output overload
	std::ostream& operator<<(std::ostream& os, const Vector4& vec)
	{
		std::cout << "(" << vec.mX << ", " << vec.mY << ", " << vec.mZ << ", " << vec.mW << ")";
		return os;
	}
}