#include "include/Vector3.h"

namespace rkm {

	Vector3 Vector3::zero(0.0f, 0.0f, 0.0f);
	Vector3 Vector3::one(1.0f, 1.0f, 1.0f);
	Vector3 Vector3::left(-1.0f, 0.0f, 0.0f);
	Vector3 Vector3::right(1.0f, 0.0f, 0.0f);
	Vector3 Vector3::up(0.0f, 1.0f, 0.0f);
	Vector3 Vector3::down(0.0f, -1.0f, 0.0f);
	Vector3 Vector3::forward(0.0f, 0.0f, 1.0f);
	Vector3 Vector3::back(0.0f, 0.0f, -1.0f);

	Vector3::Vector3()
	{
		mX = 0;
		mY = 0;
		mZ = 0;
	};

	Vector3::Vector3(float x, float y, float z)
	{
		mX = x;
		mY = y;
		mZ = z;
	};
	
	Vector3::Vector3(int x, int y, int z) 
	{ 
		mX = (float)x; 
		mY = (float)y; 
		mZ = (float)z; 
	};
	
	Vector3::~Vector3()
	{

	}

	float Vector3::getMagnitude() { return sqrtf((mX*mX) + (mY*mY) + (mZ*mZ)); };
	float Vector3::getSqrMagnitude() { return getMagnitude() * getMagnitude(); };
	Vector3 Vector3::normalize() { return *this / getMagnitude(); };

	//Negation operators
	Vector3 Vector3::operator!()
	{
		Vector3 newVec;
		newVec.mX = -mX;
		newVec.mY = -mY;
		newVec.mZ = -mZ;
		return newVec;
	};

	Vector3 Vector3::operator-()
	{
		Vector3 newVec;
		newVec.mX = -mX;
		newVec.mY = -mY;
		newVec.mZ = -mZ;
		return newVec;
	};

	float Vector3::dot(Vector3 lhs, Vector3 rhs)
	{
		float x = lhs.getX() * rhs.getX();
		float y = lhs.getY() * rhs.getY();
		float z = lhs.getZ() * rhs.getZ();
		return acos(x + y + z);
	};

	Vector3 Vector3::cross(Vector3 a, Vector3 b)
	{
		float x = (a.getY() * b.getZ()) - (a.getZ() * b.getY());
		float y = (a.getZ() * b.getX()) - (a.getX() * b.getZ());
		float z = (a.getX() * b.getY()) - (a.getY() * b.getX());
		return Vector3(x, y, z);
	}

	//Convert Vector object into float collection 
	//(NOTE): Good for referencing uniform values on shaders
	const float* Vector3::toArray() const
	{
		float arr[3] = { mX, mY, mZ };
		return arr;
	}

	//comparison
	bool Vector3::operator==(const Vector3& rhs) 
	{ 
		return mX == rhs.mX && mY == rhs.mY && mZ == rhs.mZ; 
	}
	
	bool Vector3::operator!=(const Vector3& rhs) 
	{ 
		return (mX != rhs.mX) || (mY == rhs.mY) || (mZ != rhs.mZ); 
	}

	//Component-wise overloads
	Vector3 Vector3::operator+(const Vector3& rhs)
	{
		Vector3 newVec;

		newVec.mX = mX + rhs.mX;
		newVec.mY = mY + rhs.mY;
		newVec.mZ = mZ + rhs.mZ;

		return newVec;
	};
	Vector3 Vector3::operator+=(const Vector3& rhs)
	{
		mX = mX + rhs.mX;
		mY = mY + rhs.mY;
		mZ = mZ + rhs.mZ;

		return *this;
	};
	Vector3 Vector3::operator-(const Vector3& rhs)
	{
		Vector3 newVec;

		newVec.mX = mX - rhs.mX;
		newVec.mY = mY - rhs.mY;
		newVec.mZ = mZ - rhs.mZ;

		return newVec;
	};
	Vector3 Vector3::operator-=(const Vector3& rhs)
	{
		mX = mX - rhs.mX;
		mY = mY - rhs.mY;
		mZ = mZ - rhs.mZ;

		return *this;
	};
	Vector3 Vector3::operator/(const Vector3& rhs)
	{
		Vector3 newVec;

		newVec.mX = mX / rhs.mX;
		newVec.mY = mY / rhs.mY;
		newVec.mZ = mZ / rhs.mZ;

		return newVec;
	};
	Vector3 Vector3::operator*(const Vector3& rhs)
	{
		Vector3 newVec;

		newVec.mX = mX * rhs.mX;
		newVec.mY = mY * rhs.mY;
		newVec.mZ = mZ * rhs.mZ;

		return newVec;
	};

	//Scalar overloads
	Vector3 Vector3::operator+(const float& val)
	{
		Vector3 newVec;

		newVec.mX = mX + val;
		newVec.mY = mY + val;
		newVec.mZ = mZ + val;

		return newVec;
	};
	Vector3 Vector3::operator-(const float& val)
	{
		Vector3 newVec;

		newVec.mX = mX - val;
		newVec.mY = mY - val;
		newVec.mZ = mZ - val;

		return newVec;
	};
	Vector3 Vector3::operator*(const float& val)
	{
		Vector3 newVec;

		newVec.mX = mX * val;
		newVec.mY = mY * val;
		newVec.mZ = mZ * val;

		return newVec;
	};
	Vector3 Vector3::operator/(const float& val)
	{
		Vector3 newVec;

		newVec.mX = mX / val;
		newVec.mY = mY / val;
		newVec.mZ = mZ / val;

		return newVec;
	};

	//Output overload
	std::ostream& operator<<(std::ostream& os, const Vector3& vec)
	{
		std::cout << "(" << vec.mX << ", " << vec.mY << ", " << vec.mZ << ")";
		return os;
	};
}