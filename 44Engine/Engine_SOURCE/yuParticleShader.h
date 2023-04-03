#pragma once
#include "yuComputeShader.h"
#include "yuStructedBuffer.h"

namespace yu::graphics
{
	class ParticleShader : public ComputeShader
	{
	public:
		ParticleShader();
		~ParticleShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetStrcutedBuffer(StructedBuffer* buffer) { mBuffer = buffer; }
		void SetSharedStrutedBuffer(StructedBuffer* buffer) { mSharedBuffer = buffer; }

	private:
		StructedBuffer* mBuffer;
		StructedBuffer* mSharedBuffer;
	};
}