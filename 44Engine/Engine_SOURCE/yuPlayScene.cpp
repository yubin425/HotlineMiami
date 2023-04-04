#include "yuPlayScene.h"
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
#include "yuObject.h"
#include "yuInput.h"
#include "yuCollider2D.h"
#include "yuPlayer.h"
#include "yuMonster.h"
#include "yuCollisionManager.h"
#include "yuFadeScript.h"
#include "yuAnimator.h"
#include "yuCursorScript.h"
#include "yuLight.h"
#include "yuPaintShader.h"
#include "yuParticleSystem.h"



namespace yu
{
	PlayScene::PlayScene()
		: Scene(eSceneType::Play)
	{
		
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initalize()
	{
		/*//PLAYER RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"PLAYER");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 0.0f, 5.0f));
			//이미지 회전하는 방법
			//tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));
			tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.18f, 0.18f));

			std::shared_ptr <Texture> tex1 = Resources::Find<Texture>(L"PlayerWalkSprite");
			std::shared_ptr <Texture> tex2 = Resources::Find<Texture>(L"PlayerPunchSprite");
			std::shared_ptr <Texture> tex3 = Resources::Find<Texture>(L"PlayerIdleSprite");

			Animator* animator = obj->AddComponent<Animator>();
			animator->Create(L"Idle", tex3, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"Punch", tex2, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
			animator->Create(L"Walk", tex1, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 8, 0.1f);

			animator->Play(L"Idle", true);


			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerScript>();
			obj->Pause();
		}*/
	
		Scene::Initalize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}

		Scene::Update();
	}

	void PlayScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		//Pause 상태로 비활성화 해놓은 player를 active 해준다.
		std::vector<GameObject*> gameObjs
			= GetGameObjects(eLayerType::Player);

		for (GameObject* obj : gameObjs)
		{
			obj->Active();
		}

		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;


	}


	void PlayScene::OnExit()
	{
		//씬 나갈때 다시 pause로 없애준다 
		{
			std::vector<GameObject*> gameObjs
			= GetGameObjects(eLayerType::Player);

			for (GameObject* obj : gameObjs)
			{
			obj->Pause();
			}
		}
		{
			//camera 겹치지 않도록 destroy
			std::vector<GameObject*> gameObjs
				= GetGameObjects(eLayerType::Camera);

			for (GameObject* obj : gameObjs)
			{
				obj->Death();
			}
		}
	}


}
