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



float4 main(VSOut In) : SV_TARGET
{


    float4 color = float4(1.0f,1.0f,20.f,Cumultime);
   // float4 color = float4(1.0f, 1.0f, 20.f, 1.0f);


   return color;
}