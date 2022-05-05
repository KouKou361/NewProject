#include "Lib_Outline.hlsli"

GSInput main(VSInput input)
{
    float3 p = { 0, 0, 0 };
    float3 n = { 0, 0, 0 };
    for (int i = 0; i < 4; i++)
    {
        p += (input.boneWeights[i] * mul(input.position, boneTransforms[input.boneIndices[i]])).xyz;
        n += (input.boneWeights[i] * mul(float4(input.normal.xyz, 0), boneTransforms[input.boneIndices[i]])).xyz;
    }

    GSInput vout;
    vout.pos = float4(p, 1.0f);
    vout.normal = float4(normalize(n), 1.0f);
	//vout.position = mul(position, viewProjection);
    //vout.pos = mul(float4(p, 1.0f), viewProjection);
    //vout.wNormal = n;

    float3 N = normalize(n);
    float3 L = normalize(-lightDirection.xyz);
    float d = dot(L, N) * 0.5f + 0.5f;
    vout.power = max(0, d);
    vout.color.xyz = float3(1, 1, 1) * vout.power;
    vout.color.w = materialColor.w;
    vout.texcoord = input.texcoord;

    return vout;
}
