#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//�J�n����
void BossRollAttackStartAction::Start()
{
	//�v���C���[�͍U���ڕW�ɂł��Ȃ��I�i��]���̓~�j�I�������̍U���͎󂯂Ȃ��I�j
	owner->TargetFaild();

	//�{�X�̉�]�U���I�����[�V�����̎擾
	const int BossRollAttackStartAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->BossOpenGoToRoll);
	//��]�U���A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossRollAttackStartAnimetion, false);
}

//���s����
ActionBase::State BossRollAttackStartAction::Run()
{

	//�v���C���[�̕����Ɍ���
	PlayerToTurn();
	//�U�����[�V������
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//���n�T�E���h
		BossJumpDownSound();

		//�s�����s
		return ActionBase::State::RUN;

	}

	//�s���I���I���̍s���֑J��
	return ActionBase::State::COMPLETE;
}

//�I������
void BossRollAttackStartAction::PlayerToTurn()
{
	//�U���ڕW�Ɍ���
	VECTOR3 TargetPos=owner->GetTarget()->GetPos();
	VECTOR3 OwnerPos = owner->GetPos();
	owner->Turn(TargetPos- OwnerPos);
}

//�I������
void BossRollAttackStartAction::End()
{

}

//�f�o�b�O�p
void BossRollAttackStartAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossRollAttackStartAction");
	ImGui::End();
}

//���n�T�E���h
void BossRollAttackStartAction::BossJumpDownSound()
{
	//�T�E���h
	float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());

	//�{�X�̓o��T�E���h�J�n
	const float BossJumpDownStartSound = 0.7f;
	//�{�X�̓o��T�E���h�I��
	const float BossJumpDownEndSound = 0.72f;

	if (AnimetionRate >= BossJumpDownStartSound)
	{
		if (AnimetionRate <= BossJumpDownEndSound)
		{
			TK_Lib::Lib_Sound::SoundPlay("BossAttackStart", false);
		}
	}
}