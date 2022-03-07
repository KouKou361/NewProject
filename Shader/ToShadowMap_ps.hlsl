#include "ToShadowMap.hlsli"
float4 main(VS_OUT input) : SV_TARGET0
{
    float LightDepth = input.Depth.z / input.Depth.w;
    return float4(LightDepth, LightDepth * LightDepth, 0, 1);
}
