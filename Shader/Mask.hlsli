Texture2D MaskTexture : register(t5);

cbuffer CbSubset : register(b2)
{
	float4 materialColor;
	float maskVolume;
	float3 dummy;
};


//==============================
//�}�X�N����
//==============================
float4 Mask(SamplerState ss,float2 tex,float4 color)
{
	float mask_value = MaskTexture.Sample(ss, tex).r;
	// step�֐���p���ē��ߒl��0/1�ɂ���
	float alpha = step(maskVolume, mask_value);

	color.a *= alpha;
	//color.x *= mask_value;

	return color;
}
