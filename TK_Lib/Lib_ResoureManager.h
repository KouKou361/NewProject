#pragma once

#include <d3d11.h>
#include <memory>
#include <vector>
#include <string>

using namespace std;

//���f����e�N�X�`���Ȃǂ̊Ǘ��N���X����鎞�̊��N���X
class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	//����������
	virtual void Init(const UINT MaxLoadNum)=0;
	//���[�h(1:device,2:�p�X,3:�n���h��)
	virtual bool Load(ID3D11Device* device, const string name, int& handle, const string RegisterKey="") = 0;
	//�폜
	virtual void Erase(ID3D11Device* device, const  int handle) = 0;
	//�S����
	virtual void Clear() = 0;

protected:
	//���� �ǂݍ��񂾐�
	u_int LoadNum = 0;

	//���ɓǂݍ���ł��铯���e�N�X�`�������邩�ǂ����𒲂ׂ�
	//�������ɓǂݍ���ł��铯���e�N�X�`���ꍇhandle�ɒl������܂�
	virtual bool DuplicateFind(const string name, int& handle) = 0;

	//textures�̋�ł���v�f�ɓo�^���Ă���
	virtual bool Register(ID3D11Device* device, const string name, int& handle) = 0;

};
