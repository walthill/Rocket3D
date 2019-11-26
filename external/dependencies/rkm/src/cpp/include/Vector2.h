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

			inline float getX() const { return mX; };
			inline float getY() const { return mY; };

			static Vector2 left, right, up, down, one, zero;

		private:
			float mX, mY;
	};
}
#endif // !VEC2_H
