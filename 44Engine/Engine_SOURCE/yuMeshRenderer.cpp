#include "yuMeshRenderer.h"
#include "yuGameObject.h"
#include "yuTransform.h"

namespace yu
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::Mesh)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initalize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::FixedUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		GetOwner()->GetComponent<Transform>()->SetConstantBuffer();

		mMaterial->Bind();
		mMesh->BindBuffer();

		mMesh->Render();
	}
}
