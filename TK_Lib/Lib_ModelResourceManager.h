#pragma once
#include "Lib_ModelResource.h"
#include "Lib_ResoureManager.h"
#include <map>
class ModelResourceManager:public ResourceManager
{
public:
	ModelResourceManager() {};
	~ModelResourceManager() {};

	//����������
	void Init(const UINT MaxLoadNum);
	//���[�h(1:device,2:�e�N�X�`���̃p�X,3:�e�N�X�`���̃n���h��)
	bool Load(ID3D11Device* device, const string name, int& handle, const string key);
	//���f���̃R�s�[
	int Copy(int& handle);
	//�폜
	void Erase(ID3D11Device* device, const  int handle);
	//�S����
	void Clear();
	//���f�����\�[�X�̎擾
	ModelResource* GetModelResource(const int index);
	//���f���̔z��̎擾
	vector<std::shared_ptr<ModelResource>>& GetModel() { return models; };

	//���f���̍s��X�V����
	void Tranceform(ID3D11Device* device, XMFLOAT4X4 W, const int handle);
	//���f���̃A�j���[�V����
	void UPdateAnimetion(ID3D11Device* device, const int handle, const float elapsedTime);
	//���f���̃A�j���[�V�������Đ������ǂ���
	bool IsPlayAnimetion(const int handle);
	//���f���̃A�j���[�V�����Đ�
	void PlayAnimation(const int handle, int animationIndex, bool loop);
	//�L�[�̖��O����ԍ����擾����
	int GetModelFromSerchKey(const string& SearchName);
	//�A�j���[�V�����^�C����
	float GetEndAnimetionTime(int modelIndex);
	float GetAnimetionTime(int modelIndex);

	//�m�[�h��������
	ModelResource::NodeTest* FindNode(int modelIndex, const char* name);
private:
	//���f���ۑ��̔z��
	vector<std::shared_ptr<ModelResource>> models;

	////�Z�o�p�@���f���ԍ��ƌĂяo�����̃L�[
	map<string, int> ModelIndexResources;

	//���ɓǂݍ���ł��铯���e�N�X�`�������邩�ǂ����𒲂ׂ�
	//�������ɓǂݍ���ł��铯���e�N�X�`���ꍇhandle�ɒl������܂�
	bool DuplicateFind(const string name, int& handle);

	//textures�̋�ł���v�f�ɓo�^���Ă���
	bool Register(ID3D11Device* device, const string name, int& handle);
};
