#pragma once

#include "Lib_Texture.h"
#include "Lib_DirectXFunctions.h"
#include "Lib_Blender.h"

#include <vector>
#include <d3d11.h>
#include <memory>


using namespace std;

struct VERTEXParticle;

class EffectData
{
public:
	float x, y, z;//���W
	float w, h;//�傫��
	float aw, ah;
	float vx, vy, vz;
	float ax, ay, az;
	float alpha;//�A���t�@
	float timer;//��������
	float anime_timer;//�A�j���[�V�����̐؂�ւ�鎞��
	int type;//�^�C�v(-1�ō폜)
	VECTOR4 color = { 1,1,1,1 };
	bool renderflg = false;
	void Set(int type, float timer,
		DirectX::XMFLOAT3 p, DirectX::XMFLOAT3 v, DirectX::XMFLOAT3 f, DirectX::XMFLOAT2 size, VECTOR4 color = {1,1,1,1});
	bool IsCameraRender();
};

class SpriteEffect
{
public:
	SpriteEffect() {};
	SpriteEffect(ID3D11Device* device, int Num,std::string name);
	~SpriteEffect() {};
public:
	int handle = -1;
	int UseLastEffectIndex = -1;
	Bland_state BlenderType = Bland_state::BS_ALPHA;
	
private:
	unique_ptr<TextureResource> Texture = nullptr;
	
	vector<EffectData> spriteEffects;
	vector<VERTEXParticle> vertices;
	// ���_�f�[�^
	ComPtr<ID3D11Buffer> m_vertexBuffer = nullptr;
	// �萔�o�b�t�@
	ComPtr<ID3D11Buffer> m_constantBuffer = nullptr;


	//�萔�o�b�t�@�\���̒�`(�p�[�e�B�N��)
	struct ConstantBufferForPerFrame
	{
		XMFLOAT4X4 view;//�r���[�ϊ��p�s��
		XMFLOAT4X4 projection;//�����ϊ��p�s��
		XMFLOAT2 TextureSize;//��`�b�v������̑傫��(UV���W)
		XMFLOAT2 TextureNum;//�e�N�X�`���̃`�b�v�̐�(X,Y);
	};

	ConstantBufferForPerFrame cb =
	{
		XMFLOAT4X4{0,0,0,0,   0,0,0,0, 0,0,0,0, 0,0,0,0},
		XMFLOAT4X4{0,0,0,0,   0,0,0,0, 0,0,0,0, 0,0,0,0},
		XMFLOAT2{0,0},
		XMFLOAT2{0,0}
	};

private:
	void SetNum(int MaxNum);
public:
	void Create(ID3D11Device* device, int Num, std::string name, VECTOR2 TextureChipSize, VECTOR2 TextureNum);
	void SetConstant(VECTOR2 TextureChipSize, VECTOR2 TextureNum);
	void Fire(DirectX::XMFLOAT3 pos, int max);
	void Fire2(DirectX::XMFLOAT3 pos, int max);
	
	//void Update(float timer);
	void Animation(float elapsedtimer, int Starttype,int Endtype,float Animetionspeed);
	void Set(ID3D11DeviceContext* context);
	void UpdateConstantBuffer(ID3D11DeviceContext* context, XMFLOAT4X4 view, XMFLOAT4X4 projection);
	void Render(ID3D11DeviceContext* context);
	//���ݎg�p���Ă���G�t�F�N�g�̍Ō�̔ԍ�
	void  SetUseLastEffectIndex();
	inline int GetUseLastEffectIndex() { return UseLastEffectIndex; };
	inline vector<EffectData>* Geteffects() { return &spriteEffects; };
	inline const string GetTextureName() { return Texture->GetFilename(); };
};

