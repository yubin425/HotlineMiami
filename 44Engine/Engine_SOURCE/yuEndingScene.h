#pragma once
#include "yuScene.h"

namespace yu
{
	class EndingScene : public Scene
	{
	public:
		EndingScene();
		virtual ~EndingScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
