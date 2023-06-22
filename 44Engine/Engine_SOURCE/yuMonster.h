#pragma once
#include "yuGameObject.h"

namespace yu
{
	class Monster : public GameObject
	{
	public:
		Monster();
		virtual ~Monster();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void ApplyForce(math::Vector2& force, math::Vector2& move);

		Vector2 getmove() { return mmove; }
		Vector2 getvelocity() { return velocity; }
		void setvelocity(Vector2 velo) { velocity = velo; }
		void setmove(Vector2 move) { mmove = move; }

	private:
		math::Vector2 mmove;
		math::Vector2 velocity;
	};
}