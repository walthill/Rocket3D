#ifndef MEM_TRACKER_H
#define MEM_TRACKER_H

#include <iostream>
#include <unordered_map>
#include "UtilDefines.h"

namespace rkutil {

	class MemoryTracker 
	{
		public:
			static MemoryTracker* getInstance();

			void addAlloc(void* addressPtr, unsigned int size);
			void removeAlloc(void* addressPtr);
			void reportAllocs(std::ostream& stream);

		private:
			struct AllocRecord 
			{
				int mRecordNum;
				uint32 mByteSize;
			
				AllocRecord(int recordNum, unsigned int size)
				{ 
					mRecordNum = recordNum;
					mByteSize = size;
				}
			};

			static uint32 sNumAllocs;
			static MemoryTracker* mpMemoryTracker;
			std::unordered_map<void*, AllocRecord> mAllocRecordMap;

			MemoryTracker() {};
			~MemoryTracker() {};
	};
}

#endif // !MEM_TRACKER_H