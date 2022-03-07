#include "MinionActionDerived.h"
#include "MinionPlayer.h"
#include "Player.h"
#include "Animetion.h"
//�ҋ@�s��

//�J�n����
void MinionIdleAction::Start()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(),minionOwner->anime->GetIndex(minionOwner->anime->Idle),true);
	minionOwner->SetState(MinionPlayer::StateType::TypeIdle);
}

//���s����
ActionBase::State MinionIdleAction::Run()
{
	//���ԂɂȂ�͈͂ɂ���Ȃ�
	if (minionOwner->SearchPosition(minionOwner->FollowSerchL, minionOwner->GetPlayer()->GetPos()))
	{
		minionOwner->SetTeam(MinionPlayer::Team::TeamPlayer);
		return ActionBase::State::Failed;
	}

	return ActionBase::State::Run;

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