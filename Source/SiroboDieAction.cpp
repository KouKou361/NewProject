#include "SiroboActionDerived.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "Animetion.h"

//�ҋ@�s��

//�J�n����
void SiroboDieAction::Start()
{

	siroboOwner->SetMoveVec({0,0,0});
	//siroboOwner->SetTarget(nullptr);
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Die), false);
	siroboOwner->SetState(Sirobo::StateType::TYPE_DEAD);
	TK_Lib::Lib_Sound::SoundPlay("SiroboDown", false);
}

//���s����
ActionBase::State SiroboDieAction::Run()
{
	if (siroboOwner->GetState() != Sirobo::StateType::TYPE_DEAD)
	{
		return ActionBase::State::FAILED;
	}
	return ActionBase::State::RUN;
	

	

}

//�I������
void SiroboDieAction::End()
{

}

//Imgui�f�o�b�O
void SiroboDieAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Die");
	ImGui::End();
}