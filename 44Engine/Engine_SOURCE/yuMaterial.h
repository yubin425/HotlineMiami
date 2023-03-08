#pragma once
#include "yuResource.h";
#include "yuShader.h"
#include "yuRenderer.h"
//#include "yuConstantBuffer.h"

using namespace yu::renderer;
namespace yu::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void SetData(eGPUParam param, void* data);
		void Bind();

		void SetShader(Shader* shader) { mShader = shader; }
		Shader* GetShader() { return mShader; }

	private:
		Shader* mShader;
		MaterialCB mCB;
	};
}

