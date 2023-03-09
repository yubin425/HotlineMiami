#include "yuSceneManager.h"
#include "yuTransform.h"
#include "yuMeshRenderer.h"
#include "yuRenderer.h"
#include "yuResources.h"
#include "yuTexture.h"
#include "yuPlayerScript.h"
#include "yuCamera.h"
#include "yuCameraScript.h"
#include "yuSpriteRenderer.h"
#include "yuGridScript.h"
#include "yuTitleScene.h"
#include "yuPlayScene.h"
#include "yuEndingScene.h"

namespace yu
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initalize()
	{
		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Ending] = new EndingScene();

		mActiveScene = mScenes[(UINT)eSceneType::Title];

		for (Scene* scene : mScenes)
		{
			scene->Initalize();
		}
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::FixedUpdate()
	{
		mActiveScene->FixedUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}
	
	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			delete scene;
			scene = nullptr;
		}
	}
	void SceneManager::LoadScene(eSceneType type)
	{
		if (mActiveScene)
			mActiveScene->OnExit();

		// 바뀔때 dontDestory 오브젝트는 다음씬으로 같이 넘겨줘야한다.
		std::vector<GameObject*> gameObjs 
			= mActiveScene->GetDontDestroyGameObjects();
		mActiveScene = mScenes[(UINT)type];
		
		for (GameObject* obj : gameObjs)
		{
			eLayerType type = obj->GetLayerType();
			mActiveScene->AddGameObject(obj, type);
		}

		mActiveScene->OnEnter();
	}
}