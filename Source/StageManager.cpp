#pragma once
#include "StageManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "ObjectFunctionManager.h"
#include "ObjectManager.h"
#include "Collision.h"
#include "Scene.h"

//����������
void StageManager::Init()
{
	nowStage = nullptr;
	Clear();


}
//�X�V����
void StageManager::Update()
{
	
	if (TK_Lib::Lib_Fade::GetFadeVolume() >= 1.0f)
	{
		TK_Lib::Lib_Fade::FadeOutBegin(0.02f);
	}
	nowStage->Update();
}
//�`�揈��
void StageManager::Render()
{
	nowStage->Render();
}
//���f���`�揈��
void StageManager::ModelRender()
{
	nowStage->ModelRender();
}
//�S�폜
void StageManager::Clear()
{
	stages.clear();
}


void StageManager::GoNextStage()
{
	//���݂̃X�e�[�W
	int StageIndex = -1;

	for (int i = 0; i < stages.size(); i++)
	{
		Stage* stage = stages.at(i).get();
		if (stage == nowStage)
		{
			StageIndex = i;
			StageIndex++;
			break;
		}
	}

	//�S�ẴQ�[�����N���A�����̂�Clear�V�[����
	if (StageIndex >= stages.size())
	{
		sceneGame->SetGameClear(true);
		return;
	}

	if (StageIndex>=stages.size())
	{
		assert(!L"���݂��Ȃ��X�e�[�W��G�낤�Ƃ��܂����B");
	}

	if (StageIndex==-1)
	{
		assert(!L"���݂��Ȃ��X�e�[�W��G�낤�Ƃ��܂����B");
	}
	

	ChangeStage(StageIndex);

}
void StageManager::ChangeStage(int StageIndex)
{
	//���ׂẴX�e�[�W�f�[�^�����Z�b�g����B
	sceneGame->GetObjectFunctionManager()->Clear();
	sceneGame->GetEnemyManager()->Clear();
	sceneGame->GetEffectManager()->StageReset();
	sceneGame->GetObjectManager()->Clear();
	TK_Lib::SpotLight::Clear();
	Collision::Instance().Clear();
	
	if (nowStage != nullptr)
	{
		nowStage->End();
	}
	//�v���C���[�̃��Z�b�g
	sceneGame->GetPlayer()->ResetPlayer();

	//�V�[���̐؂�ւ�
	nowStage = stages.at(StageIndex).get();
	nowStage->Init();
	
}
//�o�^
int StageManager::Register(shared_ptr<Stage> stage)
{
	int size = static_cast<int>(stages.size());
	stages.emplace_back(stage);
	//���̔ԍ���Ԃ�
	return size;
}
