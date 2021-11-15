#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float3 Normal : NORMAL;
    float2 TextureUV : TEXCOORD0;
};

struct VOut
{
    float4 position : SV_POSITION;
    float3 Normal : NORMAL;
    float2 TextureUV : TEXCOORD0;
    float3 WorldPos : WorldPos;
};

VOut VS(VIn vIn)
{
    VOut output;

    // transform input position from model to world space
    output.position = mul(float4(vIn.position, 1.0), c_modelToWorld);
    output.WorldPos = float3(output.position.x, output.position.y, output.position.z);
    // transform position from world to projection space
    output.position = mul(output.position, c_viewProj);

    output.TextureUV = vIn.TextureUV;

    output.Normal = normalize(mul(float4(vIn.Normal, 0.0), c_modelToWorld));

    return output;
}

float4 PS(VOut pIn) : SV_TARGET
{
    float4 diffuse = DiffuseTexture.Sample(DefaultSampler, pIn.TextureUV);

    return diffuse;
}
