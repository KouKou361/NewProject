Texture2D diffuseMap : register(t0);
Texture2D Shadow_map : register(t1);
SamplerState diffuseMapSamplerState : register(s0);
SamplerState shadowmapSamplerState : register(s1);

struct VSInput
{
	float4 position    : POSITION;
	float3 normal      : NORMAL;
	float3 tangent     : TANGENT;
	float2 texcoord    : TEXCOORD;
	float4 color       : COLOR;
	float4 boneWeights : WEIGHTS;
	uint4  boneIndices : BONES;
};
struct PSInput
{
	float4 position : SV_POSITION;
    float3 Wposition : TEXCOORD2;
	float2 texcoord : TEXCOORD;
	float4 color    : COLOR;
	float3 vShadow:TEXCOORD4;
	float3 normal:NORMAL;
};

cbuffer CbScene : register(b0)
{
	row_major float4x4	viewProjection;
	float4				lightDirection;
};

#define MAX_BONES 128
cbuffer CbMesh : register(b1)
{
	row_major float4x4	boneTransforms[MAX_BONES];
};


//cbuffer CbSubset : register(b2)
//{
//	float4				materialColor;
//};
cbuffer CBPerFrame3 : register(b3)
{
	float4x4 LightViewProjection;
	float4	ShadowColor;
	float4  EyePos;
	float4 LightColor;

};
//static const float Bias = 0.0008f;
static const float Bias = 0.00001f;
//static const float Bias = 0.1;
//==============================
//�g�U���ˊ֐�
//==============================
float3 Diffuse(float3 N, float3 L, float3 C, float3 K)
{
	float D = dot(N, -L);
	D = max(0, D);
    D = D / 2 + 0.5f;
	return C * D * K;
}
//--------------------------------------------
//	���ʔ��ˊ֐�(�t�H��)
//--------------------------------------------
// N:�@��(���K���ς�)
// L:���˃x�N�g��(���K���ς�)
// C:���ˌ�(�F�E����)
// E:���_�����x�N�g��(���K���ς�)
// K:���˗�(0�`1.0)
// Power:�n�C���C�g�̋���(�P���x)

float3 PhongSpecular(float3 N, float3 L, float3 C, float3 E,
	float3 K, float Power)
{
	//���˃x�N�g��
	float3 R = normalize(reflect(-L, N));
	float3 S = dot(R, E);
	S = max(0, S);
	S = pow(S, Power);
	S = S * K * C;
	return S;
}

//--------------------------------------------
//	�n�[�t�����o�[�g
//--------------------------------------------
// N:�@��(���K���ς�)
// L:���˃x�N�g��(���K���ς�)
// C:���ˌ�(�F�E����)
// K:���˗�
float3 HalfLambert(float3 N, float3 L, float3 C, float3 K)
{
	float D = dot(N, -L);
	D = D * 0.5 + 0.5f;
	//D = D * D;	// ���������Ɍ�������
	return C * D * K;
}



//���[���h���W�����C�g��ԍ��W�ɕϊ�
float3 GetShadowTex(float4x4 vp, float3 wPos)
{
	// ���K���f�o�C�X���W�n
	float4 wvpPos;
	wvpPos.xyz = wPos;
	wvpPos.w = 1;
	wvpPos = mul(vp, wvpPos);
	wvpPos /= wvpPos.w;
	// �e�N�X�`�����W�n
	wvpPos.y = -wvpPos.y;
	wvpPos.xy = 0.5f * wvpPos.xy + 0.5f;
	return wvpPos.xyz;
}

//�V���h�[�}�b�v����V���h�[��ԍ��W�ɕϊ���Z�l��r
//float3 GetShadow(Texture2D st, SamplerState ss, float3 Tex, float3 Scolor,
//	float Bias)
//{ // �V���h�E�}�b�v����[�x�����o��
//	float d = st.Sample(ss, Tex.xy).r;
//	// �V���h�E�}�b�v�̐[�x�l�ƌ����̐[�x�̔�r
//	Scolor = (Tex.z - d > Bias) ? Scolor : float3(1, 1, 1);
//	return Scolor;
//}


//�V���h�[�}�b�v����V���h�[��ԍ��W�ɕϊ���Z�l��r
float3 GetShadow(Texture2D st, SamplerState ss, float3 Tex, float3 Scolor,
	float Bias)
{ // �V���h�E�}�b�v����[�x�����o��
	//float d = st.Sample(ss, Tex.xy).r;
	//// �V���h�E�}�b�v�̐[�x�l�ƌ����̐[�x�̔�r
	//Scolor = (Tex.z - d > Bias) ? Scolor : float3(1, 1, 1);
	//return Scolor;
	float2 d = st.Sample(ss, Tex.xy).rg;
	float R = d.x * d.x;
	//E(x2)
	float G = d.y;


	//���U�̌v�Z
	float variance = max(Bias, G - R);
	//�m����̍ő�l�̎Z�o
	float a = variance + (Tex.z - d.x) * (Tex.z - d.x);
	float p_max = saturate(variance / a);
	//�e�̐F
	Scolor = lerp(Scolor, 1.0f, p_max);
	// p_max *= float3(0.1f, 0.1f, 0.1f);
    return max(Scolor, p_max);
}


