
#include "Cascade.hlsli"
#include "PointLight.hlsli"

float4 main(PSInput pin) : SV_TARGET
{
	//モデルテクスチャの取得
    float4 color = diffuseMap.Sample(diffuseMapSamplerState, pin.texcoord);
    
        // 法線マッピング
    float3 N;
    {
        float3 VX = normalize(pin.VX);
        float3 VY = normalize(pin.VY);
        float3 VZ = normalize(pin.VZ);

        //接空間からワールド空間へ変換する行列
        float3x3 mat = { VX, VY, VZ };
        N = NormalTexture.Sample(diffuseMapSamplerState, pin.texcoord).rgb;
        N = N * 2.0 - 1.0;
        //ノーマルテクスチャ法線をワールドへ変換
        N = normalize(mul(N, mat));
    }
  //  N += normalize(pin.normal);
   // float3 N = normalize(pin.normal);
    float3 E = normalize(EyePos.xyz - pin.position.xyz);
    float3 L = normalize(lightDirection.xyz);
    float3 P = float3(pin.position.x, pin.position.y, pin.position.z);

	
	//拡散反射
    float3 C = float3(1, 1, 1);
    float3 Kd = float3(1, 1, 1);
    float3 D = Diffuse(N, L, C, Kd);

	//鏡面反射
    float3 Ks = float3(1.0f, 1.0f, 1.0f);
    float3 S = PhongSpecular(N, L, C, E, Ks, 20);
    float3 H = HalfLambert(N, L, C, float3(1, 1, 1));

    float3 PL = 0;
    PL = AddPointLight(pin.Wposition, N, E, Kd, Ks);
    //PL = float3(1, 0, 0);
    //PL = AddPointLight(float3(0,0,0), N, E, Kd, Ks);
	//color*= pin.color * float4(D+S+H,1.0f);
	//color *= pin.color * float4(D+S, 1.0f);

    color *= pin.color * float4(D + S + H + PL, 1.0f);

	// シャドウマップ適用
    color.xyz *= GetCascadeShadow(pin.Wposition.xyz);
	

	
  
	
	     //ポイントライト
  //  float3 PL = 0;
  //  PL = AddPointLight(P, N, E, Kd, Ks);
  //  color *= color * float4( PL, 1.0);

	//color.rgb *= Shadow_map.Sample(diffuseMapSamplerState, pin.texcoord).xyz;



    return color;
}

