#pragma once
//#include "EffectBase.h"
#include "Manager.h"
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "Lib.h"
using namespace std;

//���t���[���G�t�F�N�g�������f�[�^
class UpdatePlayEffect
{
public:
	VECTOR3 pos;//�ʒu
	string name;//���O
	int playNum;//������
};

class EffectBase;

//�G�t�F�N�g�Ǘ��N���X
class EffectManager :public Manager
{
public:
	EffectManager() {};
	~EffectManager() {};

	//����������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	virtual void Render() {};
	//���f���`�揈��
	virtual void ModelRender() {};

	//�S�폜
	void Clear();
	//�X�e�[�W�̃��Z�b�g
	void StageReset();
	//���t���[���G�t�F�N�g�������f�[�^�o�^
	void UpdateEffectRegister(const VECTOR3 &pos, const string &name, const int &num);
	//���t���[���G�t�F�N�g�������G�t�F�N�g�̍X�V����
	void PlayUpdateEffect();
	//�S�Ĕ�\��
	void NotRender();

	//�o�^
	void Register(const shared_ptr<EffectBase>& effect,const string &registerName);
	//�j������
	void Destroy(const EffectBase* effect);
	//�G�t�F�N�g�̐��̎擾
	int GetEffectsSize() { return static_cast<int>(effects.size()); }
	//�G�t�F�N�g�̐��̎擾
	EffectBase* GetEffectsIndex(const int& index) { return effects.at(index).get(); }
	//�L�[�̖��O����G�t�F�N�g���擾����
	EffectBase* GetEffectFromSerchKey(const string& searchName);

private:

	//���t���[���o���G�t�F�N�g�i���G�t�F�N�g�Ȃǁj
	vector<UpdatePlayEffect> updatePlayEffectPoses;
	//�G�t�F�N�g
	vector<shared_ptr<EffectBase>>effects;
	//�폜�G�t�F�N�g
	vector<shared_ptr<EffectBase>>remove;
	//�L�[�̖��O����G�t�F�N�g���擾����p
	map<string, EffectBase*> effectIndexResources;

};
