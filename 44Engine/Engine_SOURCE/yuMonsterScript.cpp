#include "yuMonsterScript.h"
#include "yuTransform.h"
#include "yuGameObject.h"
#include "yuInput.h"
#include "yuTime.h"
#include "yuAnimator.h"
#include "yuCamera.h"
#include "yuRenderer.h"
#include "yuMonster.h"
#include "yuMonster.h"

namespace yu
{
	MonsterScript::MonsterScript()
		: Script()
	{
	}

	MonsterScript::~MonsterScript()
	{
	}

	void MonsterScript::Initalize()
	{
		Animator* animator = GetOwner()->GetComponent<Animator>();

	
	}


	void MonsterScript::Update()
	{

		Transform* tr = GetOwner()->GetComponent<Transform>();
		pos = tr->GetPosition();
		Monster* owner = dynamic_cast<Monster*>(GetOwner());
		mmove = owner->getmove();
		velocity = owner->getvelocity();
		//pos = pos + mmove;
		

		math::Vector2 position = Vector2(pos.x, pos.y);
		position += velocity * Time::DeltaTime();
		tr->SetPosition(math::Vector3(position.x,position.y,pos.z));

		velocity *= dampingFactor;
		owner->setvelocity(velocity);
		owner->setmove(Vector2(0.0f,0.0f));

		Animator* animator = GetOwner()->GetComponent<Animator>();


		Postpos = pos;

	}

	void MonsterScript::Render()
	{
	}

	void MonsterScript::OnCollisionEnter(Collider2D* collider)
	{


	}

	void MonsterScript::OnCollisionStay(Collider2D* collider)
	{

	}

	void MonsterScript::OnCollisionExit(Collider2D* collider)
	{
	}

	void MonsterScript::KnockBack()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		pos = tr->GetPosition();
	}

	//void MonsterScript::ApplyForce(math::Vector2& force, math::Vector2& move)
	//{
		//mmove = move;
		//velocity = velocity+force;
	//}

	void MonsterScript::Start()
	{
	}

	void MonsterScript::Action()
	{
	}

	void MonsterScript::End()
	{

	}


}