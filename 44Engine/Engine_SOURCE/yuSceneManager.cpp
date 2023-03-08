#include "yuSceneManager.h"
#include "yuTransform.h"
#include "yuMeshRenderer.h"
#include "yuRenderer.h"
#include "yuResources.h"
#include "yuTexture.h"

namespace yu
{
	Scene* SceneManager::mPlayScene = nullptr;

	void SceneManager::Initalize()
	{
		mPlayScene = new Scene();
		mPlayScene->Initalize();

		GameObject* obj = new GameObject();
		Transform* tr = new Transform();
		tr->SetPosition(Vector3 (0.0f, 0.0f, 0.0f));
		obj->AddComponent(tr);

		MeshRenderer* mr = new MeshRenderer();
		obj->AddComponent(mr);
		
		Mesh* mesh = Resources::Find<Mesh>(L"RectMesh");
		Material* mateiral = Resources::Find<Material>(L"RectMaterial");

		Vector2 vec2(1.0f, 1.0f);
		mateiral->SetData(eGPUParam::Vector2, &vec2);

		mr->SetMaterial(mateiral);
		mr->SetMesh(mesh);

		Texture* texture = Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		texture->BindShader(eShaderStage::PS, 0);

		mPlayScene->AddGameObject(obj, eLayerType::Player);
	}

	void SceneManager::Update()
	{
		mPlayScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mPlayScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mPlayScene->Render();
	}
}