#include "yuPlayerScript.h"
#include "yuTransform.h"
#include "yuGameObject.h"
#include "yuInput.h"
#include "yuTime.h"

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
	}

	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mMousPosition = Input::GetMousPosition();
		pos = tr->GetPosition();
		tr->SetPosition(Vector3(mMousPosition));

		Vector3 rotvec = pos - mMousPosition;
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

}