#include "yuComponent.h"


namespace yu
{
	Component::Component(eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}
	Component::~Component()
	{
	}
}
