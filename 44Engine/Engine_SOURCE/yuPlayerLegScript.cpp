#include "yuPlayerLegScript.h"
#include "yuTransform.h"
#include "yuGameObject.h"
#include "yuInput.h"
#include "yuTime.h"
#include "yuAnimator.h"
#include "yuCamera.h"
#include "yuRenderer.h"
#include "yuMonster.h"
#include "yuPlayer.h"
#include "yuMonsterScript.h"

namespace yu
{
	PlayerLegScript::PlayerLegScript()
		: Script()
	{
	}

	PlayerLegScript::~PlayerLegScript()
	{
	}

	void PlayerLegScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Status = ePlayerLegStatus::Idle;
	}


	void PlayerLegScript::Update()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		pos = tr->GetPosition();
		forward = tr->Foward();

		mMousPosition = Input::GetMousPosition();
		Camera* camera = renderer::mainCamera;
		mProjection = camera->GetProjectionMatrix();
		mView = camera->GetViewMatrix();

		mMousPosition.x = mMousPosition.x / mProjection._11;
		mMousPosition.y = mMousPosition.y / mProjection._22;
		//mMousPosition.x = mMousPosition.x +1.1;
		//mMousPosition.y = mMousPosition.y + 0.8;

		dirvec = mMousPosition - pos;
		dirvec.z = 0.f;


		float angle = atan2(dirvec.y, dirvec.x) - atan2(forward.y, forward.x);

		tr->SetRotation(Vector3(0.f, 0.f, angle));


		Animator* animator = GetOwner()->GetComponent<Animator>();

			if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
			{
				pos.x += 6.0f * Time::DeltaTime();
				tr->SetPosition(pos);

				if (Status != ePlayerLegStatus::Walk && Status != ePlayerLegStatus::Walking)
				{
					Status = ePlayerLegStatus::Walk;
				}

			}
			if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
			{
				pos.x -= 6.0f * Time::DeltaTime();
				tr->SetPosition(pos);
				if (Status != ePlayerLegStatus::Walk && Status != ePlayerLegStatus::Walking)
				{
					Status = ePlayerLegStatus::Walk;
				}
			}

			if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
			{
				pos.y += 6.0f * Time::DeltaTime();
				tr->SetPosition(pos);
				if (Status != ePlayerLegStatus::Walk && Status != ePlayerLegStatus::Walking)
				{
					Status = ePlayerLegStatus::Walk;
				}
			}
			if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
			{
				pos.y -= 6.0f * Time::DeltaTime();
				tr->SetPosition(pos);
				if (Status != ePlayerLegStatus::Walk && Status != ePlayerLegStatus::Walking)
				{
					Status = ePlayerLegStatus::Walk;
				}
			}
		



		if (Status == ePlayerLegStatus::Walk)
		{
			Status = ePlayerLegStatus::Walking;
			animator->Play(L"Walk", true);
		}
		else if (Postpos == pos)
		{
			Status = ePlayerLegStatus::Idle;
			animator->Play(L"Idle", true);
		}




		Postpos = pos;

	}

	void PlayerLegScript::Render()
	{
	}

	void PlayerLegScript::OnCollisionEnter(Collider2D* collider)
	{

	}

	void PlayerLegScript::OnCollisionStay(Collider2D* collider)
	{

	}

	void PlayerLegScript::OnCollisionExit(Collider2D* collider)
	{
	}


	void PlayerLegScript::Start()
	{
	}

	void PlayerLegScript::Action()
	{
	}

	void PlayerLegScript::End()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();
		Status = ePlayerLegStatus::Idle;
		animator->Play(L"Idle");
	}


}