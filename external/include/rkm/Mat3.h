#ifndef MAT3_H
#define MAT3_H

namespace rkm {
	class Mat3
	{
		public:
			Mat3();
			Mat3(float matrixArray[9]);
			~Mat3();

			inline const float* getMatrixValues() const { return mMatrixValues; };
			inline float* unwrapMatrix() { return mMatrixValues; }

			//Access array value w/ row col indeces
			float operator()(int row, int col) { return mMatrixValues[row * mROW_SIZE + col]; };

		private:
			const unsigned int mROW_SIZE = 3;

			float mMatrixValues[9] = {  0, 0, 0, 
										0, 0, 0, 
										0, 0, 0 };

	};
}

#endif // !MAT3_H
