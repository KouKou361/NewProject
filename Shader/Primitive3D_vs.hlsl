#include "Primitive3D.hlsli"
PSInput main(VSInput input)
{
	PSInput vs_out;

	vs_out.color = input.color;
	//MEMO:‚Æ‚è‚ ‚¦‚¸‚±‚ê‚Å
	vs_out.pos = mul(input.pos, WVP);

	return vs_out;

}
