#ifndef VEC2_H
#define VEC2_H

#include <ostream>
#include <iostream>

class Vector2
{
public:
	Vector2() {};
	Vector2(float x, float y) { mX = x; mY = y; };
	Vector2(int x, int y) { mX = (float)x; mY = (float)y; };

	float getMagnitude() { return sqrtf((mX*mX) + (mY*mY)); };
	float getSqrMagnitude() { return getMagnitude() * getMagnitude(); };
	Vector2 normalize() { return *this / getMagnitude(); };

	//Negation operators
	Vector2 operator!()
	{
		Vector2 newVec;
		newVec.mX = -mX;
		newVec.mY = -mY;
		return newVec;
	};

	Vector2 operator-()
	{
		Vector2 newVec;
		newVec.mX = -mX;
		newVec.mY = -mY;
		return newVec;
	};

	static float dot(Vector2 lhs, Vector2 rhs)
	{
		float x = lhs.getX() * rhs.getX();
		float y = lhs.getY() * rhs.getY();

		return acos(x + y);
	};

	//comparison
	bool operator==(const Vector2& rhs) { return mX == rhs.mX && mY == rhs.mY; };
	bool operator!=(const Vector2& rhs) { return (mX != rhs.mX) || (mY == rhs.mY); };

	//Component-wise overloads
	Vector2 operator+(const Vector2& rhs)
	{
		Vector2 newVec;

		newVec.mX = mX + rhs.mX;
		newVec.mY = mY + rhs.mY;

		return newVec;
	};
	Vector2 operator-(const Vector2& rhs)
	{
		Vector2 newVec;

		newVec.mX = mX - rhs.mX;
		newVec.mY = mY - rhs.mY;

		return newVec;
	};
	Vector2 operator/(const Vector2& rhs)
	{
		Vector2 newVec;

		newVec.mX = mX / rhs.mX;
		newVec.mY = mY / rhs.mY;

		return newVec;
	};

	//Scalar overloads
	Vector2 operator+(const float& val)
	{
		Vector2 newVec;

		newVec.mX = mX + val;
		newVec.mY = mY + val;

		return newVec;
	};

	Vector2 operator-(const float& val)
	{
		Vector2 newVec;

		newVec.mX = mX - val;
		newVec.mY = mY - val;

		return newVec;
	};
	Vector2 operator*(const float& val)
	{
		Vector2 newVec;

		newVec.mX = mX * val;
		newVec.mY = mY * val;

		return newVec;
	};
	Vector2 operator/(const float& val)
	{
		Vector2 newVec;

		newVec.mX = mX / val;
		newVec.mY = mY / val;

		return newVec;
	};

	//Output overload
	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec)
	{
		std::cout << "(" << vec.mX << ", " << vec.mY << ")";
		return os;
	};

	float getX() const { return mX; };
	float getY() const { return mY; };

	static Vector2 left, right, up, down, one, zero;

private:
	float mX, mY;
};

#endif // !VEC2_H
