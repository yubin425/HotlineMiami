#pragma once
#include "CommonInclude.h"
#include "yuMath.h"
#include "yuGraphicDevice_DX11.h"

#include "yuMesh.h"
#include "yuShader.h"
#include "yuConstantBuffer.h"

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
		Vector4 pos;
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


	extern Vertex vertexes[4];
	extern ConstantBuffer* constantBuffers[];
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[];

	void Initialize();
	void Release();
}

