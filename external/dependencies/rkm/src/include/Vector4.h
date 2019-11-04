#ifndef VEC4_H
#define VEC4_H

#include <ostream>
#include <iostream>
#include "Vector3.h"
//TODO(low): worth moving code into cpp file?

// Contains code for Vec2, Vec3, & Vec4 types

namespace rkm {

	class Vector4
	{

		public:
			Vector4();
			Vector4(Vector3 vec, float w = 1.0f);
			Vector4(float x, float y, float z, float w = 1.0f);
			Vector4(int x, int y, int z, int w = 1);
			~Vector4();

			float getMagnitude();
			float getSqrMagnitude();
			Vector4 normalize();

			//Negation operators
			Vector4 operator!();
			Vector4 operator-();

			static float dot(Vector4 lhs, Vector4 rhs);

			//comparison
			bool operator==(const Vector4& rhs);
			bool operator!=(const Vector4& rhs);

			//Component-wise overloads
			Vector4 operator+(const Vector4& rhs);
			Vector4 operator-(const Vector4& rhs);
			Vector4 operator/(const Vector4& rhs);

			//Scalar overloads
			Vector4 operator+(const float& val);
			Vector4 operator-(const float& val);
			Vector4 operator*(const float& val);
			Vector4 operator/(const float& val);

			//Output overload
			friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);

			inline float getX() const { return mX; };
			inline float getY() const { return mY; };
			inline float getZ() const { return mZ; };
			inline float getW() const { return mW; };
		private:
			float mX = 0, mY = 0, mZ = 0, mW = 0;
	};
}
#endif // !VEC4_H
