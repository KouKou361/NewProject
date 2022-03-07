
//�|�C���g���C�g�̍\����
struct POINTLIGHT {
	float index;
	float range;//���̓͂��͈�
	float type; //�L����������
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
//�g�U���ˊ֐�
//==============================
float3 mmDiffuse(float3 N, float3 L, float3 C, float3 K)
{
    float D = dot(N, -L);
    D = max(0, D);
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

float3 mmPhongSpecular(float3 N, float3 L, float3 C, float3 E,
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

// P: �s�N�Z�����[���h�ʒu
// N: ���[���h�@��(���K���ς�)
// E: ���������x�N�g��(���K���ς�)
// Kd: �g�U���˗�
// Ks: ���ʔ��˗�
float3 AddPointLight(float3 P, float3 N, float3 E, float3 Kd, float3 Ks)
{
	float3 PL; //�|�C���g���C�g�x�N�g��
	float3 PC; //�|�C���g���C�g�F
	float influence; //�|�C���g���C�g�̉e��
	float3 PD = (float3)0; //�g�U����
	float3 PS = (float3)0; //���ʔ���
	for (int i = 0; i < POINTMAX; i++) {
		//�_�����Ă��Ȃ����C�g���O
		if (PointLight[i].index <= -1) continue;
		PL = P - PointLight[i].pos.xyz;
		float d = length(PL);
		float r = PointLight[i].range;
		//�͂��Ȃ����C�g���O
		if (d > r) continue;
		influence = saturate(1.0f - d / r);
		PL = normalize(PL);
		PC = PointLight[i].color.rgb;
        PD += PC * influence;
        //PD = (1, 0, 0);
		//�g�U���̉��Z
		//PD += mmDiffuse(N, PL, PC, Kd) * influence;
		//////���ʌ��̉��Z
        //PS += mmPhongSpecular(N, PL, PC, E, Ks, 20) * influence;
    }
	return (PD + PS);
}
