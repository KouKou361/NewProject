Texture2D DiffuseTexture : register(t0);
SamplerState DecalSampler : register(s0);

struct VSInput
{
    float3 Position : POSITION;
    float2 Size : TEXCOORD;
    float4 Tex : TANGENT;
    float4 Color : COLOR;
};
struct GSInput
{
    float3 Position : POSITION; //位置
    float2 Size : TEXCOORD; //大きさ
    float4 Tex : TANGENT; //タイプ,空,空,空
    float4 Color : COLOR; //色
};
struct PSInput
{
    float4 Position : SV_POSITION; //頂点座標
    float2 Tex : TETCOORD; //テクスチャ座標
    float4 Color : COLOR0;
};
//定数バッファ
cbuffer CBPerFrame : register(b0)
{
    matrix View; //ビュー変換行列
    matrix Projection; //透視投影行列
    float2 TextureSize;//テクスチャサイズ
    float2 TextureNum; //一チップ当たりの大きさ
};
