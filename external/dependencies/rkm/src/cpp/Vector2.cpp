#include "include/Vector2.h"

namespace rkm {

	Vector2 Vector2::zero(0.0f, 0.0f);
	Vector2 Vector2::one(1.0f, 1.0f);
	Vector2 Vector2::left(-1.0f, 0.0f);
	Vector2 Vector2::right(1.0f, 0.0f);
	Vector2 Vector2::up(0.0f, 1.0f);
	Vector2 Vector2::down(0.0f, -1.0f);	

	Vector2::Vector2() 
	{

	}

	Vector2::Vector2(float x, float y) 
	{ 
		mVecArr[X] = x;
		mVecArr[Y] = y;
	}

	Vector2::Vector2(int x, int y) 
	{ 
		mVecArr[X] = (float)x;
		mVecArr[Y] = (float)y;
	};

	Vector2::Vector2(unsigned int x, unsigned int y) 
	{ 
		mVecArr[X] = (float)x;
		mVecArr[Y] = (float)y;
	};

	float Vector2::getMagnitude() { return sqrtf((mVecArr[X] * mVecArr[X]) + (mVecArr[Y] * mVecArr[Y])); };
	float Vector2::getSqrMagnitude() { return getMagnitude() * getMagnitude(); };
	Vector2 Vector2::normalize() { return *this / getMagnitude(); };

	//Negation operators
	Vector2 Vector2::operator!()
	{
		Vector2 newVec;
		newVec.mVecArr[X] = -mVecArr[X];
		newVec.mVecArr[X] = -mVecArr[X];
		return newVec;
	}

	Vector2 Vector2::operator-()
	{
		Vector2 newVec;
		newVec.mVecArr[X] = -mVecArr[X];
		newVec.mVecArr[X] = -mVecArr[X];
		return newVec;
	}

	float Vector2::dot(Vector2 lhs, Vector2 rhs)
	{
		float x = lhs.getX() * rhs.getX();
		float y = lhs.getY() * rhs.getY();

		return acos(x + y);
	}

	//comparison
	bool Vector2::operator==(const Vector2& rhs) 
	{ 
		return mVecArr[X] == rhs.mVecArr[X] && mVecArr[Y] == rhs.mVecArr[Y];
	}

	bool Vector2::operator!=(const Vector2& rhs) 
	{ 
		return (mVecArr[X] != rhs.mVecArr[X]) || (mVecArr[Y] == rhs.mVecArr[Y]);
	}

	//Component-wise overloads
	Vector2 Vector2::operator+(const Vector2& rhs)
	{
		Vector2 newVec;

		newVec.mVecArr[X] = mVecArr[X] + rhs.mVecArr[X];
		newVec.mVecArr[Y] = mVecArr[Y] + rhs.mVecArr[Y];

		return newVec;
	};

	Vector2 Vector2::operator-(const Vector2& rhs)
	{
		Vector2 newVec;

		newVec.mVecArr[X] = mVecArr[X] - rhs.mVecArr[X];
		newVec.mVecArr[Y] = mVecArr[Y] - rhs.mVecArr[Y];

		return newVec;
	};
	Vector2 Vector2::operator/(const Vector2& rhs)
	{
		Vector2 newVec;

		newVec.mVecArr[X] = mVecArr[X] / rhs.mVecArr[X];
		newVec.mVecArr[Y] = mVecArr[Y] / rhs.mVecArr[Y];

		return newVec;
	};

	//Scalar overloads
	Vector2 Vector2::operator+(const float& val)
	{
		Vector2 newVec;

		newVec.mVecArr[X] = mVecArr[X] + val;
		newVec.mVecArr[Y] = mVecArr[Y] + val;

		return newVec;
	};

	Vector2 Vector2::operator-(const float& val)
	{
		Vector2 newVec;

		newVec.mVecArr[X] = mVecArr[X] - val;
		newVec.mVecArr[Y] = mVecArr[Y] - val;

		return newVec;
	};
	Vector2 Vector2::operator*(const float& val)
	{
		Vector2 newVec;

		newVec.mVecArr[X] = mVecArr[X] * val;
		newVec.mVecArr[Y] = mVecArr[Y] * val;

		return newVec;
	};
	Vector2 Vector2::operator/(const float& val)
	{
		Vector2 newVec;

		newVec.mVecArr[X] = mVecArr[X] / val;
		newVec.mVecArr[Y] = mVecArr[Y] / val;

		return newVec;
	};

	//Output overload
	std::ostream& operator<<(std::ostream& os, const Vector2& vec)
	{
		std::cout << "(" << vec.mVecArr[0] << ", " << vec.mVecArr[1] << ")";
		return os;
	};

}