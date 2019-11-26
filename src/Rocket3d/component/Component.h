#ifndef COMPONENT_H
#define COMPONENT_H

#include <DeanLib/Trackable.h>
#include <limits>
#include "../../RocketEngine/util/EngineUtils.h"

typedef uint32 ComponentId;
const uint32 INVALID_COMPONENT_ID = UINT_MAX;

class Component : public Trackable
{
	public:
		Component(const ComponentId &id) { mId = id; };

		/*
			Virtual destructors are useful when you might potentially delete 
			an instance of a derived class through a pointer to base class:
			https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
		*/
		virtual ~Component() {};

		inline ComponentId getId() { return mId; }
	private:
		ComponentId mId;
};

#endif // !COMPONENT_H
