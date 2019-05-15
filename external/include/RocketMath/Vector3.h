#ifndef VEC3_H
#define VEC3_H

#include <ostream>
#include <iostream>

//TODO(low): worth moving code into cpp file?

// Contains code for Vec2, Vec3, & Vec4 types

class Vector3
{
	public:
		Vector3() { mX = 0; mY = 0; mZ = 0; };
		Vector3(float x, float y, float z) { mX = x; mY = y; mZ = z; };
		Vector3(int x, int y, int z) { mX = (float)x; mY = (float)y; mZ = (float)z; };
		~Vector3() {};

		float getMagnitude() { return sqrtf((mX*mX) + (mY*mY) + (mZ*mZ)); };
		float getSqrMagnitude() { return getMagnitude() * getMagnitude(); };
		Vector3 normalize() { return *this / getMagnitude(); };

		//Negation operators
		Vector3 operator!()
		{
			Vector3 newVec;
			newVec.mX = -mX;
			newVec.mY = -mY;
			newVec.mZ = -mZ;
			return newVec;
		};

		Vector3 operator-()
		{
			Vector3 newVec;
			newVec.mX = -mX;
			newVec.mY = -mY;
			newVec.mZ = -mZ;
			return newVec;
		};

		static float dot(Vector3 lhs, Vector3 rhs)
		{
			float x = lhs.getX() * rhs.getX();
			float y = lhs.getY() * rhs.getY();
			float z = lhs.getZ() * rhs.getZ();
			return acos(x + y + z);
		};

		static Vector3 cross(Vector3 a, Vector3 b)
		{
			float x = (a.getY() * b.getZ()) - (a.getZ() * b.getY());
			float y = (a.getZ() * b.getX()) - (a.getX() * b.getZ());
			float z = (a.getX() * b.getY()) - (a.getY() * b.getX());
			return Vector3(x,y,z);
		}

		float* toArray()
		{
			float *arr = new float[3];

			arr[0] = mX;
			arr[1] = mY;
			arr[2] = mZ;

			return arr;
		}

		//comparison
		bool operator==(const Vector3& rhs) { return mX == rhs.mX && mY == rhs.mY && mZ == rhs.mZ; };
		bool operator!=(const Vector3& rhs) { return (mX != rhs.mX) || (mY == rhs.mY) || (mZ != rhs.mZ); };

		//Component-wise overloads
		Vector3 operator+(const Vector3& rhs)
		{
			Vector3 newVec;

			newVec.mX = mX + rhs.mX;
			newVec.mY = mY + rhs.mY;
			newVec.mZ = mZ + rhs.mZ;

			return newVec;
		};
		Vector3 operator+=(const Vector3& rhs)
		{
			mX = mX + rhs.mX;
			mY = mY + rhs.mY;
			mZ = mZ + rhs.mZ;

			return *this;
		};
		Vector3 operator-(const Vector3& rhs)
		{
			Vector3 newVec;

			newVec.mX = mX - rhs.mX;
			newVec.mY = mY - rhs.mY;
			newVec.mZ = mZ - rhs.mZ;

			return newVec;
		}; 
		Vector3 operator-=(const Vector3& rhs)
		{
			mX = mX - rhs.mX;
			mY = mY - rhs.mY;
			mZ = mZ - rhs.mZ;

			return *this;
		};
		Vector3 operator/(const Vector3& rhs)
		{
			Vector3 newVec;

			newVec.mX = mX / rhs.mX;
			newVec.mY = mY / rhs.mY;
			newVec.mZ = mZ / rhs.mZ;

			return newVec;
		};

		//Scalar overloads
		Vector3 operator+(const float& val)
		{
			Vector3 newVec;

			newVec.mX = mX + val;
			newVec.mY = mY + val;
			newVec.mZ = mZ + val;

			return newVec;
		};
		Vector3 operator-(const float& val)
		{
			Vector3 newVec;

			newVec.mX = mX - val;
			newVec.mY = mY - val;
			newVec.mZ = mZ - val;

			return newVec;
		};
		Vector3 operator*(const float& val)
		{
			Vector3 newVec;

			newVec.mX = mX * val;
			newVec.mY = mY * val;
			newVec.mZ = mZ * val;

			return newVec;
		};
		Vector3 operator/(const float& val)
		{
			Vector3 newVec;

			newVec.mX = mX / val;
			newVec.mY = mY / val;
			newVec.mZ = mZ / val;

			return newVec;
		};

		//Output overload
		friend std::ostream& operator<<(std::ostream& os, const Vector3& vec)
		{
			std::cout << "(" << vec.mX << ", " << vec.mY << ", " << vec.mZ << ")";
			return os;
		};

		float getX() const { return mX; };
		float getY() const { return mY; };
		float getZ() const { return mZ; };

		static Vector3 left, right, up, down;
		static Vector3 forward, back, one, zero;

	private:
		float mX = 0, mY = 0, mZ = 0;
};

//Vector value (0.0f, 0.0f, 0.0f)
Vector3 Vector3::zero(0.0f, 0.0f, 0.0f);
//Vector value (1.0f, 1.0f, 1.0f)
Vector3 Vector3::one(1.0f, 1.0f, 1.0f);
//Vector value (-1.0f, 0.0f, 0.0f)
Vector3 Vector3::left(-1.0f, 0.0f, 0.0f);
//Vector value (1.0f, 0.0f, 0.0f)
Vector3 Vector3::right(1.0f, 0.0f, 0.0f);
//Vector value (0.0f, 1.0f, 0.0f)
Vector3 Vector3::up(0.0f, 1.0f, 0.0f);
//Vector value (0.0f, -1.0f, 0.0f)
Vector3 Vector3::down(0.0f, -1.0f, 0.0f);
//Vector value (0.0f, 0.0f, 1.0f)
Vector3 Vector3::forward(0.0f, 0.0f, 1.0f);
//Vector value (0.0f, 0.0f, -1.0f)
Vector3 Vector3::back(0.0f, 0.0f, -1.0f);

#endif // !VEC3_H
