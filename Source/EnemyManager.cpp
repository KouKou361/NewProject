#pragma once
#include "EnemyManager.h"
#include "Collision.h"
#include "MinionPlayer.h"
#include "Player.h"
#include "CameraController.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"
#include "EXPManager.h"
#include "EXP.h"

//����������
void EnemyManager::Init()
{
	Target = scene->GetPlayer();
}
//�X�V����
void EnemyManager::Update()
{
	for (shared_ptr<EnemyBase> enm: enemies)
	{
		if (enm)
		{
			enm->Update();

			ImGui::Begin("Attack");
			ImGui::Text("AttackMinion=%d", enm->AttackMinions.size());
			ImGui::End();
		}
	
	}
	//�j������
//�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����B
	for (shared_ptr<EnemyBase> enm : remove)
	{
		//std::vector����v�f��j������ꍇ�̓C���e�[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<shared_ptr<EnemyBase>>::iterator it = std::find(enemies.begin(), enemies.end(), enm);
		if (it != enemies.end())
		{
			enemies.erase(it);
		}
	}
	remove.clear();

}
//�`�揈��
void EnemyManager::Render()
{
	for (shared_ptr<EnemyBase> enm : enemies)
	{
		if (enm)
		{
			enm->Render();

			//Imgui
			//enm->ImguiDebug();
		}
	}
}
//���f���`�揈��
void EnemyManager::ModelRender()
{
	for (shared_ptr<EnemyBase> enm : enemies)
	{
		if (enm)
		{
			enm->ModelRender();
		}
	}
}
//�j������
void EnemyManager::Destroy(EnemyBase* Enm)
{
	for (shared_ptr<EnemyBase> enm : enemies)
	{
		std::vector<shared_ptr<EnemyBase>>::iterator it = std::find(enemies.begin(), enemies.end(), enm);
		if (it->get() == Enm)
		{
			shared_ptr<EnemyBase> e = enm;
			remove.emplace_back(e);
		}
	}

	TK_Lib::Lib_Sound::SoundPlay("SummonEXP", false);
	for(int i=0;i<5;i++)
	{
		shared_ptr<EXP> m_exp = make_shared<EXP>();
		scene->GetExpManager()->Register(m_exp,Enm->GetPos());
	}

	scene->GetEffectManager()->GetEffectFromSerchKey("Destroy")->Play(Enm->GetPos(),20);

	//�폜����̂ŖڕW�ɂ��Ă����L�����N�^�[������
	//�ڕW���Z�b�g
	ResetTheTargetCharacter(Enm);

}
bool EnemyManager::CollisionEnemy(const VECTOR3 pos,const float weight,const float collisionRadius,VECTOR3& OutPos,EnemyBase*& SaveEnm)
{
	VECTOR3 OutPosB;
	bool hitFlg = false;

	for (int i = 0; i <GetEnemiesSize(); i++)
	{
		EnemyBase* enm = GetEnemiesIndex(i);
		if (Collision::Instance().SphereVsSphere(pos, weight, collisionRadius, enm->GetPos(), enm->GetWeight(), enm->GetCollisionRadius(), OutPos, OutPosB))
		{
			//enm->SetPos(OutPosB);
			//pos = OutPosB;
			hitFlg= true;
			SaveEnm = enm;
		}

	}
	return hitFlg;

}
void EnemyManager::CollisionDebug()
{
	for (shared_ptr<EnemyBase> enm : enemies)
	{
		if (enm)
		{
			enm->CollisionDebug();
		}
	}
}

//�S�폜
void EnemyManager::Clear()
{
	for (int i = 0; i < GetEnemiesSize(); i++)
	{
		EnemyBase* enm = GetEnemiesIndex(i);
		ResetTheTargetCharacter(enm);
	}

	enemies.clear();
	remove.clear();
}
//�G�̍s�������邩�ǂ���
void EnemyManager::SetEnemyActive(bool flg)
{
	for (int i = 0; i < GetEnemiesSize(); i++)
	{
		EnemyBase* enm = GetEnemiesIndex(i);
		enm->SetActionFlg(flg);
	}
}
//�o�^
void EnemyManager::Register(shared_ptr<EnemyBase> enm)
{
	enm->Init();
	enm->SetTarget(Target);
	enemies.emplace_back(enm);
}
void EnemyManager::ResetTheTargetCharacter(EnemyBase* enm)
{
	MinionManager* minionManager = scene->GetPlayer()->GetMinionManager();
	//�~�j�I���̖ڕW���Z�b�g
	for (int i = 0; i < minionManager->GetMinionsSize(); i++)
	{
		//�~�j�I���̎擾
		MinionPlayer* minion= minionManager->GetMinionIndex(i);
		//�����~�j�I���̖ڕW���w�肳�ꂽ�G(����)�Ȃ��
		if (minion->GetTarget() == enm)
		{
			//�ڕW�̃��Z�b�g
			minion->SetTarget(nullptr);
		}
	}

	//�v���C���[�̖ڕW�̃��Z�b�g
	if (scene->GetPlayer()->GetTarget() == enm)
	{//�ڕW�̃��Z�b�g
		scene->GetPlayer()->SetTarget(nullptr);
	}

	//�J�����̃��Z�b�g
	if (scene->GetCameraManager()->GetTargetChractor() == enm)
	{//�ڕW�̃��Z�b�g
		scene->GetCameraManager()->ChangeCamera(new CameraNormal(scene->GetPlayer()));
	}
}
//�^�O���猟�����Ă����A�ŏ��Ɍ����ɓ�������Enemy��Ԃ�
EnemyBase* EnemyManager::SearchEnemyTag(const EnemyTag searchTag)
{
	for (int i = 0; i < GetEnemiesSize(); i++)
	{
		EnemyBase* enm = GetEnemiesIndex(i);
		if (enm->GetEnemyTag() == searchTag)
		{
			return enm;
		}
	}
	return nullptr;
}