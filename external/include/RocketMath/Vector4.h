#ifndef VEC4_H
#define VEC4_H

#include <ostream>
#include <iostream>

//TODO(low): worth moving code into cpp file?

// Contains code for Vec2, Vec3, & Vec4 types

class Vector4
{

	public:
		Vector4() { mX = 0; mY = 0; mZ = 0; };
		Vector4(Vector3 vec, float w = 1.0f) { mX = vec.getX(); mX = vec.getX(); mY = vec.getY(); mZ = vec.getZ(); mW = w; };
		Vector4(float x, float y, float z, float w = 1.0f) { mX = x; mY = y; mZ = z; mW = w; };
		Vector4(int x, int y, int z, int w = 1) { mX = (float)x; mY = (float)y; mZ = (float)z; mW = (float)w; };
		~Vector4() {};

		float getMagnitude() { return sqrtf((mX*mX) + (mY*mY) + (mZ*mZ) + (mW*mW)); };
		float getSqrMagnitude() { return getMagnitude() * getMagnitude(); };
		Vector4 normalize() { return *this / getMagnitude(); };

		//Negation operators
		Vector4 operator!()
		{
			Vector4 newVec;
			newVec.mX = -mX;
			newVec.mY = -mY;
			newVec.mZ = -mZ;
			newVec.mW = -mW;

			return newVec;
		};

		Vector4 operator-()
		{
			Vector4 newVec;
			newVec.mX = -mX;
			newVec.mY = -mY;
			newVec.mZ = -mZ;
			newVec.mW = -mW;

			return newVec;
		};

		static float dot(Vector4 lhs, Vector4 rhs)
		{
			float x = lhs.getX() * rhs.getX();
			float y = lhs.getY() * rhs.getY();
			float z = lhs.getZ() * rhs.getZ();
			float w = lhs.getW() * rhs.getW();
			return acos(x + y + z + w);
		};

		//comparison
		bool operator==(const Vector4& rhs) { return mX == rhs.mX && mY == rhs.mY && mZ == rhs.mZ; };
		bool operator!=(const Vector4& rhs) { return (mX != rhs.mX) || (mY == rhs.mY) || (mZ != rhs.mZ); };

		//Component-wise overloads
		Vector4 operator+(const Vector4& rhs)
		{
			Vector4 newVec;

			newVec.mX = mX + rhs.mX;
			newVec.mY = mY + rhs.mY;
			newVec.mZ = mZ + rhs.mZ;
			newVec.mW = mW + rhs.mW;

			return newVec;
		};
		Vector4 operator-(const Vector4& rhs)
		{
			Vector4 newVec;

			newVec.mX = mX - rhs.mX;
			newVec.mY = mY - rhs.mY;
			newVec.mZ = mZ - rhs.mZ;
			newVec.mW = mW - rhs.mW;


			return newVec;
		};

		Vector4 operator/(const Vector4& rhs)
		{
			Vector4 newVec;

			newVec.mX = mX / rhs.mX;
			newVec.mY = mY / rhs.mY;
			newVec.mZ = mZ / rhs.mZ;
			newVec.mW = mW / rhs.mW;

			return newVec;
		};

		//Scalar overloads
		Vector4 operator+(const float& val)
		{
			Vector4 newVec;

			newVec.mX = mX + val;
			newVec.mY = mY + val;
			newVec.mZ = mZ + val;
			newVec.mW = mW + val;

			return newVec;
		};
		Vector4 operator-(const float& val)
		{
			Vector4 newVec;

			newVec.mX = mX - val;
			newVec.mY = mY - val;
			newVec.mZ = mZ - val;
			newVec.mW = mW - val;

			return newVec;
		};
		Vector4 operator*(const float& val)
		{
			Vector4 newVec;

			newVec.mX = mX * val;
			newVec.mY = mY * val;
			newVec.mZ = mZ * val;
			newVec.mW = mW * val;

			return newVec;
		};
		Vector4 operator/(const float& val)
		{
			Vector4 newVec;

			newVec.mX = mX / val;
			newVec.mY = mY / val;
			newVec.mZ = mZ / val;
			newVec.mW = mW / val;

			return newVec;
		};

		//Output overload
		friend std::ostream& operator<<(std::ostream& os, const Vector4& vec)
		{
			std::cout << "(" << vec.mX << ", " << vec.mY << ", " << vec.mZ << ", " << vec.mW << ")";
			return os;
		};



		float getX() const { return mX; };
		float getY() const { return mY; };
		float getZ() const { return mZ; };
		float getW() const { return mW; };
	private:
		float mX = 0, mY = 0, mZ = 0, mW = 0;
};

#endif // !VEC4_H
