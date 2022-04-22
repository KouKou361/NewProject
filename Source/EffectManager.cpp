#pragma once
#include "EffectManager.h"
#include "EffectBase.h"
//����������
void EffectManager::Init()
{
	updatePlayEffectPoses.clear();
	TK_Lib::Lib_Effect::Init(10);
}
//���t���[���G�t�F�N�g�������f�[�^�o�^
void EffectManager::UpdateEffectRegister(VECTOR3 Pos, string name, int num)
{
	UpdatePlayEffect efc;

	efc.pos = Pos;
	efc.name = name;
	efc.playNum = num;

	updatePlayEffectPoses.push_back(efc);
}
//���t���[���G�t�F�N�g�������G�t�F�N�g�̍X�V����
void EffectManager::PlayUpdateEffect()
{
	for (int i = 0; i < updatePlayEffectPoses.size(); i++)
	{
		UpdatePlayEffect UpdateEfc = updatePlayEffectPoses.at(i);
		EffectBase* efc= GetEffectFromSerchKey(UpdateEfc.name);
		efc->Play(UpdateEfc.pos, UpdateEfc.playNum);
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
			e->NotRender();//��\���ɂ���
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
	updatePlayEffectPoses.clear();
}


//�S�폜
void EffectManager::Clear()
{
	for (int i = 0; i < GetEffectsSize(); i++)
	{
		GetEffectsIndex(i)->Delete();
	}
	effectIndexResources.clear();
	effects.clear();
	remove.clear();
	updatePlayEffectPoses.clear();
	TK_Lib::Lib_Effect::Init(10);


}

EffectBase* EffectManager::GetEffectFromSerchKey(const string& SearchName)
{
	return effectIndexResources.at(SearchName);
}
//�o�^
void EffectManager::Register(shared_ptr<EffectBase> efc, const string RegisterName)
{
	efc->Init();
	effects.emplace_back(efc);
	effectIndexResources.insert(make_pair(RegisterName, efc.get()));
}