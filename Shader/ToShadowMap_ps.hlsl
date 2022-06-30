#include "ToShadowMap.hlsli"
#include "Mask.hlsli"
float4 main(VS_OUT input) : SV_TARGET0
{
    float LightDepth = input.Depth.z / input.Depth.w;
    float4 color=float4(LightDepth, LightDepth * LightDepth, 0, 1);

   float4 mask = Mask(diffuseMapSamplerState, input.texcoord, color);

   return float4(color.x, color.y, color.z, mask.a);
}
