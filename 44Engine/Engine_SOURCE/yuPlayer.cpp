#include "yuPlayer.h"


namespace yu
{



	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	void Player::Initalize()
	{
		GameObject::Initalize();
	}

	void Player::Update()
	{
		
			GameObject::Update();
			//head->update();
			//body->update();
			//if (hp <= 0) { exit(0); }
	}

	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}

}
