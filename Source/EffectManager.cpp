#pragma once
#include "EffectManager.h"
#include "EffectBase.h"
//����������
void EffectManager::Init()
{
	UpdatePlayEffectPoses.clear();
	TK_Lib::Lib_Effect::Init(10);
}
//���t���[���G�t�F�N�g�������f�[�^�o�^
void EffectManager::UpdateEffectRegister(VECTOR3 Pos, string name, int num)
{
	UpdatePlayEffect efc;

	efc.Pos = Pos;
	efc.name = name;
	efc.playNum = num;

	UpdatePlayEffectPoses.push_back(efc);
}
//���t���[���G�t�F�N�g�������G�t�F�N�g�̍X�V����
void EffectManager::PlayUpdateEffect()
{
	for (int i = 0; i < UpdatePlayEffectPoses.size(); i++)
	{
		UpdatePlayEffect UpdateEfc = UpdatePlayEffectPoses.at(i);
		EffectBase* efc= GetEffectFromSerchKey(UpdateEfc.name);
		efc->Play(UpdateEfc.Pos, UpdateEfc.playNum);
	}
}
//�X�V����
void EffectManager::Update()
{
	PlayUpdateEffect();

	for (shared_ptr<EffectBase> efc : effects)
	{
		if (efc)
		{
			efc->Update();
		}
	}
	//�j������
    //�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����B
	for (shared_ptr<EffectBase> efc : remove)
	{
		//std::vector����v�f��j������ꍇ�̓C���e�[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<shared_ptr<EffectBase>>::iterator it = std::find(effects.begin(), effects.end(), efc);
		if (it != effects.end())
		{
			effects.erase(it);
		}
	}
	remove.clear();

}
//�j������
void EffectManager::Destroy(EffectBase* Efc)
{
	for (shared_ptr<EffectBase> efc : effects)
	{
		std::vector<shared_ptr<EffectBase>>::iterator it = std::find(effects.begin(), effects.end(), efc);
		if (it->get() == Efc)
		{
			shared_ptr<EffectBase> e = efc;
			remove.emplace_back(e);
		}
	}
}
//�X�e�[�W�̃��Z�b�g
void EffectManager::NotRender()
{
	for (shared_ptr<EffectBase> efc : effects)
	{
		std::vector<shared_ptr<EffectBase>>::iterator it = std::find(effects.begin(), effects.end(), efc);
		{
			shared_ptr<EffectBase> e = efc;
			e->NotRender();
		}
	}
}

//�X�e�[�W�̃��Z�b�g
void EffectManager::StageReset()
{
	NotRender();
	//EffectIndexResources.clear();
	//effects.clear();
	remove.clear();
	UpdatePlayEffectPoses.clear();
}


//�S�폜
void EffectManager::Clear()
{
	for (int i = 0; i < GetEffectsSize(); i++)
	{
		GetEffectsIndex(i)->Delete();
	}
	EffectIndexResources.clear();
	effects.clear();
	remove.clear();
	UpdatePlayEffectPoses.clear();
	TK_Lib::Lib_Effect::Init(10);


}

EffectBase* EffectManager::GetEffectFromSerchKey(const string& SearchName)
{
	return EffectIndexResources.at(SearchName);
}
//�o�^
void EffectManager::Register(shared_ptr<EffectBase> efc, const string RegisterName)
{
	efc->Init();
	effects.emplace_back(efc);
	EffectIndexResources.insert(make_pair(RegisterName, efc.get()));
}