cbuffer Transform : register(b0)
{
    row_major matrix world;
    row_major matrix view;
    row_major matrix projection;
}

cbuffer MaterialData : register(b1)
{
    int cbiData;
    float cbfData;
    float2 cbxy;
    float3 cbxyz;
    float4 cbxyzw;
    matrix cbmat;
}

cbuffer Grid : register(b2)
{
    float4 cameraPosition;
    float2 cameraScale;
    float2 resolution;
}

cbuffer Animation : register(b3)
{
    float2 leftTop;
    float2 spriteSize;
    float2 offset;
    float2 atlasSize;

    uint animationType;
}

cbuffer Fade : register(b4)
{
    float Cumultime;
    //bool fadein;
}

cbuffer NumberOfLight : register(b5)
{
    uint numberOfLight;
}

cbuffer ParticleSystem : register(b6)
{
    float4 worldPosition;
    float4 startColor;
    float4 startSize;

    uint maxParticles;
    uint simulationSpace;
    float radius;
    float startSpeed;

    float startLifeTime;
    float deltaTime;
    float elapsedTime; //�����ð�
    int padding;
}

cbuffer Debug : register(b8)
{
    float4 debugcolor;
    float padding2;
}

//cbuffer Noise : register(b7)
//{
//    float4 NoiseSize;
//}