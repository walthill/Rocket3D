#include "include/MemoryTracker.h"
#include <map>
#include <sstream>

namespace rkutil {

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
		auto iter = mAllocRecordMap.find(addressPtr);

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
		auto iter = mAllocRecordMap.find(addressPtr);

		if (iter != mAllocRecordMap.end())
			mAllocRecordMap.erase(iter);
	}

	void MemoryTracker::reportAllocs(std::ostream & stream)
	{
		stream << "Current memory allocations" << std::endl;

		//add each allocation (ordered, with ptr & size) to a map
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

	std::vector<std::string> MemoryTracker::logAllocs()
	{
		std::string title = "Current memory allocations";
		mMemoryReports.push_back(title);

		//add each allocation (ordered, with ptr & size) to a map
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
			std::stringstream ss;
			ss << recordIter->second.address;
			std::string hexAddress = ss.str();

			std::string allocString = "Allocation Num: " + std::to_string(recordIter->first),

						addressString = " | Address: " + hexAddress,

						byteString = " | Bytes: " + std::to_string(recordIter->second.size);
			
			mMemoryReports.push_back(allocString+addressString+byteString);
		}
		return mMemoryReports;
	}
}