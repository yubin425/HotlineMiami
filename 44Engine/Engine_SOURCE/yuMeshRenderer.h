#pragma once
#include "yuComponent.h"
#include "yuMesh.h"
#include "yuMaterial.h"
#include "yuBaseRenderer.h"

using namespace yu::graphics;
namespace yu
{
	class MeshRenderer : public BaseRenderer
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;
	};
}