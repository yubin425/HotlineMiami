#include "yuEndingScene.h"
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

namespace yu
{
	EndingScene::EndingScene()
		: Scene(eSceneType::Play)
	{

	}

	EndingScene::~EndingScene()
	{
	}

	void EndingScene::Initalize()
	{
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera, this);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetProjectionType(Camera::eProjectionType::Orthographic);
		//cameraComp->RegisterCameraInRenderer();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraObj->AddComponent<CameraScript>();
		//mainCamera = cameraComp;


		// Ending image
		/*GameObject* EndingSprite = object::Instantiate<GameObject>(eLayerType::Background);
		EndingSprite->SetName(L"ENDING");
		Transform* spriteEr = EndingSprite->GetComponent<Transform>();
		spriteEr->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
		spriteEr->SetScale(Vector3(10.0f, 10.0f, 10.0f));
		SpriteRenderer* sr = EndingSprite->AddComponent<SpriteRenderer>();
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");

		std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
		std::shared_ptr <Texture> ST = Resources::Find<Texture>(L"Endingimage");
		spriteMaterial->SetTexture(ST);

		sr->SetMaterial(spriteMaterial);
		sr->SetMesh(mesh);
		*/

		Scene::Initalize();
	}

	void EndingScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			std::shared_ptr<Material> spriteMaterial = Resources::Find<Material>(L"SpriteMaterial");
			std::shared_ptr <Texture> TitleST = Resources::Find<Texture>(L"Titleimage");
			spriteMaterial->SetTexture(TitleST);
			SceneManager::LoadScene(eSceneType::Title);
		}

		Scene::Update();
	}

	void EndingScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void EndingScene::Render()
	{
		Scene::Render();
	}

	void EndingScene::OnEnter()
	{

	}

	void EndingScene::OnExit()
	{

	}

}
