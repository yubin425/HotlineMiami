#pragma once
#include "yuEntity.h"
#include "yuLayer.h"
#include "yuGameObject.h"

namespace yu
{
	using namespace yu::enums;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameObj, const eLayerType type);

	private:
		std::vector<Layer> mLayers;
	};
}
