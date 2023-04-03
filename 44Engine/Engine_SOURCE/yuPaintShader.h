#pragma once
#include "yuComputeShader.h"
#include "yuTexture.h"

namespace yu::graphics
{
	class PaintShader : public ComputeShader
	{
	public:
		PaintShader();
		~PaintShader();

		virtual void Binds() override;
		virtual void Clear() override;

		void SetTarget(std::shared_ptr<Texture> texture) { mTarget = texture; }

	private:
		std::shared_ptr<Texture> mTarget;
	};
}
