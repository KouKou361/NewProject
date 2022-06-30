
#include "RenderShadow.hlsli"
#include "PointLight.hlsli"
#include "Mask.hlsli"

float4 main(PSInput pin) : SV_TARGET
{
	//���f���e�N�X�`���̎擾
	float4 color= diffuseMap.Sample(diffuseMapSamplerState, pin.texcoord);
	float3 N = normalize(pin.normal);
	float3 E = normalize(EyePos.xyz - pin.position.xyz);
	float3 L = normalize(lightDirection.xyz);
    float3 P = pin.position.xyz;

	
	//�g�U����
	float3 C =  float3(1, 1, 1);
	float3 Kd = float3(1, 1, 1);
    float3 D = Diffuse(N, L, C, Kd);

	//���ʔ���
	float3 Ks = float3(1.0f, 1.0f, 1.0f);
	float3 S = PhongSpecular(N, L, C, E, Ks, 20);
	float3 H = HalfLambert(N, L, C, float3(1,1,1));

	float3 PL = 0;
    PL = AddPointLight(pin.Wposition, N, E, Kd, Ks);
    //PL = float3(1, 0, 0);
    //PL = AddPointLight(float3(0,0,0), N, E, Kd, Ks);
	//color*= pin.color * float4(D+S+H,1.0f);
	//color *= pin.color * float4(D+S, 1.0f);

    color *= pin.color * float4(D + S + H + PL, 1.0f);

	// �V���h�E�}�b�v�K�p
    color.rgb *= GetShadow(Shadow_map, shadowmapSamplerState,
    		pin.vShadow, ShadowColor.xyz, Bias);
	

	
  
	
	     //�|�C���g���C�g
  //  float3 PL = 0;
  //  PL = AddPointLight(P, N, E, Kd, Ks);
  //  color *= color * float4( PL, 1.0);

	//color.rgb *= Shadow_map.Sample(diffuseMapSamplerState, pin.texcoord).xyz;



	return color;
}

