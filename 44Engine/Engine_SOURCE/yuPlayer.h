#pragma once
#include "yuGameObject.h"

namespace yu
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void sethp() { hp--; }

	private:
		int hp = 3;
		//GameObject* head;
		//GameObject* body;
	};
}
