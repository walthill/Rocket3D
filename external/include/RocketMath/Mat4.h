#ifndef MAT4_H
#define MAT4_H

#include <ostream>
#include <iostream>

/*
		Matrix

		| 1 0 0 0 |
		| 0 1 0 0 |
		| 0 0 1 0 |
		| 0 0 0 1 |

*/

class Mat4
{
	public:
		Mat4() {};
		Mat4(float arr[16]) 
		{
			for (size_t i = 0; i < 16; i++)
			{
				mMatrixValues[i] = arr[i];
			}
		};
		// initializes values on the matrix's diagonal
		Mat4(float val) 		
		{
			mMatrixValues[0] = val;
			mMatrixValues[5] = val;
			mMatrixValues[10] = val;
			mMatrixValues[15] = val;
		};	

		~Mat4() {};
		

		//Matrix transform order of operations
		// 1. Scaling
		// 2. Rotation
		// 3. Translation

		static Mat4 scale(Mat4 matrix, Vector3 scaleVec)
		{
			Mat4 newMatrix = Mat4::identity;

			newMatrix.mMatrixValues[0] = scaleVec.getX();
 			newMatrix.mMatrixValues[5] = scaleVec.getY();
			newMatrix.mMatrixValues[10] = scaleVec.getZ();

			newMatrix = newMatrix * matrix;

			return newMatrix;
		}

		static Mat4 rotate(Mat4 matrix, float angle, Vector3 rotationAxis)
		{
			//Mat4 newMatrix = Mat4::identity;

			Vector3 normalizedAxis = rotationAxis.normalize();
			float xAxisRotate = normalizedAxis.getX();
			float yAxisRotate = normalizedAxis.getY();
			float zAxisRotate = normalizedAxis.getZ();

			if (xAxisRotate != 0)
			{
			}
			else if (yAxisRotate != 0)
			{
			}
			else if (zAxisRotate != 0)
			{
				matrix.mMatrixValues[0] = cos(angle);
				matrix.mMatrixValues[1] = -sin(angle);
				matrix.mMatrixValues[4] = sin(angle);
				matrix.mMatrixValues[5] = cos(angle);
			}


			return matrix;
		}

		static Mat4 translate(Mat4 matrix, Vector3 translationVec)
		{
			//Mat4 newMatrix = Mat4::identity;

			matrix.mMatrixValues[3] = translationVec.getX();
			matrix.mMatrixValues[7] = translationVec.getY();
			matrix.mMatrixValues[11] = translationVec.getZ();
			
			return matrix;
		}

		//Matrix scalar operations
		Mat4 operator+(float val)
		{
			Mat4 newMat = *this;

			for (int i = 0; i < mMAT4_SIZE; i++)
				newMat.mMatrixValues[i] += val;

			return newMat;
		}
		Mat4 operator-(float val)
		{
			Mat4 newMat = *this;

			for (int i = 0; i < mMAT4_SIZE; i++)
				newMat.mMatrixValues[i] -= val;

			return newMat;
		}
		Mat4 operator*(float val)
		{
			Mat4 newMat = *this;

			for (int i = 0; i < mMAT4_SIZE; i++)
				newMat.mMatrixValues[i] *= val;

			return newMat;
		}

		//Matrix-matrix operations
		Mat4 operator*(Mat4 rhs)
		{
			Mat4 newMat;
		
			//Calculate result for each matrix element
			int currentColumn = 0, currentRowStartIndex = 0;
			for (int i = 0; i < mMAT4_SIZE; i++)
			{
					
				//Perform operations to fill each matrix element
				for (int j = 0; j < mROW_SIZE; j++)
				{
					// Multiply row value from left-hand side by column value from right-hand side. 
					// Sum those products
					
					int rowValueIndex = j + currentRowStartIndex;
					int columnValueIndex = (j * mCOL_SIZE) + currentColumn;

					newMat.mMatrixValues[i] += this->mMatrixValues[rowValueIndex] * rhs.mMatrixValues[columnValueIndex];
				} 
					
				if (currentColumn == 3) //end of matrix rows
				{
					currentColumn = 0;
					currentRowStartIndex += mROW_SIZE;
				}
				else
					currentColumn++;
			}

			return newMat;
		}



		//Matrix-Vector operations
		Vector3 operator*(Vector3 rhs)
		{
			Mat4 newMat;
			Vector3 newVec;
			float vectorMatrix[16] = {}; //treat this as a single column (Nx1) matrix
			vectorMatrix[0] = rhs.getX();
			vectorMatrix[4] = rhs.getY();
			vectorMatrix[8] = rhs.getZ();
			vectorMatrix[12] = 1;

			matrixMultiplication(newMat, vectorMatrix);
			
			newVec = Vector3(newMat.mMatrixValues[0], newMat.mMatrixValues[1],
			  				 newMat.mMatrixValues[2]);

			return newVec;
		}

		//Matrix-Vector operations
		Vector4 operator*(Vector4 rhs)
		{
			Mat4 newMat;
			Vector4 newVec;
			float vectorMatrix[16] = {}; //treat this as a single column (Nx1) matrix
			vectorMatrix[0] = rhs.getX();
			vectorMatrix[4] = rhs.getY();
			vectorMatrix[8] = rhs.getZ();
			vectorMatrix[12] = 1;

			matrixMultiplication(newMat, vectorMatrix);

			newVec = Vector4(newMat.mMatrixValues[0], newMat.mMatrixValues[1], 
							 newMat.mMatrixValues[2], newMat.mMatrixValues[3]);

			return newVec;
		}
	
		//Output overload
		friend std::ostream& operator<<(std::ostream& os, const Mat4& mat)
		{
			std::cout << " | " << mat.mMatrixValues[0] << "\t " << mat.mMatrixValues[1] << "\t " << mat.mMatrixValues[2]  << "\t " << mat.mMatrixValues[3] << " |" << std::endl
			<< " | " << mat.mMatrixValues[4] << "\t " << mat.mMatrixValues[5] << "\t " << mat.mMatrixValues[6] << "\t " << mat.mMatrixValues[7] << " |" << std::endl
			<< " | " << mat.mMatrixValues[8] << "\t " << mat.mMatrixValues[9] << "\t " << mat.mMatrixValues[10] << "\t " << mat.mMatrixValues[11] << " |" << std::endl
			<< " | " << mat.mMatrixValues[12] << "\t " << mat.mMatrixValues[13] << "\t " << mat.mMatrixValues[14] << "\t " << mat.mMatrixValues[15] << " |" << std::endl << std::endl;

			return os;
		};

		float* toArray()
		{

		}

		const float* getMatrixValues() const { return mMatrixValues; };

		static Mat4 identity;

	private:
		static const int mMAT4_SIZE = 16, mROW_SIZE = 4, mCOL_SIZE = 4;

		float mMatrixValues[16] = {  
			0, 0, 0, 0, 
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		};

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


Mat4 Mat4::identity(1);

#endif // !MAT4_H
