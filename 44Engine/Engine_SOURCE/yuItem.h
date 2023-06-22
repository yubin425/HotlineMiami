#pragma once
#include "yuGameObject.h"

namespace yu
{
	class Item : public GameObject
	{
	public:
		Item();
		virtual ~Item();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void ApplyForce(math::Vector2& force, math::Vector2& move);

		Vector2 getmove() { return mmove; }
		Vector2 getvelocity() { return velocity; }
		void setvelocity(Vector2 velo) { velocity = velo; }
		void setmove(Vector2 move) { mmove = move; }
		void setStatus(eWeaponStatus mweaponStatus) {weaponStatus = mweaponStatus;}
		eWeaponStatus getStatus() { return weaponStatus; }

	private:
		math::Vector2 mmove;
		math::Vector2 velocity;
		enum::eWeaponStatus weaponStatus;
		
	};
}