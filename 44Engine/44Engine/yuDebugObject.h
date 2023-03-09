#pragma once
#include "yuGameObject.h"


namespace yu
{
	class DebugObject : public GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void FixedUpdate() override;
	
	private:
	};
}
