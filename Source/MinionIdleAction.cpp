#include "MinionActionDerived.h"
#include "MinionPlayer.h"
#include "Player.h"
#include "Animetion.h"
//�ҋ@�s��

//�J�n����
void MinionIdleAction::Start()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(),minionOwner->GetAnime()->GetIndex(minionOwner->GetAnime()->Idle),true);
	minionOwner->SetState(MinionPlayer::StateType::TYPE_IDLE);
}

//���s����
ActionBase::State MinionIdleAction::Run()
{
	//���ԂɂȂ�͈͂ɂ���Ȃ�
	if (minionOwner->SearchPosition(minionOwner->FollowSerchL, minionOwner->GetPlayer()->GetPos()))
	{
		minionOwner->SetTeam(MinionPlayer::Team::TEAM_PLAYER);
		return ActionBase::State::FAILED;
	}

	return ActionBase::State::RUN;

}

//�I������
void MinionIdleAction::End()
{

}
//�����ڕW���������Ă��܂����ꍇ
ActionBase::State MinionIdleAction::DeleteTarget()
{
	//�܂��@�ҋ@���͊֌W�Ȃ��̂�
	return Run();
}

//Imgui�f�o�b�O
void MinionIdleAction::DebugImgui()
{
	//TK_Lib::Debug3D::Circle(minionOwner->GetPos(), minionOwner->FollowSerchL);
	ImGui::Begin("Minion");
	ImGui::Text("Idle");
	ImGui::End();
}