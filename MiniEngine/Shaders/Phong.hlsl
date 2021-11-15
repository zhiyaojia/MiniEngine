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
    pIn.Normal = normalize(pIn.Normal);
	const float3 viewDir = normalize(c_cameraPosition - pIn.WorldPos);
    float3 light = c_ambient;
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        const PointLightData l = c_pointLight[i];
        if (l.isEnabled == false) { continue; }

        const float dist = distance(l.position, pIn.WorldPos);
        float reducePow = 1.0;
        if (dist <= l.innerRadius) { reducePow = 1.0; }
        else if (dist >= l.outerRadius) { reducePow = 0.0; }
        else if (dist > l.innerRadius && dist < l.outerRadius)
        {
            reducePow = 1 - smoothstep(l.innerRadius, l.outerRadius, dist);
        }

        const float3 direction = normalize(l.position - pIn.WorldPos);
        light += l.lightColor * reducePow * max(dot(pIn.Normal, direction), 0.0);

        const float3 reflection = normalize(reflect(-direction, pIn.Normal));
        light += c_specularColor * reducePow * pow(max(dot(reflection, viewDir), 0.0), c_specularPower);
    }

    float4 diffuse = saturate(float4(light, 1.0)) * DiffuseTexture.Sample(DefaultSampler, pIn.TextureUV);

    return diffuse;
}
