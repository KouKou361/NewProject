#pragma once
#include "EnemyManager.h"
#include "Collision.h"
#include "SiroboPlayer.h"
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
	target = scene->GetPlayer();
}
//�X�V����
void EnemyManager::Update()
{
	for (shared_ptr<EnemyBase> enm: enemies)
	{
		if (enm)
		{
			//�X�V����
			enm->Update();
		}
	
	}
	//�j������
//�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����B
	for (shared_ptr<EnemyBase> enm : remove)
	{
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
void EnemyManager::Destroy(EnemyBase* enm)
{
	//�j�����X�g�ɒǉ�
	for (shared_ptr<EnemyBase> Enm : enemies)
	{
		std::vector<shared_ptr<EnemyBase>>::iterator it = std::find(enemies.begin(), enemies.end(), Enm);
		if (it->get() == enm)
		{
			shared_ptr<EnemyBase> e = Enm;
			remove.emplace_back(e);
		}
	}

	//�o���l�̂���
	SummonEXP(enm);

	//�j��G�t�F�N�g
	SummonDestoryEffect(enm);
	
	//�폜����̂ŖڕW�ɂ��Ă����L�����N�^�[�����̖ڕW�����Z�b�g
	ResetTheTargetCharacter(enm);

}
bool EnemyManager::CollisionEnemy(const VECTOR3& pos,const float& weight,const float& collisionRadius,VECTOR3& outPos,EnemyBase*& saveEnm)
{
	VECTOR3 OutPosB;
	bool hitFlg = false;

	for (int i = 0; i <GetEnemiesSize(); i++)
	{
		EnemyBase* enm = GetEnemiesIndex(i);
		if (Collision::Instance().SphereVsSphere(pos, weight, collisionRadius, enm->GetPos(), enm->GetWeight(), enm->GetCollisionRadius(), outPos, OutPosB))
		{
			//enm->SetPos(OutPosB);
			//pos = OutPosB;
			hitFlg= true;
			saveEnm = enm;
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
void EnemyManager::Register(const shared_ptr<EnemyBase>& enm)
{
	enm->Init();
	enm->SetTarget(target);
	enemies.emplace_back(enm);
}
void EnemyManager::ResetTheTargetCharacter(const EnemyBase* enm)
{
	SiroboManager* siroboManager = scene->GetPlayer()->GetSiroboManager();
	//�~�j�I���̖ڕW���Z�b�g
	for (int i = 0; i < siroboManager->GetSiroboSize(); i++)
	{
		//�~�j�I���̎擾
		Sirobo* sirobo= siroboManager->GetSiroboIndex(i);
		//�����~�j�I���̖ڕW���w�肳�ꂽ�G(����)�Ȃ��
		if (sirobo->GetTarget() == enm)
		{
			//�ڕW�̃��Z�b�g
			sirobo->SetTarget(nullptr);
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
EnemyBase* EnemyManager::SearchEnemyTag(const EnemyTag& searchTag)
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
//�o���l�̂���
void EnemyManager::SummonEXP(EnemyBase* enm)
{
	//�T�E���h�i�s�����j
	TK_Lib::Lib_Sound::SoundPlay("SummonEXP", false);

	//�o���l�̏o��
	for (int i = 0; i < enm->GetExpNum(); i++)
	{
		shared_ptr<EXP> m_exp = make_shared<EXP>();
		scene->GetExpManager()->Register(m_exp, enm->GetPos());
	}
}

//�j��G�t�F�N�g������
void EnemyManager::SummonDestoryEffect(EnemyBase* enm)
{
	//�j��G�t�F�N�g
	{
		//�G�t�F�N�g�̐�
		const int EffectNum = 20;
		scene->GetEffectManager()->GetEffectFromSerchKey("Destroy")->Play(enm->GetPos(), EffectNum);
	}
}