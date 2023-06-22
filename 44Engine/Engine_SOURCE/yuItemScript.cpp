#include "yuItemScript.h"
#include "yuTransform.h"
#include "yuGameObject.h"
#include "yuInput.h"
#include "yuTime.h"
#include "yuAnimator.h"
#include "yuCamera.h"
#include "yuRenderer.h"
#include "yuItem.h"

namespace yu
{
	ItemScript::ItemScript()
		: Script()
	{
	}

	ItemScript::~ItemScript()
	{
	}

	void ItemScript::Initalize()
	{

	}


	void ItemScript::Update()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		pos = tr->GetPosition();
		Item* owner = dynamic_cast<Item*>(GetOwner());
		mmove = owner->getmove();
		velocity = owner->getvelocity();
		//pos = pos + mmove;


		math::Vector2 position = Vector2(pos.x, pos.y);
		pos = pos + velocity*Time::DeltaTime();
		tr->SetPosition(pos);

		velocity *= dampingFactor;
		owner->setvelocity(velocity);
		owner->setmove(Vector2(0.0f, 0.0f));

		Postpos = pos;

	}

	void ItemScript::Render()
	{
	}

	void ItemScript::OnCollisionEnter(Collider2D* collider)
	{


	}

	void ItemScript::OnCollisionStay(Collider2D* collider)
	{

	}

	void ItemScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void ItemScript::KnockBack()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		pos = tr->GetPosition();
	}


	void ItemScript::Start()
	{
	}

	void ItemScript::Action()
	{
	}

	void ItemScript::End()
	{

	}


}