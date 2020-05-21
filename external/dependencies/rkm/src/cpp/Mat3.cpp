#include "include/Mat3.h"
#include "include/MathUtils.h"

namespace rkm {

    Mat3 Mat3::identity(1);

	Mat3::Mat3()
	{

	}

	Mat3::Mat3(float matrixArray[9])
	{
		for (size_t i = 0; i < 9; i++)
		{
			mMatrixValues[i] = matrixArray[i];
		}
	}

    Mat3::Mat3(float val)
    {
        mMatrixValues[0] = val;
        mMatrixValues[4] = val;
        mMatrixValues[8] = val;
    }

	Mat3::~Mat3()
	{

	}

    ///////////////////////////////////////////////////////////////////////////////
    // return determinant of 3x3 matrix
    ///////////////////////////////////////////////////////////////////////////////
    float Mat3::getDeterminant(const Mat3& mat)
    {
        return  mat(0, 0) * (mat(1, 1) * mat(2, 2) - mat(1, 2) * mat(2, 1)) -
                mat(0, 1) * (mat(1, 0) * mat(2, 2) - mat(1, 2) * mat(2, 0)) +
                mat(0, 2) * (mat(1, 0) * mat(2, 1) - mat(1, 1) * mat(2, 0));
    }



    ///////////////////////////////////////////////////////////////////////////////
    // inverse 3x3 matrix
    // If cannot find inverse (det=0), set identity matrix
    // M^-1 = adj(M) / det(M)
    //        | m4m8-m5m7  m5m6-m3m8  m3m7-m4m6 |
    //      = | m7m2-m8m1  m0m8-m2m6  m6m1-m7m0 | / det(M)
    //        | m1m5-m2m4  m2m3-m0m5  m0m4-m1m3 |
    ///////////////////////////////////////////////////////////////////////////////
    Mat3 Mat3::invert(const Mat3& mat)
    {
        float invertMat[mMAT3_SIZE];                        
        float determinant, invDeterminant;
        float tmp[9];

        tmp[0] = mat(1, 1) * mat(2, 2) - mat(1, 2) * mat(2, 1);
        tmp[1] = mat(2, 1) * mat(0, 2) - mat(2, 2) * mat(0, 1);
        tmp[2] = mat(0, 1) * mat(1, 2) - mat(0, 2) * mat(1, 1);
        tmp[3] = mat(1, 2) * mat(2, 0) - mat(1,0) *  mat(2, 2);
        tmp[4] = mat(0, 0) * mat(2, 2) - mat(0, 2) * mat(2, 0);
        tmp[5] = mat(0, 2) * mat(1, 0) - mat(0, 0) * mat(1, 2);
        tmp[6] = mat(1, 0) * mat(2, 1) - mat(1, 1) * mat(2, 0);
        tmp[7] = mat(2, 0) * mat(0, 1) - mat(2, 1) * mat(0, 0);
        tmp[8] = mat(0, 0) * mat(1, 1) - mat(0, 1) * mat(1, 0);

        // check determinant if it is 0
        determinant = mat(0,0) * tmp[0] + mat(0, 1) * tmp[3] + mat(0, 2) * tmp[6];
        if (std::fabs(determinant) <= epsilon)
        {
            return Mat3::identity; // cannot inverse, make it idenety matrix
        }

        // divide by the determinant
        invDeterminant = 1.0f / determinant;
        invertMat[0] = invDeterminant * tmp[0];
        invertMat[1] = invDeterminant * tmp[1];
        invertMat[2] = invDeterminant * tmp[2];
        invertMat[3] = invDeterminant * tmp[3];
        invertMat[4] = invDeterminant * tmp[4];
        invertMat[5] = invDeterminant * tmp[5];
        invertMat[6] = invDeterminant * tmp[6];
        invertMat[7] = invDeterminant * tmp[7];
        invertMat[8] = invDeterminant * tmp[8];

        return Mat3(invertMat);
    }


}

