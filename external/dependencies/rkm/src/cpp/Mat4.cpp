#include "include/Mat4.h"
#include "include/Mat3.h"
#include "include/MathUtils.h"
#include <vector>

namespace rkm {

	Mat4 Mat4::zero(0.0f);
	Mat4 Mat4::identity(1);

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
	}

	Mat4::Mat4(Mat3 mat)
	{

		auto values = mat.getMatrixValues();
		mMatrixValues[0] = values[0];
		mMatrixValues[1] = values[1];
		mMatrixValues[2] = values[2];
		mMatrixValues[4] = values[3];
		mMatrixValues[5] = values[4];
		mMatrixValues[6] = values[5];
		mMatrixValues[8] = values[6];
		mMatrixValues[9] = values[7];
		mMatrixValues[10] = values[8];
		mMatrixValues[15] = 1;
	}

	Mat4::~Mat4() 
	{

	}

	//Matrix transform order of operations
	// 1. Scaling
	// 2. Rotation
	// 3. Translation

	Mat4 Mat4::scale(Mat4 matrix, const Vector3& scaleVec)
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

	Mat4 Mat4::translate(Mat4 matrix, const Vector3& translationVec)
	{
		//Mat4 newMatrix = Mat4::identity;

		matrix.mMatrixValues[3] = translationVec.getX();
		matrix.mMatrixValues[7] = translationVec.getY();
		matrix.mMatrixValues[11] = translationVec.getZ();

		return matrix;
	}
	
	// Calculation & code help from the ever-helpful SongHo - https://www.songho.ca/opengl/gl_matrix.html
	// Did my own research here: https://www.thecrazyprogrammer.com/2017/02/c-c-program-find-inverse-matrix.html
	// and here: https://www.geeksforgeeks.org/adjoint-inverse-matrix/
	// SongHo "license" as of 2017 http://disq.us/p/1l6onix
	Mat4 Mat4::invert(const Mat4& mat)
	{
		if (mat(3,0) == 0 && mat(3, 1) == 0 && mat(3, 2) == 0 && mat(3, 3) == 1)
		{
			return invertAffine(mat);
		}
		else
		{
			return invertGeneral(mat);
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	// HELP FROM SONGHO
	// compute the inverse of a 4x4 affine transformation matrix
	//
	// Affine transformations are generalizations of Euclidean transformations.
	// Affine transformation includes translation, rotation, reflection, scaling,
	// and shearing. Length and angle are NOT preserved.
	// M = [ R | T ]
	//     [ --+-- ]    (R denotes 3x3 rotation/scale/shear matrix)
	//     [ 0 | 1 ]    (T denotes 1x3 translation matrix)
	//
	// y = M*x  ->  y = R*x + T  ->  x = R^-1*(y - T)  ->  x = R^-1*y - R^-1*T
	//
	//  [ R | T ]-1   [ R^-1 | -R^-1 * T ]
	//  [ --+-- ]   = [ -----+---------- ]
	//  [ 0 | 1 ]     [  0   +     1     ]
	///////////////////////////////////////////////////////////////////////////////
	Mat4 Mat4::invertAffine(const Mat4& m)
	{
		// R^-1
		float invertedMat[mMAT4_SIZE];
		float mat3Arr[9];

		//Create 3x3 mat
		mat3Arr[0] = m(0, 0);
		mat3Arr[1] = m(0, 1);
		mat3Arr[2] = m(0, 2);

		mat3Arr[3] = m(1, 0);
		mat3Arr[4] = m(1, 1);
		mat3Arr[5] = m(1, 2);

		mat3Arr[6] = m(2, 0);
		mat3Arr[7] = m(2, 1);
		mat3Arr[8] = m(2, 2);

		Mat3 newMat3(mat3Arr);
		newMat3 = Mat3::invert(newMat3);

		invertedMat[0]  = newMat3(0, 0);	
		invertedMat[1]  = newMat3(0, 1);	
		invertedMat[2]  = newMat3(0, 2);	
		invertedMat[4]  = newMat3(1, 0);	
		invertedMat[5]  = newMat3(1, 1);	
		invertedMat[6]  = newMat3(1, 2);	
		invertedMat[8]  = newMat3(2, 0);	
		invertedMat[9]  = newMat3(2, 1);	
		invertedMat[10] = newMat3(2, 2);	

		// -R^-1 * T
		float x = m(3, 0);
		float y = m(3, 1);
		float z = m(3, 2);
		invertedMat[12] = -(newMat3(0, 0) * x + newMat3(1, 0) * y + newMat3(2, 0) * z);
		invertedMat[13] = -(newMat3(0, 1) * x + newMat3(1, 1) * y + newMat3(2, 1) * z);
		invertedMat[14] = -(newMat3(0, 2) * x + newMat3(1, 2) * y + newMat3(2, 2) * z);

		// last row should be unchanged (0,0,0,1)
		invertedMat[3] = 0.0f;
		invertedMat[7] = 0.0f;
		invertedMat[11] = 0.0f;
		invertedMat[15] = 1.0f;

		return Mat4(invertedMat);
	}

	///////////////////////////////////////////////////////////////////////////////
	// HELP FROM SONGHO
	// compute the inverse of a general 4x4 matrix using Cramer's Rule
	// If cannot find inverse, return indentity matrix
	// M^-1 = adj(M) / det(M)
	///////////////////////////////////////////////////////////////////////////////
	Mat4 Mat4::invertGeneral(const Mat4& m)
	{
		// get cofactors of minor matrices
		float cofactor0 = calculateCofactor(m(1, 1), m(1, 2), m(1, 3), m(2, 1), m(2, 2), m(2, 3), m(3, 1), m(3, 2), m(3, 3));
		float cofactor1 = calculateCofactor(m(1, 0), m(1, 2), m(1, 3), m(2, 0), m(2, 2), m(2, 3), m(3, 0), m(3, 2), m(3, 3));
		float cofactor3 = calculateCofactor(m(1, 0), m(1, 1), m(1, 2), m(2, 0), m(2, 1), m(2, 2), m(3, 0), m(3, 1), m(3, 2));
		float cofactor2 = calculateCofactor(m(1, 0), m(1, 1), m(1, 3), m(2, 0), m(2, 1), m(2, 3), m(3, 0), m(3, 1), m(3, 3));

		// get determinant
		float determinant = m(0, 0) * cofactor0 - m(0, 1) * cofactor1 + m(0, 2) * cofactor2 - m(0, 3) * cofactor3;
		if (std::fabs(determinant) <= epsilon)
		{
			return Mat4::identity;
		}

		// get rest of cofactors for adj(M)
		float cofactor4 = calculateCofactor(m(0, 1), m(0, 2), m(0, 3), m(2, 1), m(2, 2), m(2, 3), m(3, 1), m(3, 2), m(3, 3));
		float cofactor5 = calculateCofactor(m(0, 0), m(0, 2), m(0, 3), m(2, 0), m(2, 2), m(2, 3), m(3, 0), m(3, 2), m(3, 3));
		float cofactor6 = calculateCofactor(m(0, 0), m(0, 1), m(0, 3), m(2, 0), m(2, 1), m(2, 3), m(3, 0), m(3, 1), m(3, 3));
		float cofactor7 = calculateCofactor(m(0, 0), m(0, 1), m(0, 2), m(2, 0), m(2, 1), m(2, 2), m(3, 0), m(3, 1), m(3, 2));

		float cofactor8 = calculateCofactor(m(0, 1), m(0, 2),  m(0, 3), m(1, 1), m(1, 2), m(1,3), m(3, 1), m(3, 2), m(3, 3));
		float cofactor9 = calculateCofactor(m(0, 0), m(0, 2),  m(0, 3), m(1, 0), m(1, 2), m(1,3), m(3, 0), m(3, 2), m(3, 3));
		float cofactor10 = calculateCofactor(m(0, 0), m(0, 1), m(0, 3), m(1, 0), m(1, 1), m(1,3), m(3, 0), m(3, 1), m(3, 3));
		float cofactor11 = calculateCofactor(m(0, 0), m(0, 1), m(0, 2), m(1, 0), m(1, 1), m(1, 2), m(3, 0), m(3, 1), m(3, 2));

		float cofactor12 = calculateCofactor(m(0, 1), m(0, 2), m(0, 3), m(1, 1), m(1, 2), m(1, 3), m(2, 1), m(2, 2), m(2, 3));
		float cofactor13 = calculateCofactor(m(0, 0), m(0, 2), m(0, 3), m(1, 0), m(1, 2), m(1, 3), m(2, 0), m(2, 2), m(2, 3));
		float cofactor14 = calculateCofactor(m(0, 0), m(0, 1), m(0, 3), m(1, 0), m(1, 1), m(1, 3), m(2, 0), m(2, 1), m(2, 3));
		float cofactor15 = calculateCofactor(m(0, 0), m(0, 1), m(0, 2), m(1, 0), m(1, 1), m(1, 2), m(2,0), m(2, 1), m(2, 2));

		// build inverse matrix = adj(M) / det(M)
		// adjugate of M is the transpose of the cofactor matrix of M
		float invDeterminant = 1.0f / determinant;

		float invertMat[mMAT4_SIZE];

		invertMat[0] = invDeterminant * cofactor0;
		invertMat[1] = -invDeterminant * cofactor4;
		invertMat[2] = invDeterminant * cofactor8;
		invertMat[3] = -invDeterminant * cofactor12;

		invertMat[4] = -invDeterminant * cofactor1;
		invertMat[5] = invDeterminant * cofactor5;
		invertMat[6] = -invDeterminant * cofactor9;
		invertMat[7] = invDeterminant * cofactor13;

		invertMat[8] = invDeterminant * cofactor2;
		invertMat[9] = -invDeterminant * cofactor6;
		invertMat[10] = invDeterminant * cofactor10;
		invertMat[11] = -invDeterminant * cofactor14;

		invertMat[12] = -invDeterminant * cofactor3;
		invertMat[13] = invDeterminant * cofactor7;
		invertMat[14] = -invDeterminant * cofactor11;
		invertMat[15] = invDeterminant * cofactor15;

		return Mat4(invertMat);
	}
	
	float Mat4::calculateDeterminate(const Mat4& mat)
	{												
		return  mat(0, 0) * calculateCofactor(mat(1, 1), mat(1,2), mat(1,3), mat(2,1), mat(2,2), mat(2,3), mat(3, 1), mat(3,2), mat(3,3)) -
				mat(0, 1) * calculateCofactor(mat(1, 0), mat(1, 2), mat(1, 3), mat(2,0), mat(2, 2), mat(2, 3), mat(3, 0), mat(3,2), mat(3, 3)) +
				mat(0, 2) * calculateCofactor(mat(1, 0), mat(1, 1), mat(1, 3), mat(2, 0), mat(2, 1), mat(2, 3), mat(3, 0), mat(3, 1), mat(3, 3)) -
				mat(0, 3) * calculateCofactor(mat(1, 0), mat(1, 1), mat(1, 2), mat(2, 0), mat(2, 1), mat(2, 2), mat(3, 0), mat(3, 1), mat(3, 2));
	}

	float Mat4::calculateCofactor(float m0, float m1, float m2,
								  float m3, float m4, float m5,
								  float m6, float m7, float m8)
	{
		return  m0 * (m4 * m8 - m5 * m7) -
				m1 * (m3 * m8 - m5 * m6) +
				m2 * (m3 * m7 - m4 * m6);
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
	Mat4 Mat4::operator*(const Mat4& rhs)
	{
		Mat4 newMat = Mat4::zero;

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
	Vector3 Mat4::operator*(const Vector3& rhs)
	{
		Mat4 newMat = Mat4::zero;
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
	Vector4 Mat4::operator*(const Vector4& rhs)
	{
		Mat4 newMat = Mat4::zero;
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