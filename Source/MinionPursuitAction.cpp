#include "MinionActionDerived.h"
#include "Player.h"
#include "MinionPlayer.h"


//�ҋ@�s��

//�J�n����
void MinionPursuitAction::Start()
{
//	minionOwner->SetState(MinionPlayer::StateType::);
}

//���s����
ActionBase::State MinionPursuitAction::Run()
{
	return ActionBase::State::RUN;
}

//�I������
void MinionPursuitAction::End()
{

}

//Imgui�f�o�b�O
void MinionPursuitAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Pursuit");
	ImGui::End();
}