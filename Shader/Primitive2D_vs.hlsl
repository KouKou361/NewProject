#include "Primitive2D.hlsli"
PSInput main(VSInput input)
{
	PSInput output=(PSInput)0;
	output.position = float4(input.position,1.0);
	output.color = input.color;
	output.tex = input.tex;
	return output;

}
