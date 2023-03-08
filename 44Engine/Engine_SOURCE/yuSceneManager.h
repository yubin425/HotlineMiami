#pragma once
#include "yuScene.h"

namespace yu
{
	class SceneManager
	{
	public:
		static void Initalize();
		static void Update();
		static void FixedUpdate();
		static void Render();

	private:
		static Scene* mPlayScene;
	};
}
