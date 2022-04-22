#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//�J�n����
void BossRollAttackEndAction::Start()
{
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->BossCloseStopRoll), false);
	owner->TargetFaild();

}

//���s����
ActionBase::State BossRollAttackEndAction::Run()
{
	

	owner->TargetFaild();
	//�U�����[�V������
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//�T�E���h
		float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());
		if (AnimetionRate >= 0.3f)
		{
			if (AnimetionRate <= 0.4f)
			{
				TK_Lib::Lib_Sound::SoundPlay("BossJumpDown", false);
			}
		}

		return ActionBase::State::RUN;
	
	}

	return ActionBase::State::COMPLETE;
}

//�I������
void BossRollAttackEndAction::End()
{
	owner->TargetComplete();

}

//�f�o�b�O�p
void BossRollAttackEndAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossRollAttackEndAction");
	ImGui::End();
}
