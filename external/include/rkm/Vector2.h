#ifndef VEC2_H
#define VEC2_H

#include <ostream>
#include <iostream>

namespace rkm {

	class Vector2
	{
		public:
			Vector2();
			Vector2(float x, float y);
			Vector2(int x, int y);
			Vector2(unsigned int x, unsigned int y);

			float getMagnitude();
			float getSqrMagnitude();
			Vector2 normalize();

			//Negation operators
			Vector2 operator!();
			Vector2 operator-();

			inline const float* toArray() const { return mVecArr; };

			static float dot(Vector2 lhs, Vector2 rhs);

			//comparison
			bool operator==(const Vector2& rhs);
			bool operator!=(const Vector2& rhs);

			//Component-wise overloads
			Vector2 operator+(const Vector2& rhs);
			Vector2 operator-(const Vector2& rhs);
			Vector2 operator/(const Vector2& rhs);

			//Scalar overloads
			Vector2 operator+(const float& val);
			Vector2 operator-(const float& val);
			Vector2 operator*(const float& val);
			Vector2 operator/(const float& val);

			//Output overload
			friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);

			inline float getX() const { return mVecArr[X]; };
			inline float getY() const { return mVecArr[Y]; };

			static Vector2 left, right, up, down, one, zero;

		private:
			float mVecArr[2];
			static const char X = 0, Y = 1;
	};
}
#endif // !VEC2_H
