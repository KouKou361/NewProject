#pragma once
#include "MinionPlayer.h"

//����������
void MinionManager::Init()
{
	Clear();
	IndexMinion = 0;
}
//�X�V����
void MinionManager::Update()
{
	for (int i=0;i<minions.size();i++)
	{
		MinionPlayer* minion = minions.at(i).get();
		if (minion)
		{
			minion->Update();
		}

	}
	//�j������
//�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����B
	for (shared_ptr<MinionPlayer> minion : remove)
	{
		//std::vector����v�f��j������ꍇ�̓C���e�[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<shared_ptr<MinionPlayer>>::iterator it = std::find(minions.begin(), minions.end(), minion);
		if (it != minions.end())
		{
			minions.erase(it);
		}
	}
	remove.clear();

}
//�`�揈��
void MinionManager::Render()
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		if (minion)
		{
			minion->Render();

			//Imgui
			//minion->ImguiDebug();
		}
	}
}
//���f���`�揈��
void MinionManager::ModelRender()
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		if (minion)
		{
			minion->ModelRender();
		}
	}
}
//�j������
void MinionManager::Destroy(MinionPlayer* minion)
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		std::vector<shared_ptr<MinionPlayer>>::iterator it = std::find(minions.begin(), minions.end(), minion);
		if (it != minions.end())
		{
			shared_ptr<MinionPlayer> e = minion;
			remove.emplace_back(e);
		}
	}

}
void MinionManager::AllBack()
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		if (minion)
		{
			if (minion->GetState() == MinionPlayer::StateType::TYPE_DEAD)continue;
			//�U���\�ȃ~�j�I���̎Z�o
			if (minion->GetState() != MinionPlayer::StateType::TYPE_STAND_BY)
			{
				minion->ResetNode();
			}
		}
	}
}
//�~�j�I���̍U��OK�s���̂ݍU������
void MinionManager::OneAttack(MinionPlayer* minion)
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		if (minion)
		{
			//�U���\�ȃ~�j�I���̎Z�o
			if (minion->GetState() == MinionPlayer::StateType::TYPE_STAND_BY)
			{
				minion->SetAttackStandBy(true);
				minion->ResetNode();
					break;
			}
		}
	}
}
void MinionManager::CollisionDebug()
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		if (minion)
		{
			minion->CollisionDebug();
		}
	}
}

//�S�폜
void MinionManager::Clear()
{
	minions.clear();
	remove.clear();
}
//�o�^
void MinionManager::Register(shared_ptr<MinionPlayer> minion)
{
	minion->SetIndex(IndexMinion);
	minion->SetManager(this);
	minions.emplace_back(minion);
	IndexMinion++;
}
