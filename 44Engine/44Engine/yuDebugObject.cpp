#include "yuDebugObject.h"
#include "yuRenderer.h"


namespace yu
{
	DebugObject::DebugObject()
	{

	}
	DebugObject::~DebugObject()
	{

	}

	void DebugObject::FixedUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->FixedUpdate();
		}

		/*// Constant buffer
		yu::graphics::ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Debug];
		renderer::DebugCB data;
		data.color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		data.padding2 = 0.0f;

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);*/
	}


}