#include "yuParticleShader.h"
#include "yuRenderer.h"
#include "yuConstantBuffer.h"
#include "yuTime.h"

namespace yu::graphics
{
	ParticleShader::ParticleShader()
		: ComputeShader(128, 1, 1)
		, mBuffer(nullptr)
		, mSharedBuffer(nullptr)
	{
	}

	ParticleShader::~ParticleShader()
	{
	}

	void ParticleShader::Binds()
	{
		mBuffer->BindUAV(eShaderStage::CS, 0);
		mSharedBuffer->BindUAV(eShaderStage::CS, 1);
		mGroupX = mBuffer->GetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void ParticleShader::Clear()
	{
		mBuffer->Clear();
		mSharedBuffer->Clear();
	}



}
