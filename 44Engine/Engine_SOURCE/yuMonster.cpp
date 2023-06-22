#include "yuMonster.h"


namespace yu
{
	Monster::Monster()
	{
	}
	Monster::~Monster()
	{
	}
	void Monster::Initalize()
	{
		GameObject::Initalize();
	}
	void Monster::Update()
	{
		GameObject::Update();
	}
	void Monster::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Monster::Render()
	{
		GameObject::Render();
	}
	void Monster::ApplyForce(math::Vector2& force, math::Vector2& move)
	{
		mmove = move;
		velocity = velocity + force;
	}

}
