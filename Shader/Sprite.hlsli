Texture2D diffuseTexture : register(t0);
SamplerState diffuseSampler : register(s0);

struct VSInput
{
	float3 position:POSITION;
	float2 tex:TEXCOORD;
	float4 color:COLOR;
};
struct PSInput
{
	float4 position:SV_POSITION;
	float2 tex:TEXCOORD;
	float4 color:COLOR;
};