Texture2D MaskTexture : register(t5);

cbuffer CbSubset : register(b2)
{
	float4 materialColor;
	float maskVolume;
	float3 dummy;
};


//==============================
//マスク処理
//==============================
float4 Mask(SamplerState ss,float2 tex,float4 color)
{
	float mask_value = MaskTexture.Sample(ss, tex).r;
	// step関数を用いて透過値を0/1にする
	float alpha = step(maskVolume, mask_value);

	color.a *= alpha;
	//color.x *= mask_value;

	return color;
}
