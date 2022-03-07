#pragma once
#include "Lib_SpriteEffect.h"
#include "Lib_ResoureManager.h"
#include "Vector.h"
#include "Lib_ShaderResource.h"
#include <map>

using namespace std;
class Lib_EffectManager
{
private:
	unique_ptr<ShaderResource>    PointSpriteshader = nullptr;
public:
	Lib_EffectManager() {};
	~Lib_EffectManager() {};


	//����������
	void Init(const UINT MaxLoadNum,ID3D11Device* device);
	//���[�h(1:device,2:�e�N�X�`���̃p�X,3:�e�N�X�`���̃n���h��)
	void Load(ID3D11Device* device, const string name, int& handle, int Maxnum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state);
	//�폜
	void Erase(ID3D11Device* device, const  int handle);
	//�S����
	void Clear();
	//�X�V����
	void Update();
	//�A�j���[�V��������
	void Animation(float elapsedtimer, const  int handle,int Starttype, int Endtype, float Animetionspeed);
	void SetType(const int handle, int type);

	//�G�t�F�N�g�̕`��J�n����
	void Begin(ID3D11DeviceContext* device);
	//�`�揈��
	void Render(ID3D11DeviceContext* device, XMFLOAT4X4 view, XMFLOAT4X4 projection);
	//�G�t�F�N�g�̕`��J�n����
	void End(ID3D11DeviceContext* device);

	SpriteEffect* GetSpriteEffectResource(const int handle);
	vector<EffectData>* Geteffects(const int handle);

protected:

	//�G�t�F�N�g�̔z��
	vector<std::shared_ptr<SpriteEffect>> SpriteEffects;


	//���� �ǂݍ��񂾐�
	u_int LoadNum = 0;

	//���ɓǂݍ���ł��铯���e�N�X�`�������邩�ǂ����𒲂ׂ�
	//�������ɓǂݍ���ł��铯���e�N�X�`���ꍇhandle�ɒl������܂�
	bool DuplicateFind(const string name, int& handle);

	//textures�̋�ł���v�f�ɓo�^���Ă���
	void Register(ID3D11Device* device, const string name, int& handle, int Maxnum, VECTOR2 TextureChipSize, VECTOR2 TextureNum, Bland_state state);
	

};