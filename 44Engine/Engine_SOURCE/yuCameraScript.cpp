#include "yuCameraScript.h"
#include "yuTransform.h"
#include "yuGameObject.h"
#include "yuInput.h"
#include "yuTime.h"

namespace yu
{
	CameraScript::CameraScript()
		: Script()
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initalize()
	{
	}

	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 pos = tr->GetPosition();

		if (Input::GetKeyState(eKeyCode::RIGHT) == eKeyState::PRESSED)
		{
			pos += 100.0f * tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::LEFT) == eKeyState::PRESSED)
		{
			pos += 100.0f * -tr->Right() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::UP) == eKeyState::PRESSED)
		{
			pos += 100.0f * tr->Up() * Time::DeltaTime();
		}
		else if (Input::GetKeyState(eKeyCode::DOWN) == eKeyState::PRESSED)
		{
			pos += 100.0f * -tr->Up() * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}
	void CameraScript::Render()
	{
	}
}