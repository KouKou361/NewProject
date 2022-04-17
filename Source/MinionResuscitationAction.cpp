#include "MinionActionDerived.h"
#include "Player.h"
#include "MinionPlayer.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "Animetion.h"

//�ҋ@�s��

//�J�n����
void MinionResuscitationAction::Start()
{
	minionOwner->SetMoveVec({ 0,0,0 });
	minionOwner->ResuscitationTime = 0;
}

//���s����
ActionBase::State MinionResuscitationAction::Run()
{
	if (!minionOwner->IsResuscitation())
	{
		minionOwner->SetState(MinionPlayer::StateType::TYPE_DEAD);
		//�h������Ă��Ȃ��Ȃ�
		return ActionBase::State::Failed;
	}

	//�h���X�V����
	UpdateResuscitation();
	if (minionOwner->GetState() == MinionPlayer::StateType::TYPE_STAND_BY)
	{
		return ActionBase::State::Failed;
	}

	minionOwner->ResuscitationFlg = false;
	return ActionBase::State::Run;

	
}

//�h������
void MinionResuscitationAction::Resuscitation()
{
	minionOwner->ResuscitationTime = 0;
	minionOwner->SetHp(minionOwner->GetMaxHp());
	minionOwner->SetState(MinionPlayer::StateType::TYPE_STAND_BY);
}

//�h���X�V����
void MinionResuscitationAction::UpdateResuscitation()
{
	minionOwner->ResuscitationTime++;
	const int MaxResuscitationTime = 60;

	if (minionOwner->ResuscitationTime >= MaxResuscitationTime)
	{
		Resuscitation();
	}

}

//�����ڕW���������Ă��܂����ꍇ
ActionBase::State MinionResuscitationAction::DeleteTarget()
{
	return Run();
}
//�I������
void MinionResuscitationAction::End()
{
	minionOwner->ResuscitationTime = 0;
}

//Imgui�f�o�b�O
void MinionResuscitationAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Resuscitation");
	ImGui::Text("ResuscitationTime=%d", minionOwner->ResuscitationTime);
	ImGui::End();
}