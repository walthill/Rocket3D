#include "include/Mat3.h"

namespace rkm {
	
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

	Mat3::~Mat3()
	{

	}

}

