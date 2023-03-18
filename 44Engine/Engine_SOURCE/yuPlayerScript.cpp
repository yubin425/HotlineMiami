#include "yuPlayerScript.h"
#include "yuTransform.h"
#include "yuGameObject.h"
#include "yuInput.h"
#include "yuTime.h"
#include "yuAnimator.h"
#include "yuCamera.h"
#include "yuRenderer.h"

namespace yu
{
	PlayerScript::PlayerScript()
		: Script()
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		animator->GetStartEvent(L"Idle") = std::bind(&PlayerScript::Start, this);
		animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		animator->GetEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
	}


	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		pos = tr->GetPosition();

		mMousPosition = Input::GetMousPosition();
		Camera* camera = renderer::mainCamera;
		mProjection= camera->GetProjectionMatrix();
		mView = camera->GetViewMatrix();

		mMousPosition.x = mMousPosition.x / mProjection._11;
		mMousPosition.y = mMousPosition.y / mProjection._22;


		tr->SetPosition(Vector3(mMousPosition.x, mMousPosition.y,pos.z));
		
		//Vector3 rotvec = pos - mMousPosition;
		//rotvec.To ToEuler

		//rot.z += 10.0f * Time::DeltaTime();
		//tr->SetRotation(rot);
		
		/* mMousPosition = Input::GetMousPosition();
		 pos = tr->GetPosition();
		
			//Vector3 rot = tr->GetRotation();
			Vector3 rot = tr->GetRotation();
			Quaternion rotfi;
			rot.x = mMousPosition.x;
			rot.y = mMousPosition.y;
			rotfi=Quaternion::LookRotation(rot,pos);
			tr->SetRotation(rotfi);
		*/

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos = tr->GetPosition();
			pos.x += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos = tr->GetPosition();
			pos.x -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos = tr->GetPosition();
			pos.y += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos = tr->GetPosition();
			pos.y -= 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		Animator* animator = GetOwner()->GetComponent<Animator>();
		if (Input::GetKey(eKeyCode::N_1))
		{
			animator->Play(L"Idle");
		}

	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{
	}


	void PlayerScript::Start()
	{
	}

	void PlayerScript::Action()
	{
	}

	void PlayerScript::End()
	{
	}


}