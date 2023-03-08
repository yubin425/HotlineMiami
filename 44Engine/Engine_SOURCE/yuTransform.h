#pragma once
#include "yuComponent.h"

using namespace yu::math;
namespace yu
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetConstantBuffer();

		Vector3 GetPosition() { return mPosition; };
		Vector3 GetRotation() { return mRotation; };
		Vector3 GetScale() { return mScale; };

		void SetPosition(Vector3 position) { mPosition = position; };
		void SetRotation(Vector3 rotation) { mRotation = rotation; };
		void SetScale(Vector3 scale) { mScale = scale; };

	private:
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;
	};
}
