#ifndef MAT3_H
#define MAT3_H

namespace rkm {
	class Mat4; 
	class Mat3
	{
		public:
			Mat3(float matrixArray[9]);
			// initializes values on the matrix's diagonal
			Mat3(float val);
			Mat3(Mat4 mat);

			~Mat3();

			static Mat3 invert(const Mat3& mat);

			inline const float* getMatrixValues() const { return mMatrixValues; };
			inline float* unwrapMatrix() { return mMatrixValues; }

			//Access array value w/ row col indeces
			const float& operator()(int row, int col) const { return mMatrixValues[row * mROW_SIZE + col]; };

			static Mat3 identity;

		private:
			static const int mMAT3_SIZE = 9, mROW_SIZE = 3;

			float mMatrixValues[9] = {  0, 0, 0, 
										0, 0, 0, 
										0, 0, 0 };

			static float getDeterminant(const Mat3& mat);
	};
}

#endif // !MAT3_H
