Texture2D diffuseMap : register(t0);
SamplerState diffuseMapSamplerState : register(s0);

struct VS_OUT
{
	float4 position : SV_POSITION;
	float4 Depth:TEXCOORD1;//ê[ìxèÓïÒ
};

cbuffer CbScene : register(b0)
{
	row_major float4x4	viewProjection;
	float4				lightDirection;
};

#define MAX_BONES 128
cbuffer CbMesh : register(b1)
{
	row_major float4x4	boneTransforms[MAX_BONES];
};

cbuffer CbSubset : register(b2)
{
	float4				materialColor;
};