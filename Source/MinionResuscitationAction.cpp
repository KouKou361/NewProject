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
	minionOwner->resuscitationTime = 0;
}

//���s����
ActionBase::State MinionResuscitationAction::Run()
{
	if (!minionOwner->IsResuscitation())
	{
		minionOwner->SetState(MinionPlayer::StateType::TYPE_DEAD);
		//�h������Ă��Ȃ��Ȃ�
		return ActionBase::State::FAILED;
	}

	//�h���X�V����
	UpdateResuscitation();
	if (minionOwner->GetState() == MinionPlayer::StateType::TYPE_STAND_BY)
	{
		return ActionBase::State::FAILED;
	}

	minionOwner->resuscitationFlg = false;
	return ActionBase::State::RUN;

	
}

//�h������
void MinionResuscitationAction::Resuscitation()
{
	minionOwner->resuscitationTime = 0;
	minionOwner->SetHp(minionOwner->GetMaxHp());
	minionOwner->SetState(MinionPlayer::StateType::TYPE_STAND_BY);
}

//�h���X�V����
void MinionResuscitationAction::UpdateResuscitation()
{
	minionOwner->resuscitationTime++;
	const int MaxResuscitationTime = 60;

	if (minionOwner->resuscitationTime >= MaxResuscitationTime)
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
	minionOwner->resuscitationTime = 0;
}

//Imgui�f�o�b�O
void MinionResuscitationAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Resuscitation");
	ImGui::Text("ResuscitationTime=%d", minionOwner->resuscitationTime);
	ImGui::End();
}