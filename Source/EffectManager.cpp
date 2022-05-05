#pragma once
#include "EffectManager.h"
#include "EffectBase.h"
//����������
void EffectManager::Init()
{
	updatePlayEffectPoses.clear();
	TK_Lib::Lib_Effect::Init(10);//�G�t�F�N�g�̐ݒ�
}

//���t���[���G�t�F�N�g�������f�[�^�o�^
void EffectManager::UpdateEffectRegister(const VECTOR3& pos, const string &name,const int& num)
{
	UpdatePlayEffect efc;

	efc.pos = pos;
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

		if (TK_Lib::Camera::IsCamera(UpdateEfc.pos))
		{
			efc->Play(UpdateEfc.pos, UpdateEfc.playNum);
		}

		

	}
}
//�X�V����
void EffectManager::Update()
{
	//���t���[���G�t�F�N�g�������G�t�F�N�g�̍X�V����
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
void EffectManager::Destroy(const EffectBase* efc)
{
	for (shared_ptr<EffectBase> m_efc : effects)
	{
		std::vector<shared_ptr<EffectBase>>::iterator it = std::find(effects.begin(), effects.end(), m_efc);
		if (it->get() == efc)
		{
			shared_ptr<EffectBase> e = m_efc;
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
	NotRender();//�S�Ĕ�\���ɂ���
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
//�o�^�������O����G�t�F�N�g�擾
EffectBase* EffectManager::GetEffectFromSerchKey(const string& searchName)
{
	return effectIndexResources.at(searchName);
}
//�G�t�F�N�g�o�^
void EffectManager::Register(const shared_ptr<EffectBase>& efc, const string& registerName)
{
	efc->Init();
	effects.emplace_back(efc);
	effectIndexResources.insert(make_pair(registerName, efc.get()));
}