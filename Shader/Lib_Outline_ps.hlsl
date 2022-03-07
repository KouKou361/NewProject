#include "Lib_Outline.hlsli"

float4 main(PSInput pin) : SV_TARGET
{
	//テクスチャの色
    float4 color = diffuseMap.Sample(diffuseMapSamplerState, pin.texcoord) * pin.color;
    return color;
}

