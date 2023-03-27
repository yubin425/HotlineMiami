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
		//animator->GetCompleteEvent(L"Idle") = std::bind(&PlayerScript::Action, this);
		//animator->GetEndEvent(L"Idle") = std::bind(&PlayerScript::End, this);
		animator->GetCompleteEvent(L"Punch") = std::bind(&PlayerScript::End, this);
		//animator->GetCompleteEvent(L"Walk") = std::bind(&PlayerScript::End, this);
		//animator->GetEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
		Status = ePlayerStatus::Idle;
	}


	void PlayerScript::Update()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		pos = tr->GetPosition(); 
		forward = tr->Foward();

		mMousPosition = Input::GetMousPosition();
		Camera* camera = renderer::mainCamera;
		mProjection= camera->GetProjectionMatrix();
		mView = camera->GetViewMatrix();

		mMousPosition.x = mMousPosition.x / mProjection._11 ;
		mMousPosition.y = mMousPosition.y / mProjection._22;
		//mMousPosition.x = mMousPosition.x +1.1;
		//mMousPosition.y = mMousPosition.y + 0.8;

		Vector3 dirvec =  mMousPosition-pos;
		dirvec.z = 0.f;

	
		float angle = atan2(dirvec.y, dirvec.x)- atan2(forward.y, forward.x);
		
		tr->SetRotation(Vector3(0.f,0.f,angle));

		Matrix rotationz = Matrix::CreateRotationZ(angle); //z축을 기준으롤 한 회전행렬을 생성
		Vector3 dirx = Vector3::TransformNormal(Vector3::UnitX, rotationz); //단위벡터에 곱해줌
		Vector3 diry = Vector3::UnitZ.Cross(dirx);

		Animator* animator = GetOwner()->GetComponent<Animator>();

		if (Status == ePlayerStatus::Walk)
		{
			//animator->Play(L"Walk", true);
			Status = ePlayerStatus::Idle;
			animator->Play(L"Idle");
		}

		if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
		{
			pos.x +=  6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			if (Status != ePlayerStatus::Walk)
			{
				animator->Play(L"Walk", true);
				Status = ePlayerStatus::Walk;
			}
	
		}
		if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
		{
			pos.x -=  6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			if (Status != ePlayerStatus::Walk)
			{
				animator->Play(L"Walk", true);
				Status = ePlayerStatus::Walk;
			}
		}

		if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
		{
			pos.y += 6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			if (Status != ePlayerStatus::Walk)
			{
				animator->Play(L"Walk", true);
				Status = ePlayerStatus::Walk;
			}
		}
		if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
		{
			pos.y -=  6.0f * Time::DeltaTime();
			tr->SetPosition(pos);
			if (Status != ePlayerStatus::Walk)
			{
				animator->Play(L"Walk", true);
				Status = ePlayerStatus::Walk;
			}
		}

		
		if (Input::GetKeyState(eKeyCode::LBTN)== eKeyState::DOWN)
		{
			Status = ePlayerStatus::Attack;
			animator->Play(L"Punch", false);
		}

		
		//else if (Status == ePlayerStatus::Walk)
		//{
			//animator->Play(L"Walk", false);
		//}

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
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Status = ePlayerStatus::Idle;
		animator->Play(L"Idle");
	}


}