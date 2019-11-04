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
		mX = x; 
		mY = y; 
	}

	Vector2::Vector2(int x, int y) 
	{ 
		mX = (float)x; 
		mY = (float)y; 
	};

	Vector2::Vector2(unsigned int x, unsigned int y) 
	{ 
		mX = (float)x; 
		mY = (float)y; 
	};

	float Vector2::getMagnitude() { return sqrtf((mX*mX) + (mY*mY)); };
	float Vector2::getSqrMagnitude() { return getMagnitude() * getMagnitude(); };
	Vector2 Vector2::normalize() { return *this / getMagnitude(); };

	//Negation operators
	Vector2 Vector2::operator!()
	{
		Vector2 newVec;
		newVec.mX = -mX;
		newVec.mY = -mY;
		return newVec;
	}

	Vector2 Vector2::operator-()
	{
		Vector2 newVec;
		newVec.mX = -mX;
		newVec.mY = -mY;
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
		return mX == rhs.mX && mY == rhs.mY; 
	}

	bool Vector2::operator!=(const Vector2& rhs) 
	{ 
		return (mX != rhs.mX) || (mY == rhs.mY); 
	}

	//Component-wise overloads
	Vector2 Vector2::operator+(const Vector2& rhs)
	{
		Vector2 newVec;

		newVec.mX = mX + rhs.mX;
		newVec.mY = mY + rhs.mY;

		return newVec;
	};

	Vector2 Vector2::operator-(const Vector2& rhs)
	{
		Vector2 newVec;

		newVec.mX = mX - rhs.mX;
		newVec.mY = mY - rhs.mY;

		return newVec;
	};
	Vector2 Vector2::operator/(const Vector2& rhs)
	{
		Vector2 newVec;

		newVec.mX = mX / rhs.mX;
		newVec.mY = mY / rhs.mY;

		return newVec;
	};

	//Scalar overloads
	Vector2 Vector2::operator+(const float& val)
	{
		Vector2 newVec;

		newVec.mX = mX + val;
		newVec.mY = mY + val;

		return newVec;
	};

	Vector2 Vector2::operator-(const float& val)
	{
		Vector2 newVec;

		newVec.mX = mX - val;
		newVec.mY = mY - val;

		return newVec;
	};
	Vector2 Vector2::operator*(const float& val)
	{
		Vector2 newVec;

		newVec.mX = mX * val;
		newVec.mY = mY * val;

		return newVec;
	};
	Vector2 Vector2::operator/(const float& val)
	{
		Vector2 newVec;

		newVec.mX = mX / val;
		newVec.mY = mY / val;

		return newVec;
	};

	//Output overload
	std::ostream& operator<<(std::ostream& os, const Vector2& vec)
	{
		std::cout << "(" << vec.mX << ", " << vec.mY << ")";
		return os;
	};

}