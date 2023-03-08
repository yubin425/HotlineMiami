#pragma once
#include "yuComponent.h"
#include "yuMesh.h"
#include "yuMaterial.h"

using namespace yu::graphics;
namespace yu
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		void SetMesh(Mesh* mesh) { mMesh = mesh; }
		void SetMaterial(Material* shader) { mMaterial = shader; }

	private:
		Mesh* mMesh;
		Material* mMaterial;
	};
}