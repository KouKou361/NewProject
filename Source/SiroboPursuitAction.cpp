#include "SiroboActionDerived.h"
#include "Player.h"
#include "SiroboPlayer.h"


//�ҋ@�s��

//�J�n����
void SiroboPursuitAction::Start()
{
//	siroboOwner->SetState(SiroboPlayer::StateType::);
}

//���s����
ActionBase::State SiroboPursuitAction::Run()
{
	return ActionBase::State::RUN;
}

//�I������
void SiroboPursuitAction::End()
{

}

//Imgui�f�o�b�O
void SiroboPursuitAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Pursuit");
	ImGui::End();
}