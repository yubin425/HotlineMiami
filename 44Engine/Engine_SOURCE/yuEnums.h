#pragma once

namespace yu::enums
{
	enum class eSceneType
	{
		Title,
		Play,
		Ending,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Grid,
		Background,
		Camera,
		
		
		Monster,
		Item,
		Leg,
		Player,

		Fade,
		Cursor,
		Particle,
		PostProcess,
		UI,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Camera,
		Mesh,
		Collider,
		//Collider2,
		MeshRenerer,
		SpriteRenderer,
		Animator,
		ParticleSystem,
		Light,
		UI,
		//FadeOut,FadeIn
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};

	enum class eCollisionType
	{
		None,
		Collision,
		Detect,
		Sound,
		End,
	};

	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimension,
		End,
	};

	enum class ePlayerStatus
	{
		Idle,
		Walk,
		Walking,
		Attack,
		End,
	};

	enum class ePlayerLegStatus
	{
		Idle,
		Walk,
		Walking,
		End,
	};


	enum class eMonsterStatus
	{
		Idle,
		Walk,
		Walking,
		Attack,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};

}