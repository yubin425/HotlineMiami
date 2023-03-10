#include "yuMeshRenderer.h"
#include "yuGameObject.h"
#include "yuTransform.h"

namespace yu
{
	MeshRenderer::MeshRenderer()
		: BaseRenderer(eComponentType::MeshRenerer)
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

		GetMaterial()->Bind();
		GetMesh()->BindBuffer();

		GetMesh()->Render();

		GetMaterial()->Clear();
	}
}
