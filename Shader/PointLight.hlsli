
//ポイントライトの構造体
struct POINTLIGHT {
	float index;
	float range;//光の届く範囲
	float type; //有効か無効か
	float dummy;
	float4 pos;
	float4 color;
};
static const int POINTMAX = 8;
cbuffer CBPerFrame:register(b4)
{
	POINTLIGHT PointLight[POINTMAX];
}

//==============================
//拡散反射関数
//==============================
float3 mmDiffuse(float3 N, float3 L, float3 C, float3 K)
{
    float D = dot(N, -L);
    D = max(0, D);
    return C * D * K;
}
//--------------------------------------------
//	鏡面反射関数(フォン)
//--------------------------------------------
// N:法線(正規化済み)
// L:入射ベクトル(正規化済み)
// C:入射光(色・強さ)
// E:視点方向ベクトル(正規化済み)
// K:反射率(0～1.0)
// Power:ハイライトの強さ(輝き度)

float3 mmPhongSpecular(float3 N, float3 L, float3 C, float3 E,
	float3 K, float Power)
{
	//反射ベクトル
    float3 R = normalize(reflect(-L, N));
    float3 S = dot(R, E);
    S = max(0, S);
    S = pow(S, Power);
    S = S * K * C;
    return S;
}

// P: ピクセルワールド位置
// N: ワールド法線(正規化済み)
// E: 視線方向ベクトル(正規化済み)
// Kd: 拡散反射率
// Ks: 鏡面反射率
float3 AddPointLight(float3 P, float3 N, float3 E, float3 Kd, float3 Ks)
{
	float3 PL; //ポイントライトベクトル
	float3 PC; //ポイントライト色
	float influence; //ポイントライトの影響
	float3 PD = (float3)0; //拡散反射
	float3 PS = (float3)0; //鏡面反射
	for (int i = 0; i < POINTMAX; i++) {
		//点灯していないライト除外
		if (PointLight[i].index <= -1) continue;
		PL = P - PointLight[i].pos.xyz;
		float d = length(PL);
		float r = PointLight[i].range;
		//届かないライト除外
		if (d > r) continue;
		influence = saturate(1.0f - d / r);
		PL = normalize(PL);
		PC = PointLight[i].color.rgb;
        PD += PC * influence;
        //PD = (1, 0, 0);
		//拡散光の加算
		//PD += mmDiffuse(N, PL, PC, Kd) * influence;
		//////鏡面光の加算
        //PS += mmPhongSpecular(N, PL, PC, E, Ks, 20) * influence;
    }
	return (PD + PS);
}
