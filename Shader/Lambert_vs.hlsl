#include "Lambert.hlsli"

PSInput main(VSInput input)
{
    float3 p = { 0, 0, 0 };
    float3 n = { 0, 0, 0 };
    for (int i = 0; i < 4; i++)
    {
        p += (input.boneWeights[i] * mul(input.position, boneTransforms[input.boneIndices[i]])).xyz;
        n += (input.boneWeights[i] * mul(float4(input.normal.xyz, 0), boneTransforms[input.boneIndices[i]])).xyz;
    }

    PSInput vout;
    vout.position = mul(float4(p, 1.0f), viewProjection);
	//vout.position = mul(position, viewProjection);

    float3 N = normalize(n);
    float3 L = normalize(-lightDirection.xyz);
    float d = dot(L, N) * 0.5f + 0.5f;
    vout.power = max(0, d);
    vout.color.xyz = (1, 1, 1) * vout.power;
    vout.color.w = materialColor.w;
    vout.texcoord = input.texcoord;

    return vout;
}
