#ifndef TRACKABLE_H
#define TRACKABLE_H

#include <iostream>
#include <malloc.h>

namespace rkutil {
	
	class Trackable
	{
		public:
			void* operator new(unsigned int size);
			void* operator new[](unsigned int size);
			void operator delete(void* ptr);
			void operator delete[](void* ptr);
	};
}



#endif // !TRACKABLE_H
