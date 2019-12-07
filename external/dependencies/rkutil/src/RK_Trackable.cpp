#include "include/RK_MemoryTracker.h"
#include "include/RK_Trackable.h"

namespace rkutil {

#if _DEBUG

	void* Trackable::operator new(unsigned int size)
	{
		void* ptr = malloc(size);
		MemoryTracker::getInstance()->addAlloc(ptr, size);
		return ptr;
	}

	void * Trackable::operator new[](unsigned int size)
	{
		void* ptr = malloc(size);
		MemoryTracker::getInstance()->addAlloc(ptr, size);
		return ptr;
	}
	
	void Trackable::operator delete(void * ptr)
	{
		MemoryTracker::getInstance()->removeAlloc(ptr);
		free(ptr);
	}
	
	void Trackable::operator delete[](void * ptr)
	{
		MemoryTracker::getInstance()->removeAlloc(ptr);
		free(ptr);
	}

#endif
}

