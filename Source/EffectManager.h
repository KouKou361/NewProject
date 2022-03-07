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
	VECTOR3 Pos;//�ʒu
	string name;//���O
	int playNum;//������
};

class EffectBase;

class EffectManager :public Manager
{
public:
	EffectManager() {};
	~EffectManager() {};

	//����������
	void Init();
	//�X�V����
	void Update();
	//�S�폜
	void Clear();
	//�X�e�[�W�̃��Z�b�g
	void StageReset();
	//���t���[���G�t�F�N�g�������f�[�^�o�^
	void UpdateEffectRegister(VECTOR3 Pos,string name,int num);
	//���t���[���G�t�F�N�g�������G�t�F�N�g�̍X�V����
	void PlayUpdateEffect();

	void NotRender();
	//�`�揈��
	virtual void Render() {};
	//���f���`�揈��
	virtual void ModelRender() {};
	//�o�^
	void Register(shared_ptr<EffectBase> effect,const string RegisterName);
	//�j������
	void Destroy(EffectBase* effect);
	//�G�t�F�N�g�̐��̎擾
	int GetEffectsSize() { return effects.size(); }
	//�G�t�F�N�g�̐��̎擾
	EffectBase* GetEffectsIndex(const int& index) { return effects.at(index).get(); }
	//�L�[�̖��O����G�t�F�N�g���擾����
	EffectBase* GetEffectFromSerchKey(const string& SearchName);

private:

	//����
	vector<UpdatePlayEffect> UpdatePlayEffectPoses;

	vector<shared_ptr<EffectBase>>effects;
	vector<shared_ptr<EffectBase>>remove;

	map<string, EffectBase*> EffectIndexResources;

};
