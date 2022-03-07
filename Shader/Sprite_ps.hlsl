#include "Sprite.hlsli"
float4 main(PSInput input) :SV_TARGET0
{
    float4 color = diffuseTexture.Sample(diffuseSampler, input.tex) * input.color;
    //color += input.color;
   // color.w = 0.1f;
    return color;
}