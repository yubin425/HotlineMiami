#pragma once
#include "yuScript.h"


namespace yu
{
	class CameraScript : public Script
	{
	public:
		CameraScript();
		~CameraScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

	private:

	};
}
