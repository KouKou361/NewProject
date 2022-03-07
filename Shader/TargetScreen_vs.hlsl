#include "TargetScreen.hlsli"
PSInput main(VSInput input)
{
    PSInput output = (PSInput) 0;

    output.position = float4(input.position, 1.0f);
    output.tex = input.tex;
    output.color = input.color;
    return output;
}