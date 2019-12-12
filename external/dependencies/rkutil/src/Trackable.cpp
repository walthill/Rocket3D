#include "include/MemoryTracker.h"
#include "include/Trackable.h"

namespace rkutil {

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
}

