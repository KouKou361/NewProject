struct VSInput
{
	float4 pos:POSITION;
	float4 normal : NORMAL;
	float2 tex : TEXCOORD;
	float4 color:COLOR;
};

struct PSInput
{
	float4 pos:SV_POSITION;
	float4 color:COLOR;
};

cbuffer ConstantBuffer: register(b0)
{
	row_major float4x4 WVP;
};