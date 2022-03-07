#include "VarianceShadowMap.hlsli"
float4 main(VS_OUT input) : SV_TARGET0
{
	//return float4(input.Depth.z / input.Depth.w,0,0,1);
//4
	float LightDepth = input.Depth.z / input.Depth.w;
	return float4(LightDepth, LightDepth * LightDepth, 0, 1);
}
