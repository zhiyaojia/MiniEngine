//#include "Constants.hlsl"
//
//struct VIn
//{
//    float3 position : POSITION0;
//    float3 normal : NORMAL0;
//    float4 color : COLOR0;
//    float2 uv : TEXCOORD0;
//};
//
//struct VOut
//{
//    float4 position : SV_POSITION;
//    float4 worldPos : POSITION1;
//    float3 normal : NORMAL0;
//    float4 color : COLOR0;
//    float2 uv : TEXCOORD0;
//};
//
//VOut VS(VIn vIn)
//{
//    VOut output;
//
//    float4 pos = float4(vIn.position, 1.0);
//    output.worldPos = mul(pos, c_modelToWorld);
//    output.position = mul(output.worldPos, c_viewProj);
//    float4 norm = float4(vIn.normal, 0.0);
//    output.normal = mul(norm, c_modelToWorld).xyz;
//    output.color = vIn.color;
//    output.uv = vIn.uv;
//
//    return output;
//}
//
//float4 PS(VOut pIn) : SV_TARGET
//{
//    float4 diffuseTex = DiffuseTexture.Sample(DefaultSampler, pIn.uv);
//
//    // do the lighting
//    float3 lightColor = c_ambient;
//    float3 n = normalize(pIn.normal.xyz);
//    float3 v = normalize(c_cameraPosition - pIn.worldPos);
//    for (int i = 0; i < MAX_POINT_LIGHTS; ++i)
//    {
//        if (c_pointLight[i].isEnabled)
//        {
//            float3 l = c_pointLight[i].position - pIn.worldPos.xyz;
//            float dist = length(l);
//            if (dist > 0.0)
//            {
//                l = l / dist;
//                float falloff = smoothstep(c_pointLight[i].outerRadius, c_pointLight[i].innerRadius, dist);
//                float3 d = falloff * c_pointLight[i].lightColor * max(0.0, dot(l, n));
//                lightColor += d;
//
//                float3 r = -reflect(l, n);
//                float3 s = falloff * c_specularColor * pow(max(0.0, dot(r, v)), c_specularPower);
//                lightColor += s;
//            }
//        }
//    }
//
//    // combine the final lighting with the vertex color and the texture color 
//    float4 finalColor = pIn.color * diffuseTex * float4(lightColor, 1.0);
//    return finalColor;
//}

#include "Constants.hlsl"

struct VIn
{
    float3 position : POSITION0;
    float3 Normal : NORMAL;
    float4 color : COLOR0;
    float2 TextureUV : TEXCOORD0;
};

struct VOut
{
    float4 position : SV_POSITION;
    float3 Normal : NORMAL;
    float4 color : COLOR0;
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

    output.color = vIn.color;
    output.TextureUV = vIn.TextureUV;

    output.Normal = normalize(mul(float4(vIn.Normal, 0.0), c_modelToWorld));

    return output;
}

float4 PS(VOut pIn) : SV_TARGET
{
    pIn.Normal = normalize(pIn.Normal);

    float3 light = c_ambient;
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        PointLightData l = c_pointLight[i];
        if (!l.isEnabled) { continue; }

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

        const float3 viewDir = normalize(c_cameraPosition - pIn.WorldPos);
        const float3 reflection = normalize(reflect(-direction, pIn.Normal));
        light += c_specularColor * reducePow * pow(max(dot(reflection, viewDir), 0.0), c_specularPower);
    }

    float4 finalLight = float4(light, 1.0);
    float4 diffuse = finalLight * DiffuseTexture.Sample(DefaultSampler, pIn.TextureUV) * pIn.color;

    return diffuse;
}
