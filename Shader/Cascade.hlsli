Texture2D diffuseMap : register(t0);
Texture2D ShadowTexture0 : register(t1);
Texture2D ShadowTexture1 : register(t2);
Texture2D ShadowTexture2 : register(t3);
Texture2D NormalTexture : register(t4);
SamplerState diffuseMapSamplerState : register(s0);
SamplerState shadowmapSamplerState : register(s1);

struct VSInput
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float2 texcoord : TEXCOORD;
    float4 color : COLOR;
    float4 boneWeights : WEIGHTS;
    uint4 boneIndices : BONES;
};
struct PSInput
{
    float4 position : SV_POSITION;
    float3 Wposition : TEXCOORD2;
    float2 texcoord : TEXCOORD;
    float4 color : COLOR;
   // float3 vShadow : TEXCOORD4;
    float3 normal : NORMAL;
    
    float3 VX : TEXCOORD5; //�ڋ�ԗpX��
    float3 VY : TEXCOORD6; //�ڋ�ԗpY��
    float3 VZ : TEXCOORD7; //�ڋ�ԗpZ��
};

cbuffer CbScene : register(b0)
{
    row_major float4x4 viewProjection;
    float4 lightDirection;
};

#define MAX_BONES 128
cbuffer CbMesh : register(b1)
{
    row_major float4x4 boneTransforms[MAX_BONES];
};


cbuffer CbSubset : register(b2)
{
    float4 materialColor;
};

cbuffer CBPerFrame3 : register(b3)
{
    float4x4 LightViewProjection[3];
    float4 ShadowColor;
    float4 EyePos;
    float4 LightColor;

};
static const float Bias[3] = { 0.0009f, 0.001f, 0.002f };
//static const float Bias = 0.00001f;
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
    
    //float3 R = reflect(L, N);
    //float power = max(dot(-E, R), 0);
    //power = pow(power, 128);
    //return C * power * K;
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



//���C�g���
float3 GetShadowTex(float4x4 vp, float3 wPos)
{
    //���K���f�o�C�X
    float4 wvpPos;
    wvpPos.xyz = wPos;
    wvpPos.w = 1.0f;
    
    wvpPos = mul(vp, wvpPos);
    wvpPos /= wvpPos.w;
    //�e�N�X�`��
    wvpPos.y = -wvpPos.y;
    wvpPos.xy = 0.5f * wvpPos.xy + 0.5f;
    return wvpPos.xyz;

}

//���C�g���
float3 GetShadow(Texture2D st, SamplerState ss, float3 Tex, float3 Scolor, float Bias)
{
    //�����œ�̌x���I
    //�����𔺂����[�v�Ŏg�p����鎖�Ōx������Ă���炵���B
    //for�����g��Ȃ��悤�ɂ����玡�肻�������A
    //�\�[�X�R�[�h���Y�킳��ۂׂɍ���͂��̌x���𓦂��Ă����B
    
    //�V���h�E�}�b�v
    float d = st.Sample(ss, Tex.xy).r;
    //�V���h�E�}�b�v�}�b�v�̐[�x
    Scolor = (Tex.z - d > Bias) ? Scolor : float3(1, 1, 1);
    
    float2 da = st.Sample(ss, Tex.xy).rg;
    float R = da.x * da.x;
	//E(x2)
    float G = da.y;


	//���U�̌v�Z
    float variance = max(Bias, G - R);
	//�m����̍ő�l�̎Z�o
    float a = variance + (Tex.z - da.x) * (Tex.z - da.x);
    float p_max = saturate(variance / a);
	//�e�̐F
    Scolor = lerp(Scolor, 1.0f, 0.2f);
   
    return Scolor;
    //return max(Scolor, p_max);

}

float3 GetCascadeShadow(float3 P)
{
    //�V���h�E�}�b�v
    Texture2D shadowTexure[3] = { ShadowTexture0, ShadowTexture1, ShadowTexture2 };

    float3 color = { 1,1,1 };

    for (int j = 0; j < 3; ++j)
    {
        
        float3 vShadow = GetShadowTex(LightViewProjection[j], P);
        float3 ShadowTexcoord = vShadow;

        if (ShadowTexcoord.z >= 0 && ShadowTexcoord.z <= 1 &&
            ShadowTexcoord.x >= 0 && ShadowTexcoord.x <= 1 &&
            ShadowTexcoord.y >= 0 && ShadowTexcoord.y <= 1)
        {

            //switch���ł����肱����̕����\�[�X�R�[�h���Y��ɂȂ邪�A
            //�Ȃ����x�����o�Ă��܂��B�iTexture2DArray���g���΍s�����������j
            //�����switch���ɂ���B
            // 
            //color = GetShadow(shadowTexure[j], shadowmapSamplerState, vShadow, ShadowColor.xyz, Bias[j]);

            switch (j)
            {
            case 0:        color= GetShadow(shadowTexure[0], shadowmapSamplerState, vShadow, ShadowColor.xyz, Bias[0]);
                break;
            case 1:        color = GetShadow(shadowTexure[1], shadowmapSamplerState, vShadow, ShadowColor.xyz, Bias[1]);
                break;
            case 2:        color = GetShadow(shadowTexure[2], shadowmapSamplerState, vShadow, ShadowColor.xyz, Bias[2]);
                break;
            }
            break;
    
        }
    }
    return color;

}