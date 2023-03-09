#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    
    float2 WorldPos : POSITION;
};

float4 main(VSOut In) : SV_TARGET
{
    float4 Out = float4(1.0f, 1.0f, 1.0f, 1.0f);
    
    const int width = 100;
    const int height = 100;
    
    uint worldX = (int) In.WorldPos.x;
    uint worldY = (int) In.WorldPos.y;
    
    // �� �β�
    const float thickness = 1.0f;
    
    if (abs((worldX + 1) % width) <= thickness)
        return Out;
    
    if (abs((worldY + 1) % height) <= thickness)
        return Out;
    
    discard;
    return float4(1.0f, 0.0f, 1.0f, 1.0f);
}