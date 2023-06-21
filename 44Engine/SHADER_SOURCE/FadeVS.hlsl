#include "globals.hlsli"
struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;

};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;

};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut)0.f;

    float4 worldPosition = mul(In.Pos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 ProjPosition = mul(viewPosition, projection);

    const float meshScale = 2.0f;
    Out.Pos = ProjPosition; 
    Out.Pos =  float4(In.Pos.xy * meshScale, 0.0f, 0.0f);
    Out.UV = In.UV;
    Out.Color = float4(1.0f, 1.0f, 1.0f, 0.5f);
    //Out.Time = Cumultime;

    return Out;
}