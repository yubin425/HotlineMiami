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


float4 main(VSOut In) : SV_TARGET
{


    float4 color = float4(1.0f,1.0f,1.0f,1.0f);


    return color;
}