#pragma once
#include "yuEntity.h"
#include "yuGraphics.h"


namespace yu::graphics
{
	class StructedBuffer : public GpuBuffer
	{
	public:
		StructedBuffer();
		~StructedBuffer();

		bool Create(UINT size, UINT stride, eSRVType type, void* data);
		void Bind(void* data, UINT bufferCount);
		void SetPipeline(eShaderStage stage, UINT slot);


		UINT GetSize() { return mSize; }
		UINT GetStride() { return mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		eSRVType mType;

		UINT mSize;
		UINT mStride;
	};
}
