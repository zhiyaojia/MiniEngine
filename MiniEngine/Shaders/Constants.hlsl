// We want to use row major matrices
#pragma pack_matrix(row_major)

cbuffer PerCameraConstants : register(b0)
{
    float4x4 c_viewProj;
    float3 c_cameraPosition;
};

cbuffer PerObjectConstants : register(b1)
{
    float4x4 c_modelToWorld;
};

#define MAX_POINT_LIGHTS 8
struct PointLightData
{
    float3 diffuseColor;
    float3 specularColor;
    float3 position;
    float specularPower;
    float innerRadius;
    float outerRadius;
    bool isEnabled;
};

cbuffer LightingConstants : register(b2)
{
    float3	c_ambient;
    PointLightData c_pointLight[MAX_POINT_LIGHTS];
};

cbuffer PerParticleConstants : register(b3)
{
    float3 c_pos;
    float c_size;
};

cbuffer ParticleConst : register(b0)
{                                   
    float c_deltaTime;
    float c_gravity;
    float c_startSize;
    float c_endSize;
    float c_timeOut;
};

SamplerState DefaultSampler : register(s0);
Texture2D DiffuseTexture : register(t0);
