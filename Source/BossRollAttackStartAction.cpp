#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//�J�n����
void BossRollAttackStartAction::Start()
{
	owner->TargetFaild();
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->BossOpenGoToRoll), false);
}

//���s����
ActionBase::State BossRollAttackStartAction::Run()
{

	owner->TargetFaild();
	PlayerToTurn();
	//�U�����[�V������
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
	

		//�T�E���h
		float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());

		if (AnimetionRate >= 0.7f)
		{
			if (AnimetionRate <= 0.72f)
			{
				TK_Lib::Lib_Sound::SoundPlay("BossAttackStart", false);
			}
		}

		return ActionBase::State::Run;

	}

	return ActionBase::State::Complete;
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
