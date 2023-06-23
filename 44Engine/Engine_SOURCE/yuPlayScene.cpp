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
#include "yuMonsterScript.h"
#include "yuPlayerLegScript.h"
#include "yuItem.h"
#include "yuItemScript.h"

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

		if (Input::GetKeyDown(eKeyCode::X))
		{
			exit(0);
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

			std::shared_ptr <Texture> tex4 = Resources::Find<Texture>(L"PlayerPanAttackSprite");
			std::shared_ptr <Texture> tex5 = Resources::Find<Texture>(L"PlayerPanWalkSprite");

			std::shared_ptr <Texture> tex6 = Resources::Find<Texture>(L"PlayerMP5AttackSprite");
			std::shared_ptr <Texture> tex7 = Resources::Find<Texture>(L"PlayerMP5WalkSprite");

			Animator* animator = obj->AddComponent<Animator>();
			animator->Create(L"Idle", tex3, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);
			animator->Create(L"Punch", tex2, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.08f);
			animator->Create(L"Walk", tex1, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 8, 0.1f);

			animator->Create(L"PanAttack", tex4, Vector2(0.0f, 0.0f), Vector2(48.0f, 70.0f), Vector2::Zero, 8, 0.08f);
			animator->Create(L"PanWalk", tex5, Vector2(0.0f, 0.0f), Vector2(32.0f, 34.0f), Vector2::Zero, 8, 0.1f);
			animator->Create(L"PanIdle", tex5, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);

			animator->Create(L"MP5Attack", tex6, Vector2(0.0f, 0.0f), Vector2(52.0f, 32.0f), Vector2::Zero, 3, 0.08f);
			animator->Create(L"MP5Walk", tex7, Vector2(0.0f, 0.0f), Vector2(52.0f, 32.0f), Vector2::Zero, 8, 0.1f);
			animator->Create(L"MP5Idle", tex7, Vector2(0.0f, 0.0f), Vector2(52.0f, 32.0f), Vector2::Zero, 1, 0.1f);

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
		//PLAYER Leg RECT
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Leg);
			obj->SetName(L"PLAYERLEG");
			tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 0.0f, 5.0f));
			tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

			std::shared_ptr <Texture> tex1 = Resources::Find<Texture>(L"PlayerLegSprite");

			Animator* animator = obj->AddComponent<Animator>();
			animator->Create(L"Walk", tex1, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 16, 0.05f);
			animator->Create(L"Idle", tex1, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 1, 0.1f);

			animator->Play(L"Idle", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"PlayerLegMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<PlayerLegScript>();

		}

		//Monster RECT
		{
			Monster* obj = object::Instantiate<Monster>(eLayerType::Item);
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
			obj->AddComponent<MonsterScript>();
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

		//Weapon1 RECT
		{
			Item* obj = object::Instantiate<Item>(eLayerType::Item);
			obj->SetName(L"WEAPON");
			obj->setStatus(eWeaponStatus::Pan);
			tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 1.0f, 5.0f));
			tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.11f, 0.07f));
			
			std::shared_ptr <Texture> tex1 = Resources::Find<Texture>(L"weaponSprite");

			Animator* animator = obj->AddComponent<Animator>();
			animator->Create(L"pan", tex1, Vector2(1320.0f, 0.0f), Vector2(60.0f,60.0f), Vector2::Zero, 1, 0.1f);
			animator->Play(L"pan", false);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Weapon1Material");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<ItemScript>();
		}

		//Weapon2 RECT
		{
			Item* obj = object::Instantiate<Item>(eLayerType::Item);
			obj->SetName(L"WEAPON");
			obj->setStatus(eWeaponStatus::Mp5);
			tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(3.0f, 1.0f, 5.0f));
			tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.11f, 0.07f));

			std::shared_ptr <Texture> tex1 = Resources::Find<Texture>(L"weaponSprite");

			Animator* animator = obj->AddComponent<Animator>();
			animator->Create(L"mp5", tex1, Vector2(720.0f, 0.0f), Vector2(60.0f, 60.0f), Vector2::Zero, 1, 0.1f);
			animator->Play(L"mp5", false);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Weapon2Material");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<ItemScript>();
		}

		//Bullet RECT
		{
			Item* obj = object::Instantiate<Item>(eLayerType::Item);
			obj->SetName(L"WEAPON");
			obj->setStatus(eWeaponStatus::Bullet);
			tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(1.0f, 1.0f, 5.0f));
			tr->SetScale(Vector3(5.0f, 5.0f, 1.0f));

			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			collider->SetSize(Vector2(0.07f, 0.05f));

			std::shared_ptr <Texture> tex1 = Resources::Find<Texture>(L"BulletSprite");

			Animator* animator = obj->AddComponent<Animator>();
			animator->Create(L"bullet", tex1, Vector2(0.0f, 0.0f), Vector2(8.0f, 3.0f), Vector2::Zero, 8, 0.05f);
			animator->Play(L"bullet", true);

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"Weapon2Material");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<ItemScript>();
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
