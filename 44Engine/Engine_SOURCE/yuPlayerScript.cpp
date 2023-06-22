#include "yuPlayerScript.h"
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
		animator->GetCompleteEvent(L"PanAttack") = std::bind(&PlayerScript::End, this);
		animator->GetCompleteEvent(L"MP5Attack") = std::bind(&PlayerScript::End, this);
		//animator->GetCompleteEvent(L"Walk") = std::bind(&PlayerScript::End, this);
		//animator->GetEvent(L"Idle", 1) = std::bind(&PlayerScript::End, this);
		Status = ePlayerStatus::Idle;

		weaponStatus = eWeaponStatus::Idle;
		weapon = false;
		postweapon = false;
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

		dirvec =  mMousPosition-pos;
		dirvec.z = 0.f;

	
		float angle = atan2(dirvec.y, dirvec.x)- atan2(forward.y, forward.x);
		
		tr->SetRotation(Vector3(0.f,0.f,angle));

		//Matrix rotationz = Matrix::CreateRotationZ(angle); //z축을 기준으롤 한 회전행렬을 생성
		//Vector3 dirx = Vector3::TransformNormal(Vector3::UnitX, rotationz); //단위벡터에 곱해줌
		//Vector3 diry = Vector3::UnitZ.Cross(dirx);

		Animator* animator = GetOwner()->GetComponent<Animator>();
		
			if (Input::GetKeyState(eKeyCode::D) == eKeyState::PRESSED)
			{
				pos.x += 6.0f * Time::DeltaTime();
				tr->SetPosition(pos);

				if (Status != ePlayerStatus::Walk && Status != ePlayerStatus::Walking)
				{
					Status = ePlayerStatus::Walk;
				}

			}
			if (Input::GetKeyState(eKeyCode::A) == eKeyState::PRESSED)
			{
				pos.x -= 6.0f * Time::DeltaTime();
				tr->SetPosition(pos);
				if (Status != ePlayerStatus::Walk && Status != ePlayerStatus::Walking)
				{
					Status = ePlayerStatus::Walk;
				}
			}

			if (Input::GetKeyState(eKeyCode::W) == eKeyState::PRESSED)
			{
				pos.y += 6.0f * Time::DeltaTime();
				tr->SetPosition(pos);
				if (Status != ePlayerStatus::Walk && Status != ePlayerStatus::Walking)
				{
					Status = ePlayerStatus::Walk;
				}
			}
			if (Input::GetKeyState(eKeyCode::S) == eKeyState::PRESSED)
			{
				pos.y -= 6.0f * Time::DeltaTime();
				tr->SetPosition(pos);
				if (Status != ePlayerStatus::Walk && Status != ePlayerStatus::Walking)
				{
					Status = ePlayerStatus::Walk;
				}
			}
		


		if (Input::GetKeyState(eKeyCode::LBTN)== eKeyState::DOWN)
		{
			Status = ePlayerStatus::Attack;
			if (weaponStatus == eWeaponStatus::Pan)
			{
				animator->Play(L"PanAttack", false);
			}
			else if (weaponStatus == eWeaponStatus::Mp5)
			{
				animator->Play(L"MP5Attack", false);
			}
			else
			{
				animator->Play(L"Punch", false);
			}

		}	
		else if(postStatus == ePlayerStatus::Attack)
		{
			Status = ePlayerStatus::Attack;
		}
		else if (Status == ePlayerStatus::Walk)
		{
			Status = ePlayerStatus::Walking;

			if (weaponStatus == eWeaponStatus::Pan)
			{
				animator->Play(L"PanWalk", true);
			}
			else if (weaponStatus == eWeaponStatus::Mp5)
			{
				animator->Play(L"MP5Walk");
			}
			else
			{
				animator->Play(L"Walk", true);
			}
		}
		else if (Status != ePlayerStatus::Attack&&Postpos == pos)
		{
			Status = ePlayerStatus::Idle;
			if (weaponStatus == eWeaponStatus::Pan)
			{
				animator->Play(L"PanIdle");
			}
			else if (weaponStatus == eWeaponStatus::Mp5)
			{
				animator->Play(L"MP5Idle");
			}
			else
			{
				animator->Play(L"Idle");
			}

		}

		if (Input::GetKeyDown(eKeyCode::RBTN)&&weapon)
		{
			if (postweapon && mitem!=nullptr)
			{
				throwweapon();
			}
		}

		postStatus = Status;
		Postpos = pos; 
		postweapon = weapon;

	}

	void PlayerScript::Render()
	{
	}

	void PlayerScript::OnCollisionEnter(Collider2D* collider)
	{
		GameObject* owner = collider->GetOwner();


		// Constant buffer
		/*yu::graphics::ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Debug];
		renderer::DebugCB data;
		data.color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		data.padding2 = 0.0f;

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);*/

	}

	void PlayerScript::OnCollisionStay(Collider2D* collider)
	{
		GameObject* owner = collider->GetOwner();

		if (dynamic_cast<Monster*>(owner))
		{
			Monster* monster = dynamic_cast<Monster*>(owner);
			dynamic_cast<Player*>(GetOwner())->sethp();
			if (Status == ePlayerStatus::Attack)
			{
				owner->GetComponent<Animator>()->Play(L"fallen", true);

				//Vector3 monsterToPlayer = owner->GetComponent<Transform>()->GetPosition() - pos;
				//mMousPosition.Normalize();
				Vector3 monsterToPlayer = mMousPosition- owner->GetComponent<Transform>()->GetPosition();
				//Vector3 monsterToPlayer = dirvec;
				monsterToPlayer.Normalize();
				//monsterToPlayer = Vector3(1.0f, 1.0f, 1.0f);
				Vector3 monsterMoveAmount = monsterToPlayer * 5.0f;

				//Vector2 direction = Vector2(monsterToPlayer.x * 0.01f, monsterToPlayer.y * 0.01f);
				Vector2 moveamount = Vector2(monsterMoveAmount.x, monsterMoveAmount.y);

				monster->ApplyForce(moveamount, moveamount);
			}
		}

		if (dynamic_cast<Item*>(owner))
		{
			
			if (Input::GetKeyDown(eKeyCode::RBTN)&& mitem == nullptr)
			{
				if (mitem != nullptr && postweapon == true)
				{
					throwweapon();
				}
				Item* item = dynamic_cast<Item*>(owner);
				weaponStatus = item->getStatus();
				owner->Pause();
				weapon = true;
				mitem = owner;
			}
		}
	}

	void PlayerScript::OnCollisionExit(Collider2D* collider)
	{

	}

	void PlayerScript::throwweapon()
	{
		weaponStatus = eWeaponStatus::Idle;
		mitem->setActive();
		Transform* tr = mitem->GetComponent<Transform>();
		tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		Vector3 ItemToPlayer = mMousPosition - tr->GetPosition();
		ItemToPlayer = dirvec;
		ItemToPlayer.Normalize();
		Vector2 moveamount = Vector2(ItemToPlayer.x, ItemToPlayer.y);
		moveamount *= 25.0f;

		dynamic_cast<Item*>(mitem)->ApplyForce(moveamount, moveamount);

		mitem = nullptr;
		weapon = false;
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
		postStatus = ePlayerStatus::Idle;
		if (weaponStatus == eWeaponStatus::Pan)
		{
			animator->Play(L"PanIdle");
		}
		else if (weaponStatus == eWeaponStatus::Mp5)
		{
			animator->Play(L"MP5Idle");
		}
		else
		{
			animator->Play(L"Idle");
		}

	}


}