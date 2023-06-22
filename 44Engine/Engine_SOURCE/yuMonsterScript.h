#pragma once
#include "yuScript.h"
#include "yuMath.h"


namespace yu
{
	class MonsterScript : public Script
	{
	public:
		MonsterScript();
		~MonsterScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

		//void ApplyForce(math::Vector2& force, math::Vector2& move);

	private:
		math::Vector2 mmove;
		math::Vector3 pos;
		math::Vector3 Postpos;
		math::Vector3 forward;
		math::Vector2 velocity;

		Matrix mView;
		Matrix mProjection;

		void KnockBack();
		void Start();
		void Action();
		void End();

		float dampingFactor = 0.5f;


	};
}
