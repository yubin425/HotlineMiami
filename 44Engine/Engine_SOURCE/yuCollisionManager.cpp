#include "yuCollisionManager.h"
#include "yuScene.h"
#include "yuSceneManager.h"

namespace yu
{
	std::bitset<(UINT)eLayerType::End> CollisionManager::mLayerCollisionMatrix[(UINT)eLayerType::End] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap;

	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::End; row++)
		{
			for (UINT column = 0; column < (UINT)eLayerType::End; column++)
			{
				if (mLayerCollisionMatrix[row][column])
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)column);
				}
			}
		}
	}
	void CollisionManager::FixedUpdate()
	{
	}
	void CollisionManager::Render()
	{
	}
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int column = 0;

		if ((UINT)left <= (UINT)right)
		{
			row = (UINT)left;
			column = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			column = (UINT)left;
		}

		mLayerCollisionMatrix[row][column] = enable;
	}
	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		const std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		for (GameObject* left : lefts)
		{
			if (left->GetState() != GameObject::Active)
				continue;
			if (left->GetComponent<Collider2D>() == nullptr)
				continue;


			for (GameObject* right : rights)
			{
				if (right->GetState() != GameObject::Active)
					continue;
				if (right->GetComponent<Collider2D>() == nullptr)
					continue;
				if (left == right)
					continue;

				ColliderCollision(left->GetComponent<Collider2D>(), right->GetComponent<Collider2D>());
			}

			if ((UINT)left == (UINT)right)
				break;
		}

	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// �� �浹ü ���̾�� ������ ID Ȯ��
		ColliderID colliderID;
		colliderID.left = (UINT)left->GetID();
		colliderID.right = (UINT)right->GetID();

		// ���� �浹 ������ �˻��Ѵ�.
		// ���࿡ �浹������ ���� ���¶��
		// �浹������ �������ش�.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}
		
		// �浹üũ�� ���ش�.
		if (Intersect(left, right)) // �浹�� �� ����
		{
			// ���� �浹�� Enter
			if (iter->second == false)
			{
				if (left->IsTriiger())
					left->OnTriggerEnter(right);
				else
					left->OnCollisionEnter(right);

				if (right->IsTriiger())
					right->OnTriggerEnter(left);
				else
					right->OnCollisionEnter(left);

				iter->second = true;
			}
			else // �浹 ������ ���� ���� Enter
			{
				if (left->IsTriiger())
					left->OnTriggerStay(right);
				else
					left->OnCollisionStay(right);

				if (right->IsTriiger())
					right->OnTriggerStay(left);
				else
					right->OnCollisionStay(left);
			}
		}
		else // �浹���� ��������
		{
			// �浹 ���λ��� Exit
			if (iter->second == true)
			{
				if (left->IsTriiger())
					left->OnTriggerExit(right);
				else
					left->OnCollisionExit(right);

				if (right->IsTriiger())
					right->OnTriggerExit(left);
				else
					right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2

		Vector3 arrLocalPos[4] =
		{
			Vector3{-0.5f, 0.5f, 0.0f}
			,Vector3{0.5f, 0.5f, 0.0f}
			,Vector3{0.5f, -0.5f, 0.0f}
			,Vector3{-0.5f, -0.5f, 0.0f}
		};

		if (left->GetType() == eColliderType::Rect && right->GetType() == eColliderType::Rect)
		{
			Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
			Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

			Matrix leftMat = leftTr->GetWorldMatrix();
			Matrix rightMat = rightTr->GetWorldMatrix();

			// �и��� ���� 4�� ���ϱ�
			Vector3 Axis[4] = {};
	

			Vector3 leftScale = Vector3(left->GetSize().x, left->GetSize().y, 1.0f);

			Matrix finalLeft = Matrix::CreateScale(leftScale);
			finalLeft *= leftMat;

			Vector3 rightScale = Vector3(right->GetSize().x, right->GetSize().y, 1.0f);
			Matrix finalRight = Matrix::CreateScale(rightScale);
			finalRight *= rightMat;

			Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft);
			Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft);
			Axis[2] = Vector3::Transform(arrLocalPos[1], finalRight);
			Axis[3] = Vector3::Transform(arrLocalPos[3], finalRight);

			Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);
			Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);
			Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRight);
			Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRight);

			for (size_t i = 0; i < 4; i++)
				Axis[i].z = 0.0f;

			Vector3 vc = leftTr->GetPosition() - rightTr->GetPosition();
			vc.z = 0.0f;

			Vector3 centerDir = vc;
			for (size_t i = 0; i < 4; i++)
			{
				Vector3 vA = Axis[i];
				//vA.Normalize();

				float projDist = 0.0f;
				for (size_t j = 0; j < 4; j++)
				{
					projDist += fabsf(Axis[j].Dot(vA) / 2.0f);
				}

				if (projDist < fabsf(centerDir.Dot(vA)))
				{
					return false;
				}
			}
		}

		// Circle vs Cirlce
		else if (left->GetType() == eColliderType::Circle&& right->GetType() == eColliderType::Circle)
		{
			Vector2 DistanceV = Vector2(left->GetPosition()) - Vector2(right->GetPosition());
			float Distance = DistanceV.Length();
			float radius = left->GetRadius() + right->GetRadius();
			if (Distance > radius)
			{
				return false;
			}


		}



		return true;
	}
}
