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

		Transform* tr;
		//PLAYER RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Player);
			obj->SetName(L"PLAYER");
			tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 0.0f, 5.0f));
			//이미지 회전하는 방법
			//tr->SetRotation(Vector3(0.0f, 180.0f, 0.0f));
			//tr->SetRotation(Vector3(0.0f, 0.0f, XM_PIDIV2 / 2.0f));
			tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.11f, 0.11f));

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


			Light* lightComp = obj->AddComponent<Light>();
			lightComp->SetType(eLightType::Point);
			lightComp->SetRadius(1.0f);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			lightComp->SetOwner(obj);
	
		}

		//Monster RECT
		{
			Monster* obj = object::Instantiate<Monster>(eLayerType::Monster);
			obj->SetName(L"MONSTER");
			tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 3.0f, 5.0f));
			tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.11f, 0.11f));

			std::shared_ptr <Texture> tex1 = Resources::Find<Texture>(L"EnemyIdleSprite");
			std::shared_ptr <Texture> tex2 = Resources::Find<Texture>(L"EnemyfallenSprite");

			Animator* animator = obj->AddComponent<Animator>();
			animator->Create(L"Idle", tex1, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 8, 0.1f);
			animator->Create(L"fallen", tex2, Vector2(0.0f, 0.0f), Vector2(64.0f, 32.0f), Vector2::Zero, 1, 0.1f);

			animator->Play(L"Idle", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"EnemyMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			//obj->AddComponent<PlayerScript>();
		}

		// MAP image
		{
			GameObject* MapSprite = object::Instantiate<GameObject>(eLayerType::Background);
			MapSprite->SetName(L"MAP");
			Transform* spriteTr = MapSprite->GetComponent<Transform>();
			spriteTr->SetPosition(Vector3(1.0f, 3.0f, 500.0f));
			spriteTr->SetScale(Vector3(20.0f, 20.0f, 1.f));
			SpriteRenderer* Mapsr = MapSprite->AddComponent<SpriteRenderer>();
			std::shared_ptr<Mesh> Mapmesh = Resources::Find<Mesh>(L"RectMesh");

			std::shared_ptr<Material> MapMaterial = Resources::Find<Material>(L"MapMaterial");

			Mapsr->SetMaterial(MapMaterial);
			Mapsr->SetMesh(Mapmesh);
			//object::DontDestroyOnLoad(TitleSprite);
		}

		//post process object
		/* {
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::PostProcess);
			obj->SetName(L"PostProcessGameObject");
			tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 2.0f));
			tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetSize(Vector2(1.0f, 0.5f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PostProcessMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}*/


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
			//PLAYER DESTROY 해줌
		{
			std::vector<GameObject*> gameObjs
				= GetGameObjects(eLayerType::Player);

			for (GameObject* obj : gameObjs)
			{
				obj->Death();
			}
		}
		//몬스터 DESTROY 해줌
		{
			std::vector<GameObject*> gameObjs
				= GetGameObjects(eLayerType::Monster);

			for (GameObject* obj : gameObjs)
			{
				obj->Death();
			}
		}
	}


}
