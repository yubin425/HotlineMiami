#include "yuItem.h"


namespace yu
{
	Item::Item()
	{
	}
	Item::~Item()
	{
	}
	void Item::Initalize()
	{
		GameObject::Initalize();
	}
	void Item::Update()
	{
		GameObject::Update();
	}
	void Item::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Item::Render()
	{
		GameObject::Render();
	}
	void Item::ApplyForce(math::Vector2& force, math::Vector2& move)
	{
		mmove = move;
		velocity = velocity + force;
	}

}
