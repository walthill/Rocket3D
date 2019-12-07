#include "include/RK_MemoryTracker.h"
#include <map>

namespace rkutil {

#if _DEBUG

	unsigned int MemoryTracker::sNumAllocs = 0;
	MemoryTracker* MemoryTracker::mpMemoryTracker = NULL;

	MemoryTracker* MemoryTracker::getInstance()
	{
		if (mpMemoryTracker == nullptr)
			mpMemoryTracker = new MemoryTracker();

		return mpMemoryTracker;
	}

	void MemoryTracker::addAlloc(void * addressPtr, unsigned int size)
	{
		//Check if address is already in the map
		std::unordered_map<void*, AllocRecord>::iterator iter = mAllocRecordMap.find(addressPtr);

		if (iter == mAllocRecordMap.end())
		{
			AllocRecord allocRecord(sNumAllocs, size);
			std::pair<void*, AllocRecord> mapPair(addressPtr, allocRecord);
			mAllocRecordMap.insert(mapPair);
			sNumAllocs += 1;
		}
	}

	void MemoryTracker::removeAlloc(void * addressPtr)
	{
		//Check if address has already been removed from map
		std::unordered_map<void*, AllocRecord>::iterator iter = mAllocRecordMap.find(addressPtr);

		if (iter != mAllocRecordMap.end())
			mAllocRecordMap.erase(iter);
	}

	void MemoryTracker::reportAllocs(std::ostream & stream)
	{
		stream << "Current memory allocations" << std::endl;

		//add each allocation (ordered, with ptr & size) to a map
		struct ReportData
		{
			ReportData() {};
			ReportData(void* anAddr, size_t aSize): address(anAddr), size(aSize) {};
			void* address;
			unsigned int size;
		};

		std::map<int, ReportData> reportMap;

		//build map for sorting
		std::unordered_map<void*, AllocRecord>::iterator iter;
		for (iter = mAllocRecordMap.begin(); iter != mAllocRecordMap.end(); ++iter)
		{
			//iter->first == mem address
			//iter->second == byte size of ptr
			ReportData data(iter->first, iter->second.mByteSize);
			reportMap[iter->second.mRecordNum] = data;
		}

		//display allocation report in order
		std::map<int, ReportData>::iterator recordIter;
		for (recordIter = reportMap.begin(); recordIter != reportMap.end(); ++recordIter)
		{
			stream << "Allocation Num: " << recordIter->first
				   << " | Address: " << recordIter->second.address
				   << " | Bytes: " << recordIter->second.size 
				   << std::endl;
		}
	}
#endif

}