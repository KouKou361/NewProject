#include "PlayerState.h"
#include "Player.h"
#include "Collision.h"
#include "Animetion.h"
#include "MinionPlayer.h"
#include "Stage.h"

//=============================
//�v���C���[�̃{�X��o�ꉉ�o�N���X
//=============================

//������
void BossEntryPlayerState::Start(Player* pl)
{
	pl->state = Player::State::BOSS_ENTRY;
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Run), true);
	pl->moveVec = { 0,0,-0.1f };
}
//�X�V
void BossEntryPlayerState::Run(Player* pl)
{
	if (stage->GetEventState() == EventState::TURN_CAMERA_LOOK_FRONT)
	{
		TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Idle), true);
		pl->moveVec = { 0,0,0 };
	}

	pl->Move();

	////�v���C���[�̓��͏���
	//pl->Input();
	////�v���C���[�̉�]
	//pl->Turn(pl->moveVec);
	////�G�Ƃ̓����蔻��
	//pl->VsEnemy();
	////���C�s�b�N�ɂ��ʒu�␳
	//pl->UpdateCollision();
	////Nav���b�V���Ɍ��ݒn���X�V����
	//Collision::Instance().SetTarget(pl->GetPos());
	////�ߋ��̒n�_�̕ۑ�
	//pl->SetOldPos(pl->GetPos());
	////���G���Ԃ̍X�V
	//pl->InvincibleTimeUpdate();

	//if (fabsf(pl->moveVec.x) + fabsf(pl->moveVec.y) + fabsf(pl->moveVec.z) == 0)
	//{
	//	pl->ChangeState(pl->stateWait.get());
	//}
}
//�I��
void BossEntryPlayerState::End(Player* pl)
{

}



