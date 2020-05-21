#ifndef MAT4_H
#define MAT4_H

#include <ostream>
#include <iostream>
#include "Mat3.h"
#include "Vector3.h"
#include "Vector4.h"

/*
		Matrix - coded/calculated in row major order

		| 1 0 0 0 |
		| 0 1 0 0 |
		| 0 0 1 0 |
		| 0 0 0 1 |

		 Index breakdown
		|  0  1  2  3   |
		|  4  5  6  7   |
		|  8  9  10 11  |
		|  12 13 14 15  |
*/
namespace rkm {

	class Mat4
	{
		public:
			Mat4();
			Mat4(float arr[16]);
			// initializes values on the matrix's diagonal
			Mat4(float val);

			~Mat4();

			//Matrix transform order of operations
			// 1. Scaling
			// 2. Rotation
			// 3. Translation

			static Mat4 scale(Mat4 matrix, const Vector3& scaleVec);
			static Mat4 rotate(Mat4 matrix, float angle, Vector3 rotationAxis);
			static Mat4 translate(Mat4 matrix, const Vector3& translationVec);
			static Mat4 invert(const Mat4& matrixToInvert);

			//Written with help from https://learnopengl.com/code_viewer.php?code=getting-started/camera-exercise2
			static Mat4 lookAt(Vector3 pos, Vector3 target, Vector3 worldUp = Vector3::up);

			//Matrix scalar operations
			Mat4 operator+(float val);
			Mat4 operator-(float val);
			Mat4 operator*(float val);

			//Matrix-matrix operations
			Mat4 operator*(const Mat4& rhs);
			   
			//Matrix-Vector operations
			Vector3 operator*(const Vector3& rhs);

			//Matrix-Vector operations
			Vector4 operator*(const Vector4& rhs);

			//Output overload
			friend std::ostream& operator<<(std::ostream& os, const Mat4& mat);

			//Access array value w/ row col indeces
			const float& operator()(int row, int col) const { return mMatrixValues[row * mROW_SIZE + col]; };

			inline const float* getMatrixValues() const { return mMatrixValues; };
			inline float* unwrapMatrix() { return mMatrixValues; }
			static Mat4 identity;

		private:
			static const int mMAT4_SIZE = 16, mROW_SIZE = 4, mCOL_SIZE = 4;

			float mMatrixValues[16] = {
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0
			};

			static Mat4 invertAffine(const Mat4& mat);
			static Mat4 invertGeneral(const Mat4& mat);
			static float calculateDeterminate(const Mat4& mat);
			static float calculateCofactor(float m0, float m1, float m2,
											float m3, float m4, float m5,
											float m6, float m7, float m8);

			void matrixMultiplication(Mat4 &newMat, float* vec)
			{
				//Calculate result for each matrix element
				int currentRowStartIndex = 0;
				for (int i = 0; i < mCOL_SIZE; i++)
				{
					//Perform operations to fill each matrix element
					for (int j = 0; j < mROW_SIZE; j++)
					{
						// Multiply row value from left-hand side by column value from right-hand side. 
						// Sum those products

						int rowValueIndex = j + currentRowStartIndex;
						int columnValueIndex = (j * mCOL_SIZE);

						newMat.mMatrixValues[i] += this->mMatrixValues[rowValueIndex] * vec[columnValueIndex];
					}
					currentRowStartIndex += mROW_SIZE;
				}
			}
	};
}
#endif // !MAT4_H
