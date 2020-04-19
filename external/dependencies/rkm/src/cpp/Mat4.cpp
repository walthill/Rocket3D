#include "include/Mat4.h"
#include <vector>

namespace rkm {

	Mat4 Mat4::identity(1);

	Mat4::Mat4() 
	{

	}
	Mat4::Mat4(float arr[16])
	{
		for (size_t i = 0; i < 16; i++)
		{
			mMatrixValues[i] = arr[i];
		}
	}

	// initializes values on the matrix's diagonal
	Mat4::Mat4(float val)
	{
		mMatrixValues[0] = val;
		mMatrixValues[5] = val;
		mMatrixValues[10] = val;
		mMatrixValues[15] = val;
	};

	Mat4::~Mat4() 
	{

	}

	//Matrix transform order of operations
	// 1. Scaling
	// 2. Rotation
	// 3. Translation

	Mat4 Mat4::scale(Mat4 matrix, Vector3 scaleVec)
	{
		Mat4 newMatrix = Mat4::identity;

		newMatrix.mMatrixValues[0] = scaleVec.getX();
		newMatrix.mMatrixValues[5] = scaleVec.getY();
		newMatrix.mMatrixValues[10] = scaleVec.getZ();

		newMatrix = matrix * newMatrix;

		return newMatrix;
	};

	Mat4 Mat4::rotate(Mat4 matrix, float angle, Vector3 rotationAxis)
	{
		Mat4 newMatrix = Mat4::identity;

		Vector3 normalizedAxis = rotationAxis.normalize();
		float x = normalizedAxis.getX();
		float y = normalizedAxis.getY();
		float z = normalizedAxis.getZ();

		float cosine = cos(angle);
		float sine = sin(angle);
		float cosDiff = 1 - cosine;

		//Calculations to allow for non-uniform scaling
		float scaleValue0 = (x * x) * cosDiff + cosine;
		float scaleValue1 = (x * y) * cosDiff - z * sine;
		float scaleValue2 = (x * z) * cosDiff + y * sine;

		float scaleValue4 = (x * y) * cosDiff + z * sine;
		float scaleValue5 = (y * y) * cosDiff + cosine;
		float scaleValue6 = (y * z) * cosDiff - x * sine;

		float scaleValue8 = (x * z) * cosDiff - y * sine;
		float scaleValue9 = (y * z) * cosDiff + x * sine;
		float scaleValue10 = (z * z)  * cosDiff + cosine;

		newMatrix.mMatrixValues[0] = scaleValue0;
		newMatrix.mMatrixValues[1] = scaleValue1;
		newMatrix.mMatrixValues[2] = scaleValue2;
		newMatrix.mMatrixValues[4] = scaleValue4;
		newMatrix.mMatrixValues[5] = scaleValue5;
		newMatrix.mMatrixValues[6] = scaleValue6;
		newMatrix.mMatrixValues[8] = scaleValue8;
		newMatrix.mMatrixValues[9] = scaleValue9;
		newMatrix.mMatrixValues[10] = scaleValue10;

		return matrix * newMatrix;
	};

	Mat4 Mat4::translate(Mat4 matrix, Vector3 translationVec)
	{
		//Mat4 newMatrix = Mat4::identity;

		matrix.mMatrixValues[3] = translationVec.getX();
		matrix.mMatrixValues[7] = translationVec.getY();
		matrix.mMatrixValues[11] = translationVec.getZ();

		return matrix;
	}
	
	Mat4 Mat4::inverse(Mat4 mat)
	{
		//Inverse of Matrix A is A^-1
//			Mat4 inverseMatrix(matrixToInvert.unwrapMatrix());

		std::vector<Mat3> mat3List;
		float* mat3Arr = new float[9];
		float determinant = 0;
		int sign = 1;

		for (size_t i = 0; i < 4; i++)
		{
			//Set Mat3 cofactors 
			if (i == 0)
			{
				mat3Arr[0] = mat(1, 1);
				mat3Arr[1] = mat(1, 2);
				mat3Arr[2] = mat(1, 3);
				mat3Arr[3] = mat(2, 1);
				mat3Arr[4] = mat(2, 2);
				mat3Arr[5] = mat(2, 3);
				mat3Arr[6] = mat(3, 1);
				mat3Arr[7] = mat(3, 2);
				mat3Arr[8] = mat(3, 3);
				sign = 1;
			}
			else if(i == 1)
			{
				mat3Arr[0] = mat(1, 0);
				mat3Arr[1] = mat(1, 2);
				mat3Arr[2] = mat(1, 3);
				mat3Arr[3] = mat(2, 0);
				mat3Arr[4] = mat(2, 2);
				mat3Arr[5] = mat(2, 3);
				mat3Arr[6] = mat(3, 0);
				mat3Arr[7] = mat(3, 2);
				mat3Arr[8] = mat(3, 3);
				sign = -1;
			}
			else if (i == 2)
			{
				mat3Arr[0] = mat(1, 0);
				mat3Arr[1] = mat(1, 1);
				mat3Arr[2] = mat(1, 3);
				mat3Arr[3] = mat(2, 0);
				mat3Arr[4] = mat(2, 1);
				mat3Arr[5] = mat(2, 3);
				mat3Arr[6] = mat(3, 0);
				mat3Arr[7] = mat(3, 1);
				mat3Arr[8] = mat(3, 3);
				sign = 1;
			}
			else if (i == 3)
			{
				mat3Arr[0] = mat(1, 0);
				mat3Arr[1] = mat(1, 1);
				mat3Arr[2] = mat(1, 2);
				mat3Arr[3] = mat(2, 0);
				mat3Arr[4] = mat(2, 1);
				mat3Arr[5] = mat(2, 2);
				mat3Arr[6] = mat(3, 0);
				mat3Arr[7] = mat(3, 1);
				mat3Arr[8] = mat(3, 2);

				sign = -1;
			}

			Mat3 mat3 = Mat3(mat3Arr);
			mat3List.push_back(mat3);
			determinant +=  ( sign * mat(0, i) * calculateDeterminate(mat3));
		}



		//Calculate cofactor of all 3x3 matrices
/*		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
				((mat[(j + 1) % 3][(i + 1) % 3] * mat[(j + 2) % 3][(i + 2) % 3]) - (mat[(j + 1) % 3][(i + 2) % 3] * mat[(j + 2) % 3][(i + 1) % 3])) / determinant << "\t";

		}*/



		return mat;
	}


	//Calculation help from https://www.thecrazyprogrammer.com/2017/02/c-c-program-find-inverse-matrix.html
	float Mat4::calculateDeterminate(Mat3 mat)
	{
		float det = 0;

		//finding determinant
		for (int i = 0; i < 3; i++)
			det += (mat(0, i)) * (mat(1, (i + 1) % 3) * mat(2, (i + 2) % 3) - mat(1, (i + 2) % 3) * mat(2, (i + 1) % 3));
		
		return det;
	}



	//Written with help from https://learnopengl.com/code_viewer.php?code=getting-started/camera-exercise2
	Mat4 Mat4::lookAt(Vector3 pos, Vector3 target, Vector3 worldUp)
	{
		//Calculate camera direction
		Vector3 dir = pos - target;
		Vector3 zAxis = dir.normalize();

		//Positive right axis
		Vector3 up = worldUp.normalize();
		Vector3 xAxis = Vector3::cross(up, zAxis);
		xAxis = xAxis.normalize();

		//Camera up
		Vector3 yAxis = Vector3::cross(zAxis, xAxis);

		Mat4 translation = Mat4::identity, rotation = Mat4::identity;

		translation.mMatrixValues[3] = -pos.getX();
		translation.mMatrixValues[7] = -pos.getY();
		translation.mMatrixValues[11] = -pos.getZ();

		rotation.mMatrixValues[0] = xAxis.getX();
		rotation.mMatrixValues[1] = xAxis.getY();
		rotation.mMatrixValues[2] = xAxis.getZ();

		rotation.mMatrixValues[4] = yAxis.getX();
		rotation.mMatrixValues[5] = yAxis.getY();
		rotation.mMatrixValues[6] = yAxis.getZ();

		rotation.mMatrixValues[8] = zAxis.getX();
		rotation.mMatrixValues[9] = zAxis.getY();
		rotation.mMatrixValues[10] = zAxis.getZ();

		return rotation * translation;
	};

	//Matrix scalar operations
	Mat4 Mat4::operator+(float val)
	{
		Mat4 newMat = *this;

		for (int i = 0; i < mMAT4_SIZE; i++)
			newMat.mMatrixValues[i] += val;

		return newMat;
	};
	Mat4 Mat4::operator-(float val)
	{
		Mat4 newMat = *this;

		for (int i = 0; i < mMAT4_SIZE; i++)
			newMat.mMatrixValues[i] -= val;

		return newMat;
	};
	Mat4 Mat4::operator*(float val)
	{
		Mat4 newMat = *this;

		for (int i = 0; i < mMAT4_SIZE; i++)
			newMat.mMatrixValues[i] *= val;

		return newMat;
	};

	//Matrix-matrix operations
	Mat4 Mat4::operator*(Mat4 rhs)
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
	};



	//Matrix-Vector operations
	Vector3 Mat4::operator*(Vector3 rhs)
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
	};

	//Matrix-Vector operations
	Vector4 Mat4::operator*(Vector4 rhs)
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
	};

	//Output overload
	std::ostream& operator<<(std::ostream& os, const Mat4& mat)
	{
		std::cout << " | " << mat.mMatrixValues[0] << "\t " << mat.mMatrixValues[1] << "\t " << mat.mMatrixValues[2] << "\t " << mat.mMatrixValues[3] << " |" << std::endl
			<< " | " << mat.mMatrixValues[4] << "\t " << mat.mMatrixValues[5] << "\t " << mat.mMatrixValues[6] << "\t " << mat.mMatrixValues[7] << " |" << std::endl
			<< " | " << mat.mMatrixValues[8] << "\t " << mat.mMatrixValues[9] << "\t " << mat.mMatrixValues[10] << "\t " << mat.mMatrixValues[11] << " |" << std::endl
			<< " | " << mat.mMatrixValues[12] << "\t " << mat.mMatrixValues[13] << "\t " << mat.mMatrixValues[14] << "\t " << mat.mMatrixValues[15] << " |" << std::endl << std::endl;

		return os;
	};
}