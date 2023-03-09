#pragma once

#include "yuComponent.h"
#include "yuMesh.h"
#include "yuMaterial.h"
#include "yuBaseRenderer.h"

using namespace yu::graphics;
namespace yu
{
	class SpriteRenderer : public BaseRenderer
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}
