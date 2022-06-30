#include "PlayerState.h"
#include "Player.h"
#include "Collision.h"
#include "Animetion.h"
#include "SiroboPlayer.h"
#include "Scene.h"
#include "EnemyManager.h"
//=============================
//�v���C���[�̍U���N���X
//=============================

//������
void AttackState::Start(Player* pl)
{
	//�U���A�j���[�V����
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Attack1),false);
	pl->state = Player::State::ATTACK;

	//�U���o������
	attackFlg = true;
}
//�X�V
void AttackState::Run(Player* pl)
{

	//�v���C���[�̓��͏���
	pl->Input();
	//����
	DownSpeed(pl);
	//�G�Ƃ̓����蔻��
	pl->VsEnemy();
	//���C�s�b�N�ɂ��ʒu�␳
	pl->UpdateCollision();

	//�����G�����Ȃ��Ȃ�
	if (pl->GetTarget() == nullptr)
	{
		pl->ChangeState(pl->stateWalk.get());
		return;
	}
	//�����X�^���o�C��Ԃ̃V���{�����Ȃ��ꍇ
	if (pl->GetSiroboManager()->GetTypeSiroboSize(Sirobo::StateType::TYPE_STAND_BY) == 0)
	{
		pl->ChangeState(pl->stateWalk.get());
		return;
	}

	//�G�̕����Ɍ�������
	VECTOR3 Vec;
	Vec = pl->GetTarget()->GetPos() - pl->GetPos();
	pl->Turn(Vec);

	//�����A�j���[�V�������ł͂Ȃ��Ȃ�
	if (TK_Lib::Model::IsPlayAnimetion(pl->GetModel()) == false)
	{
		pl->ChangeState(pl->stateWalk.get());
		return;
	}



	float RateTime = TK_Lib::Model::IsPlayAnimetionRate(pl->GetModel());
	//�~�j�I���̍U���J�n
	if (RateTime>=AttackTimeRate)
	{
		if (attackFlg == true)
		{
			pl->siroboManager->OneAttack(nullptr);
		}

		//�U���o�����Ԃ�false�ɂ���
		attackFlg = false;

	}

}
//�I��
void AttackState::End(Player* pl)
{

}

void AttackState::DownSpeed(Player* pl)
{
	pl->moveVec.x *= pl->AttackSpeedDown;
	pl->moveVec.y *= pl->AttackSpeedDown;
	pl->moveVec.z *= pl->AttackSpeedDown;
}

//=============================
//�v���C���[�̃_���[�W�N���X
//=============================

//������
void DamageState::Start(Player* pl)
{
	pl->moveVec = { 0,0,0 };
	pl->state = Player::State::DAMAGE;
	pl->SetDamageFlg(false);
	//�_���[�W�A�j���[�V����
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Damage), false);
}
//�X�V
void DamageState::Run(Player* pl)
{
	//�����A�j���[�V�������ł͂Ȃ��Ȃ�
	if (TK_Lib::Model::IsPlayAnimetion(pl->GetModel())==false)
	{
		pl->ChangeState(pl->stateWalk.get());
	}
}
//�I��
void DamageState::End(Player* pl)
{

}

//=============================
//�v���C���[�̎��S�N���X
//=============================

//������
void DeadState::Start(Player* pl)
{
	pl->moveVec = { 0,0,0 };
	pl->state = Player::State::DEAD;
	pl->SetDeadFlg(false);
	//���S�A�j���[�V����
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Die), false);
	pl->sceneGame->GetEnemyManager()->SetEnemyActive(false);
}
//�X�V
void DeadState::Run(Player* pl)
{
//	//�����A�j���[�V�������ł͂Ȃ��Ȃ�
//	if (TK_Lib::Model::IsPlayAnimetion(pl->GetModel()) == false)
//	{
//		pl->ChangeState(pl->stateWalk.get());
//	}
}
//�I��
void DeadState::End(Player* pl)
{
	pl->sceneGame->GetEnemyManager()->SetEnemyActive(true);
}

//=============================
//�v���C���[�̑ҋ@�N���X
//=============================

//������
void WaitState::Start(Player* pl)
{
	pl->state = Player::State::WAIT;
	//�ҋ@�A�j���[�V����
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Idle), true);
}
//�X�V
void WaitState::Run(Player* pl)
{
	//�v���C���[�̓��͏���
	pl->Input();
	//�v���C���[�̉�]
	pl->Turn(pl->moveVec);
	
	//�����ړ������Ȃ�
	if (fabsf(pl->moveVec.x) + fabsf(pl->moveVec.y) + fabsf(pl->moveVec.z) > 0)
	{
		pl->ChangeState(pl->stateWalk.get());
	}
}
//�I��
void WaitState::End(Player* pl)
{

}

//=============================
//�v���C���[�̈ړ��N���X
//=============================

//������
void WalkState::Start(Player* pl)
{
	pl->state = Player::State::WALK;
	//����A�j���[�V����
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Run), true);
}
//�X�V
void WalkState::Run(Player* pl)
{
	//�v���C���[�̓��͏���
	pl->Input();
	//�v���C���[�̉�]
	pl->Turn(pl->moveVec);
	//�G�Ƃ̓����蔻��
	pl->VsEnemy();
	//���C�s�b�N�ɂ��ʒu�␳
	pl->UpdateCollision();
	//Nav���b�V���Ɍ��ݒn���X�V����
	Collision::Instance().SetTarget(pl->GetPos());
	//�ߋ��̒n�_�̕ۑ�
	pl->SetOldPos(pl->GetPos());
	//���G���Ԃ̍X�V
	pl->InvincibleTimeUpdate();

	if (fabsf(pl->moveVec.x) + fabsf(pl->moveVec.y) + fabsf(pl->moveVec.z) == 0)
	{
		pl->ChangeState(pl->stateWait.get());
	}
}
//�I��
void WalkState::End(Player* pl)
{

}


//=============================
//�v���C���[�̃{�X��o�ꉉ�o�N���X
//=============================

//������
void BossEntryPlayerState::Start(Player* pl)
{
	pl->state = Player::State::BOSS_ENTRY;
	//�����A�j���[�V����
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Run), true);
	//�{�X�o�ꃀ�[�u���A������ƑO�i���Ă����B
	pl->moveVec = { 0,0,-0.1f };
}
//�X�V
void BossEntryPlayerState::Run(Player* pl)
{
	//�{�X�̕����Ɍ����C�x���g�Ɉڍs������
	if (stage->GetEventState() == EventState::TURN_CAMERA_LOOK_FRONT)
	{
		//�O�ɐi�ނ��Ƃ���߂�B
		TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Idle), true);
		pl->moveVec = { 0,0,0 };
	}

	pl->Move();
}
//�I��
void BossEntryPlayerState::End(Player* pl)
{

}






