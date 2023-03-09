#include "yuFadeScript.h"
#include "yuTransform.h"
#include "yuGameObject.h"
#include "yuApplication.h"
#include "yuConstantBuffer.h"
#include "yuRenderer.h"

extern yu::Application application;

namespace yu
{
    FadeScript::FadeScript()
        : Script(),
        fadein(true)
    {

    }

    FadeScript::~FadeScript()
    {

    }

    void FadeScript::Initalize()
    {

    }

    void FadeScript::Update()
    {
        fadein = false; //fade in�� ���� out�� ���� ������ �� �ִ�. 
        float time = Time::DeltaTime();
        float FadeTime = 2.0f; //Fadeinout�� �ð�
        if (CumulTime <= 1)
        {
            CumulTime += (float)time / FadeTime;
        }


        // Constant buffer
        ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Fade];
        renderer::FadeCB data;
        if (fadein) { data.cumultime = CumulTime; }
        else { data.cumultime = 1.0f - CumulTime; }

        cb->Bind(&data);
        cb->SetPipline(eShaderStage::VS);
        cb->SetPipline(eShaderStage::PS);
    }

    void FadeScript::FixedUpdate()
    {
    }

    void FadeScript::Render()
    {
    }
}