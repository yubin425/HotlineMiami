#pragma once
#include "CommonInclude.h"
#include "yuMath.h"
#include "yuGraphicDevice_DX11.h"

#include "yuMesh.h"
#include "yuShader.h"
#include "yuConstantBuffer.h"
#include "yuCamera.h"
#include "yuLight.h"
#include "yuStructedBuffer.h"

using namespace yu::math;
using namespace yu::graphics;

namespace yu::renderer
{
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		int iData;
		float fData;
		Vector2 xy;
		Vector3 xyz;
		Vector4 xyzw;
		Matrix matrix;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};

	CBUFFER(FadeCB, CBSLOT_FADE)
	{
		float cumultime;
	};

	CBUFFER(AnimationCB, CBSLOT_ANIMATION)
	{
		Vector2 leftTop;
		Vector2 size;
		Vector2 offset;
		Vector2 atlasSize;

		UINT type;
	};

	//CBSLOT_NUMBEROFLIGHT
	CBUFFER(LightCB, CBSLOT_NUMBEROFLIGHT)
	{
		UINT numberOfLight;
	};

	CBUFFER(ParticleSystemCB, CBSLOT_PARTICLESYSTEM)
	{
		Vector4 color;
		UINT elementCount;
		float deltaTime;
	};



	extern Vertex vertexes[4];
	extern Camera* mainCamera;
	extern ConstantBuffer* constantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];
	
	extern std::vector<Camera*> cameras[];
	extern std::vector<DebugMesh> debugMeshes;
	extern std::vector<LightAttribute> lights;
	extern StructedBuffer* lightsBuffer;

	void Initialize();
	void Render();
	void Release();

	//Renderer
	void PushLightAttribute(LightAttribute lightAttribute);
	void BindLights();

}

