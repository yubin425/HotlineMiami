#pragma once
#include "..\Engine_SOURCE\yuGameObject.h"


namespace yu
{
	class EditorObject : public GameObject
	{
	public:
		EditorObject();
		virtual ~EditorObject();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	private:
		
	};
}