#ifndef VEC3_H
#define VEC3_H

#include <ostream>
#include <iostream>
#include "../../DeanLib/include/Trackable.h"

//TODO(low): worth moving code into cpp file?

// Contains code for Vec2, Vec3, & Vec4 types

namespace rkm {

	class Vector3 : public Trackable
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(int x, int y, int z);
		~Vector3();

		float getMagnitude();
		float getSqrMagnitude();
		Vector3 normalize();

		//Negation operators
		Vector3 operator!();
		Vector3 operator-();

		static float dot(Vector3 lhs, Vector3 rhs);
		static Vector3 cross(Vector3 a, Vector3 b);

		//Convert Vector object into float collection 
		//(NOTE): Good for referencing uniform values on shaders
		const float* toArray() const;

		//comparison
		bool operator==(const Vector3& rhs);
		bool operator!=(const Vector3& rhs);

		//Component-wise overloads
		Vector3 operator+(const Vector3& rhs);
		Vector3 operator+=(const Vector3& rhs);
		Vector3 operator-(const Vector3& rhs);
		Vector3 operator-=(const Vector3& rhs);
		Vector3 operator/(const Vector3& rhs);
		Vector3 operator*(const Vector3& rhs);

		//Scalar overloads
		Vector3 operator+(const float& val);
		Vector3 operator-(const float& val);
		Vector3 operator*(const float& val);
		Vector3 operator/(const float& val);

		//Output overload
		friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);

		inline float getX() const { return mX; };
		inline float getY() const { return mY; };
		inline float getZ() const { return mZ; };

		static Vector3 left, right, up, down;
		static Vector3 forward, back, one, zero;

	private:
		float mX = 0, mY = 0, mZ = 0;
	};
}
#endif // !VEC3_H
