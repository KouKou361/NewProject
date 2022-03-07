#include "MinionActionDerived.h"
#include "Player.h"
#include "MinionPlayer.h"
#include "Animetion.h"

//�ҋ@�s��

//�J�n����
void MinionDieAction::Start()
{

	minionOwner->SetMoveVec({0,0,0});
	//minionOwner->SetTarget(nullptr);
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(), minionOwner->anime->GetIndex(minionOwner->anime->Die), false);
	minionOwner->SetState(MinionPlayer::StateType::TypeDead);
	TK_Lib::Lib_Sound::SoundPlay("MinionDown", false);
}

//���s����
ActionBase::State MinionDieAction::Run()
{
	if (minionOwner->GetState() != MinionPlayer::StateType::TypeDead)
	{
		return ActionBase::State::Failed;
	}
	return ActionBase::State::Run;
	

	

}

//�I������
void MinionDieAction::End()
{

}

//Imgui�f�o�b�O
void MinionDieAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Die");
	ImGui::End();
}