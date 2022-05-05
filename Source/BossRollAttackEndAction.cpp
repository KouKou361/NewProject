#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//�J�n����
void BossRollAttackEndAction::Start()
{
	//�{�X�̉�]�U���I�����[�V�����̎擾
	const int BossRollAttackEndAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->BossCloseStopRoll);
	//��]�U���A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossRollAttackEndAnimetion, false);

	//�v���C���[�͍U���ڕW�ɂł��Ȃ��I�i��]���̓~�j�I�������̍U���͎󂯂Ȃ��I�j
	owner->TargetFaild();

}

//���s����
ActionBase::State BossRollAttackEndAction::Run()
{

	//�U�����[�V������
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//���n�T�E���h
		BossJumpDownSound();
	
		//�s�����s�I
		return ActionBase::State::RUN;
	
	}

	//�s���I���I�ʂ̍s���֑J�ځI
	return ActionBase::State::COMPLETE;
}

//�I������
void BossRollAttackEndAction::End()
{
	//�v���C���[�͍U���ڕW�ɂł���I
	owner->TargetComplete();
}

//�f�o�b�O�p
void BossRollAttackEndAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossRollAttackEndAction");
	ImGui::End();
}

//���n�T�E���h
void BossRollAttackEndAction::BossJumpDownSound()
{
	float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());

	//�{�X�̓o��T�E���h�J�n
	const float BossTranceformStartSound = 0.3f;
	//�{�X�̓o��T�E���h�I��
	const float BossTranceformEndSound = 0.4f;

	if (AnimetionRate >= BossTranceformStartSound)
	{
		if (AnimetionRate <= BossTranceformEndSound)
		{
			//�T�E���h(�K�V�����I)
			TK_Lib::Lib_Sound::SoundPlay("BossJumpDown", false);
		}
	}
}
