#pragma once
#include "yuScript.h"
#include "yuMath.h"


namespace yu
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		math::Vector2 mMousPosition;
		math::Vector3 pos;
		math::Vector3 Postpos;
		math::Vector3 forward;
		math::Vector3 dirvec;

		Matrix mView;
		Matrix mProjection;

		enum::ePlayerStatus Status;
		enum::ePlayerStatus postStatus;

		void Start();
		void Action();
		void End();

	};
}
