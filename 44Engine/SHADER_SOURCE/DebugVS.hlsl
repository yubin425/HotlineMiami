#include "globals.hlsli"
struct VSIn
{
    float4 Pos : POSITION;
    float4 Color : COLOR;

};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;

};

VSOut main(VSIn In)
{
    VSOut Out = (VSOut)0.f;

    float4 worldPosition = mul(In.Pos, world);
    float4 viewPosition = mul(worldPosition, view);
    float4 ProjPosition = mul(viewPosition, projection);

    Out.Pos = ProjPosition;
    Out.Color = float4(1.0f, 0.0f, 1.0f, 1.0f);

    return Out;
}