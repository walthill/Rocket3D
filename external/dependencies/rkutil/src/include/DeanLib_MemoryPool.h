/****************************************************************

	Pulled from Champlain College Game Architecture 
	course (EGP-310) library DeanLib

*****************************************************************/

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include "UtilDefines.h"
#include "DeanLib_CircularQueue.h"
#include "Trackable.h"

namespace rkutil
{
	class MemoryPool : public Trackable
	{
	public:
		MemoryPool(uint32 maxNumObjects, uint32 objectSize);
		~MemoryPool() { free(mMemory); delete mpFreeList; };

		void reset();//doesn't reallocate memory but does reset free list and num allocated objects

		Byte* allocateObject();
		void freeObject(Byte* ptr);

		inline uint32 getMaxObjectSize() { return mObjectSize; };
		inline uint32 getNumFreeObjects() { return mMaxNumObjects - mNumAllocatedObjects; };

	private:
		Byte* mMemory;
		Byte* mHighestValidAddress;
		uint32 mMaxNumObjects;
		uint32 mNumAllocatedObjects;
		uint32 mObjectSize;
		CircularQueue<Byte*>* mpFreeList;

		void createFreeList();
	};
}
#endif //!MEMORY_POOL_H