#pragma once
#include "yuScript.h"
#include "yuCamera.h"
#include "yuTime.h"

namespace yu
{
    class FadeScript : public Script
    {
    public:
        FadeScript();
        virtual ~FadeScript();

        virtual void Initalize();
        virtual void Update();
        virtual void FixedUpdate();
        virtual void Render();


    private:
        float CumulTime = 0.f;
        bool fadein;
    };
}