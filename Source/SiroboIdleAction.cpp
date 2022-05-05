#include "SiroboActionDerived.h"
#include "SiroboPlayer.h"
#include "Player.h"
#include "Animetion.h"
//�ҋ@�s��

//�J�n����
void SiroboIdleAction::Start()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(),siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Idle),true);
	siroboOwner->SetState(Sirobo::StateType::TYPE_IDLE);
}

//���s����
ActionBase::State SiroboIdleAction::Run()
{
	//���ԂɂȂ�͈͂ɂ���Ȃ�
	if (siroboOwner->SearchPosition(siroboOwner->FollowSerchL, siroboOwner->GetPlayer()->GetPos()))
	{
		siroboOwner->SetTeam(Sirobo::Team::TEAM_PLAYER);
		return ActionBase::State::FAILED;
	}

	return ActionBase::State::RUN;

}

//�I������
void SiroboIdleAction::End()
{

}
//�����ڕW���������Ă��܂����ꍇ
ActionBase::State SiroboIdleAction::DeleteTarget()
{
	//�܂��@�ҋ@���͊֌W�Ȃ��̂�
	return Run();
}

//Imgui�f�o�b�O
void SiroboIdleAction::DebugImgui()
{
	//TK_Lib::Debug3D::Circle(siroboOwner->GetPos(), siroboOwner->FollowSerchL);
	ImGui::Begin("Sirobo");
	ImGui::Text("Idle");
	ImGui::End();
}