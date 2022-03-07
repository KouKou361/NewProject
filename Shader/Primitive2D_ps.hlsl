#include "Primitive2D.hlsli"
float4 main(PSInput input) :SV_TARGET
{
	float4 color = (float4)0;
	color = input.color;
	return color;
}