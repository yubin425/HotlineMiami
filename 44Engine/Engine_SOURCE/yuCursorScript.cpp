#include "yuCursorScript.h"
#include "yuTransform.h"
#include "yuGameObject.h"
#include "yuInput.h"
#include "yuTime.h"
#include "yuAnimator.h"
#include "yuCamera.h"
#include "yuRenderer.h"

namespace yu
{
	CursorScript::CursorScript()
		: Script()
	{
	}

	CursorScript::~CursorScript()
	{
	}

	void CursorScript::Initalize()
	{
	
	}


	void CursorScript::Update()
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

		Vector3 dirvec = mMousPosition - pos;
		dirvec.z = 0.f;


		float angle = atan2(dirvec.y, dirvec.x) - atan2(forward.y, forward.x);

		tr->SetPosition(Vector3(mMousPosition));



	}

	void CursorScript::Render()
	{
	}

	void CursorScript::OnCollisionEnter(Collider2D* collider)
	{
	}

	void CursorScript::OnCollisionStay(Collider2D* collider)
	{
	}

	void CursorScript::OnCollisionExit(Collider2D* collider)
	{
	}


	void CursorScript::Start()
	{
	}

	void CursorScript::Action()
	{
	}

	void CursorScript::End()
	{
	
	}


}