
#include "RenderShadow.hlsli"
#include "Mask.hlsli"

PSInput main(VSInput input)
{
	float3 p = { 0, 0, 0 };
	float3 n = { 0, 0, 0 };
	for (int i = 0; i < 4; i++)
	{
		p += (input.boneWeights[i] * mul(input.position, boneTransforms[input.boneIndices[i]])).xyz;
		n += (input.boneWeights[i] * mul(float4(input.normal.xyz, 0), boneTransforms[input.boneIndices[i]])).xyz;
	}

	PSInput output;
	output.position = mul(float4(p, 1.0f), viewProjection);
	//output.position = mul(position, viewProjection);
    output.Wposition = p;
	output.color = materialColor;
	output.normal = n;
	output.texcoord = input.texcoord;
	//output.vShadow = float3( 1,1,1 );
	output.vShadow = GetShadowTex(LightViewProjection,p.xyz);

	return output;
}
