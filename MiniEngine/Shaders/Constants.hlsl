// We want to use row major matrices
#pragma pack_matrix(row_major)

cbuffer PerCameraConstants : register(b0)
{
    float4x4 c_viewProj;
    float3 c_cameraPosition;
}

cbuffer PerObjectConstants : register(b1)
{
    float4x4 c_modelToWorld;
}

cbuffer MaterialConstants : register(b2)
{
    float3 c_diffuseColor;
    float3 c_specularColor;
    float c_specularPower;
}

#define MAX_POINT_LIGHTS 8
struct PointLightData
{
    float3 lightColor;
    float3 position;
    float innerRadius;
    float outerRadius;
    bool isEnabled;
};

cbuffer LightingConstants : register(b3)
{
    float3	c_ambient;
    PointLightData c_pointLight[MAX_POINT_LIGHTS];
}

#define MAX_SKELETON_BONES 80
cbuffer SkinConstants : register(b4)
{
    float4x4 c_skinMatrix[MAX_SKELETON_BONES];
}

//cbuffer PerParticleConstants : register(b5)
//{
//    float3 c_pos;
//    float c_size;
//};

//cbuffer ParticleConst : register(b0)
//{                                   
//    float c_deltaTime;
//    float c_gravity;
//    float c_startSize;
//    float c_endSize;
//    float c_timeOut;
//};

SamplerState DefaultSampler : register(s0);
Texture2D DiffuseTexture : register(t0);
