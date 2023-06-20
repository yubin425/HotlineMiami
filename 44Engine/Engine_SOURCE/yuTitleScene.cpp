#include "yuTitleScene.h"
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
	TitleScene::TitleScene()
		: Scene(eSceneType::Title)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{

		//paint shader
		std::shared_ptr<PaintShader> paintShader = Resources::Find<PaintShader>(L"PaintShader");
		//L"SmileTexture"
		std::shared_ptr<Texture> paintTex = Resources::Find<Texture>(L"PaintTexture");
		paintShader->SetTarget(paintTex);
		paintShader->OnExcute();


		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -100.0f));
			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			object::DontDestroyOnLoad(directionalLight);
		}

		{
			//GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
			//directionalLight->GetComponent<Transform>()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
			//Light* lightComp = directionalLight->AddComponent<Light>();
			//lightComp->SetType(eLightType::Point);
			//lightComp->SetRadius(10.0f);
			//lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);

		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;

		
		//renderer::cameras[0] = cameraComp;

		// UI Camera
		//GameObject* cameraUIObj = object::Instantiate<GameObject>(eLayerType::Camera);
		//Camera* cameraUIComp = cameraUIObj->AddComponent<Camera>();
		//cameraUIComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraUIComp->DisableLayerMasks();
		//cameraUIComp->TurnLayerMask(eLayerType::UI, true);


		// Fade Object
		{
		GameObject* fadeObject = object::Instantiate<GameObject>(eLayerType::Fade);
		MeshRenderer* fadeMr = fadeObject->AddComponent<MeshRenderer>();
		fadeMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		fadeMr->SetMaterial(Resources::Find<Material>(L"FadeMaterial"));
		FadeScript* fadeScript = fadeObject->AddComponent<FadeScript>();
		//object::DontDestroyOnLoad(fadeObject);
		}

		// Title image
		{
		GameObject* TitleSprite = object::Instantiate<GameObject>(eLayerType::Background);
		TitleSprite->SetName(L"TITLE");
		Transform* spriteTr = TitleSprite->GetComponent<Transform>();
		spriteTr->SetPosition(Vector3(1.0f, 1.0f, 100.0f));
		spriteTr->SetScale(Vector3(17.0f, 10.0f, 1.f));
		SpriteRenderer* Titlesr = TitleSprite->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> Titlemesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr <Texture> TitleST = Resources::Find<Texture>(L"Titleimage");
		spriteMaterial->SetTexture(eTextureSlot::T0, TitleST);

		Titlesr->SetMaterial(spriteMaterial);
		Titlesr->SetMesh(Titlemesh);
		object::DontDestroyOnLoad(TitleSprite);
		}

		//// HPBAR
		//GameObject* hpBar = object::Instantiate<GameObject>(eLayerType::Player);
		//hpBar->SetName(L"HPBAR");
		//Transform* hpBarTR = hpBar->GetComponent<Transform>();
		//hpBarTR->SetPosition(Vector3(-5.0f, 3.0f, 12.0f));
		//hpBarTR->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		//SpriteRenderer* hpsr = hpBar->AddComponent<SpriteRenderer>();
		//hpBar->AddComponent(hpsr);
		//std::shared_ptr<Mesh> hpmesh = Resources::Find<Mesh>(L"RectMesh");
		//std::shared_ptr<Material> hpspriteMaterial = Resources::Find<Material>(L"UIMaterial");
		//hpsr->SetMesh(hpmesh);
		//hpsr->SetMaterial(hpspriteMaterial);
		
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
			std::shared_ptr <Texture> tex2= Resources::Find<Texture>(L"PlayerPunchSprite");
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
			object::DontDestroyOnLoad(obj);
		}*/

		//cursor
		{
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Cursor);
			obj->SetName(L"CURSOR");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(2.0f, 0.0f, 5.0f));
			tr->SetScale(Vector3(0.5f, 0.5f, 1.0f));
			Collider2D* collider = obj->AddComponent<Collider2D>();
			collider->SetType(eColliderType::Rect);
			//collider->SetSize(Vector2(0.18f, 0.18f));

			SpriteRenderer* mr = obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> mateiral = Resources::Find<Material>(L"CursorMaterial");
			mr->SetMaterial(mateiral);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
			obj->AddComponent<CursorScript>();
			object::DontDestroyOnLoad(obj);
		}

		////SMILE RECT CHild
		//GameObject* child = object::Instantiate<GameObject>(eLayerType::Player);
		//child->SetName(L"SMILE");
		//Transform* childTr = child->GetComponent<Transform>();
		//childTr->SetPosition(Vector3(2.0f, 0.0f, 11.0f));
		//childTr->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//childTr->SetParent(tr);

		//MeshRenderer* childMr = child->AddComponent<MeshRenderer>();
		//std::shared_ptr<Material> childmateiral = Resources::Find<Material>(L"RectMaterial");
		//childMr->SetMaterial(childmateiral);
		//childMr->SetMesh(mesh);

		//Particle
		{
			Player* obj = object::Instantiate<Player>(eLayerType::Particle);
			obj->SetName(L"PARTICLE");
			Transform* tr = obj->GetComponent<Transform>();
			tr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
			obj->AddComponent<ParticleSystem>();
		}

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Player, true);

		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
			std::shared_ptr <Texture> ST = Resources::Find<Texture>(L"Endingimage");
			spriteMaterial->SetTexture(eTextureSlot::T0, ST);
			SceneManager::LoadScene(eSceneType::Play);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		mainCamera = cameraComp;
	}
	void TitleScene::OnExit()
	{
		
			std::vector<GameObject*> gameObjs
				= GetGameObjects(eLayerType::Camera);

			for (GameObject* obj : gameObjs)
			{
				obj->Death();
			}



	}
}
