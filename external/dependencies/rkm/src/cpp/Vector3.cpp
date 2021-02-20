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
		mVecArr[X] = 0;
		mVecArr[Y] = 0;
		mVecArr[Z] = 0;
	};

	Vector3::Vector3(float x, float y, float z)
	{
		mVecArr[X] = x;
		mVecArr[Y] = y;
		mVecArr[Z] = z;
	};
	
	Vector3::Vector3(int x, int y, int z) 
	{ 
		mVecArr[X] = (float)x;
		mVecArr[Y] = (float)y;
		mVecArr[Z] = (float)z;
	};
	
	Vector3::~Vector3()
	{

	}

	float Vector3::getMagnitude() { return sqrtf((mVecArr[X] * mVecArr[X]) + (mVecArr[Y] * mVecArr[Y]) + (mVecArr[Z] * mVecArr[Z])); };
	float Vector3::getSqrMagnitude() { return getMagnitude() * getMagnitude(); };
	Vector3 Vector3::normalize() { return *this / getMagnitude(); };

	//Negation operators
	Vector3 Vector3::operator!()
	{
		Vector3 newVec;
		newVec.mVecArr[X] = -mVecArr[X];
		newVec.mVecArr[Y] = -mVecArr[Y];
		newVec.mVecArr[Z] = -mVecArr[Z];
		return newVec;
	};

	Vector3 Vector3::operator-()
	{
		Vector3 newVec;
		newVec.mVecArr[X] = -mVecArr[X];
		newVec.mVecArr[Y] = -mVecArr[Y];
		newVec.mVecArr[Z] = -mVecArr[Z];
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


	//comparison
	bool Vector3::operator==(const Vector3& rhs) 
	{ 
		return mVecArr[X] == rhs.mVecArr[X] && mVecArr[Y] == rhs.mVecArr[Y] && mVecArr[Z] == rhs.mVecArr[Z];
	}
	
	bool Vector3::operator!=(const Vector3& rhs) 
	{ 
		return (mVecArr[X] != rhs.mVecArr[X]) || (mVecArr[Y] == rhs.mVecArr[Y]) || (mVecArr[Z] != rhs.mVecArr[Z]);
	}

	//Component-wise overloads
	Vector3 Vector3::operator+(const Vector3& rhs)
	{
		Vector3 newVec;

		newVec.mVecArr[X] = mVecArr[X] + rhs.mVecArr[X];
		newVec.mVecArr[Y] = mVecArr[Y] + rhs.mVecArr[Y];
		newVec.mVecArr[Z] = mVecArr[Z] + rhs.mVecArr[Z];

		return newVec;
	};
	Vector3 Vector3::operator+=(const Vector3& rhs)
	{
		mVecArr[X] = mVecArr[X] + rhs.mVecArr[X];
		mVecArr[Y] = mVecArr[Y] + rhs.mVecArr[Y];
		mVecArr[Z] = mVecArr[Z] + rhs.mVecArr[Z];

		return *this;
	};
	Vector3 Vector3::operator-(const Vector3& rhs)
	{
		Vector3 newVec;

		newVec.mVecArr[X] = mVecArr[X] - rhs.mVecArr[X];
		newVec.mVecArr[Y] = mVecArr[Y] - rhs.mVecArr[Y];
		newVec.mVecArr[Z] = mVecArr[Z] - rhs.mVecArr[Z];

		return newVec;
	};
	Vector3 Vector3::operator-=(const Vector3& rhs)
	{
		mVecArr[X] = mVecArr[X] - rhs.mVecArr[X];
		mVecArr[Y] = mVecArr[Y] - rhs.mVecArr[Y];
		mVecArr[Z] = mVecArr[Z] - rhs.mVecArr[Z];

		return *this;
	};
	Vector3 Vector3::operator/(const Vector3& rhs)
	{
		Vector3 newVec;

		newVec.mVecArr[X] = mVecArr[X] / rhs.mVecArr[X];
		newVec.mVecArr[Y] = mVecArr[Y] / rhs.mVecArr[Y];
		newVec.mVecArr[Z] = mVecArr[Z] / rhs.mVecArr[Z];

		return newVec;
	};
	Vector3 Vector3::operator*(const Vector3& rhs)
	{
		Vector3 newVec;

		newVec.mVecArr[X] = mVecArr[X] * rhs.mVecArr[X];
		newVec.mVecArr[Y] = mVecArr[Y] * rhs.mVecArr[Y];
		newVec.mVecArr[Z] = mVecArr[Z] * rhs.mVecArr[Z];

		return newVec;
	};

	//Scalar overloads
	Vector3 Vector3::operator+(const float& val)
	{
		Vector3 newVec;

		newVec.mVecArr[X] = mVecArr[X] + val;
		newVec.mVecArr[Y] = mVecArr[Y] + val;
		newVec.mVecArr[Z] = mVecArr[Z] + val;

		return newVec;
	};
	Vector3 Vector3::operator-(const float& val)
	{
		Vector3 newVec;

		newVec.mVecArr[X] = mVecArr[X] - val;
		newVec.mVecArr[Y] = mVecArr[Y] - val;
		newVec.mVecArr[Z] = mVecArr[Z] - val;

		return newVec;
	};
	Vector3 Vector3::operator*(const float& val)
	{
		Vector3 newVec;

		newVec.mVecArr[X] = mVecArr[X] * val;
		newVec.mVecArr[Y] = mVecArr[Y] * val;
		newVec.mVecArr[Z] = mVecArr[Z] * val;

		return newVec;
	};
	Vector3 Vector3::operator/(const float& val)
	{
		Vector3 newVec;

		newVec.mVecArr[X] = mVecArr[X] / val;
		newVec.mVecArr[Y] = mVecArr[Y] / val;
		newVec.mVecArr[Z] = mVecArr[Z] / val;

		return newVec;
	};

	//Output overload
	std::ostream& operator<<(std::ostream& os, const Vector3& vec)
	{
		std::cout << "(" << vec.mVecArr[0] << ", " << vec.mVecArr[1] << ", " << vec.mVecArr[2] << ")";
		return os;
	};
}