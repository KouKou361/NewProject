struct VSInput
{
	float3 position:POSITION;
	float3 normal:NORMAL;
	float2 tex:TEXCOORD;
	float4 color:COLOR;
};
struct PSInput
{
	float4 position:SV_POSITION;
	float2 tex:TEXCOORD;
	float4 color:COLOR;
};