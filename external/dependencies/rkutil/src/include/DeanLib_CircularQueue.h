/****************************************************************

	Pulled from Champlain College Game Architecture 
	course (EGP-310) library DeanLib

*****************************************************************/

#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "Trackable.h"
#include "UtilDefines.h"

namespace rkutil
{
	template < class T >
	class CircularQueue : public Trackable
	{
	public:
		explicit CircularQueue(uint32 size)
			: mCapacity(size)
			, mFront(0)
			, mBack(0)
			, mNumEntries(0)
		{
			mArray = new T[size];
		}

		~CircularQueue()
		{
			delete[] mArray;
		}

		void reset()
		{
			mFront = 0;
			mBack = 0;
			mNumEntries = 0;
		}

		bool pushBack(const T& item)//return false if not successfully added (not enough space)
		{
			if (mNumEntries >= mCapacity)//no room left
				return false;

			mArray[mBack] = item;
			mBack++;
			mNumEntries++;

			if (mBack >= mCapacity)
			{
				mBack = 0;
			}

			return true;
		}

		bool popFront(T& item)//returns false if queue is empty
		{
			if (mNumEntries == 0)//empty
				return false;

			item = mArray[mFront];
			mFront++;
			mNumEntries--;

			if (mFront >= mCapacity)
			{
				mFront = 0;
			}

			return true;
		}
	private:
		T* mArray;
		uint32 mCapacity;
		uint32 mBack;
		uint32 mFront;
		uint32 mNumEntries;
	};
}
#endif //!CIRCULAR_QUEUE_H