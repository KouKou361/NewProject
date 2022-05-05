#pragma once
#include "SiroboPlayer.h"

//����������
void SiroboManager::Init()
{
	Clear();
	indexSirobo = 0;
}
//�X�V����
void SiroboManager::Update()
{
	for (int i=0;i<sirobos.size();i++)
	{
		Sirobo* sirobo = sirobos.at(i).get();
		if (sirobo)
		{
			sirobo->Update();
		}

	}
	//�j������
//�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����B
	for (shared_ptr<Sirobo> sirobo : remove)
	{
		//std::vector����v�f��j������ꍇ�̓C���e�[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<shared_ptr<Sirobo>>::iterator it = std::find(sirobos.begin(), sirobos.end(), sirobo);
		if (it != sirobos.end())
		{
			sirobos.erase(it);
		}
	}
	remove.clear();

}
//�`�揈��
void SiroboManager::Render()
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		if (sirobo)
		{
			sirobo->Render();

			//Imgui
			//sirobo->ImguiDebug();
		}
	}
}
//���f���`�揈��
void SiroboManager::ModelRender()
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		if (sirobo)
		{
			sirobo->ModelRender();
		}
	}
}
//�j������
void SiroboManager::Destroy(Sirobo* sirobo)
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		std::vector<shared_ptr<Sirobo>>::iterator it = std::find(sirobos.begin(), sirobos.end(), sirobo);
		if (it != sirobos.end())
		{
			shared_ptr<Sirobo> e = sirobo;
			remove.emplace_back(e);
		}
	}

}
void SiroboManager::AllBack()
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		if (sirobo)
		{
			if (sirobo->GetState() == Sirobo::StateType::TYPE_DEAD)continue;
			//�U���\�ȃ~�j�I���̎Z�o
			if (sirobo->GetState() != Sirobo::StateType::TYPE_STAND_BY)
			{
				sirobo->ResetNode();
			}
		}
	}
}
//�~�j�I���̍U��OK�s���̂ݍU������
void SiroboManager::OneAttack(Sirobo* sirobo)
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		if (sirobo)
		{
			//�U���\�ȃ~�j�I���̎Z�o
			if (sirobo->GetState() == Sirobo::StateType::TYPE_STAND_BY)
			{
				sirobo->SetAttackStandBy(true);
				sirobo->ResetNode();
					break;
			}
		}
	}
}
void SiroboManager::CollisionDebug()
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		if (sirobo)
		{
			sirobo->CollisionDebug();
		}
	}
}

//�S�폜
void SiroboManager::Clear()
{
	sirobos.clear();
	remove.clear();
}
//�o�^
void SiroboManager::Register(shared_ptr<Sirobo> sirobo)
{
	sirobo->SetIndex(indexSirobo);
	sirobo->SetManager(this);
	sirobos.emplace_back(sirobo);
	indexSirobo++;
}
