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
    float3 Position : POSITION; //�ʒu
    float2 Size : TEXCOORD; //�傫��
    float4 Tex : TANGENT; //�^�C�v,��,��,��
    float4 Color : COLOR; //�F
};
struct PSInput
{
    float4 Position : SV_POSITION; //���_���W
    float2 Tex : TETCOORD; //�e�N�X�`�����W
    float4 Color : COLOR0;
};
//�萔�o�b�t�@
cbuffer CBPerFrame : register(b0)
{
    matrix View; //�r���[�ϊ��s��
    matrix Projection; //�������e�s��
    float2 TextureSize;//�e�N�X�`���T�C�Y
    float2 TextureNum; //��`�b�v������̑傫��
};
