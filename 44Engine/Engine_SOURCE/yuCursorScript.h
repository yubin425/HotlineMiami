#pragma once
#include "yuScript.h"
#include "yuMath.h"


namespace yu
{
	class CursorScript : public Script
	{
	public:
		CursorScript();
		~CursorScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;

	private:
		math::Vector2 mMousPosition;
		math::Vector3 pos;
		math::Vector3 forward;

		Matrix mView;
		Matrix mProjection;

		void Start();
		void Action();
		void End();

	};
}
