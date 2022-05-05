#include "SiroboActionDerived.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "Animetion.h"

//�ҋ@�s��

//�J�n����
void SiroboResuscitationAction::Start()
{
	siroboOwner->SetMoveVec({ 0,0,0 });
	siroboOwner->resuscitationTime = 0;
}

//���s����
ActionBase::State SiroboResuscitationAction::Run()
{
	if (!siroboOwner->IsResuscitation())
	{
		siroboOwner->SetState(Sirobo::StateType::TYPE_DEAD);
		//�h������Ă��Ȃ��Ȃ�
		return ActionBase::State::FAILED;
	}

	//�h���X�V����
	UpdateResuscitation();
	if (siroboOwner->GetState() == Sirobo::StateType::TYPE_STAND_BY)
	{
		return ActionBase::State::FAILED;
	}

	siroboOwner->resuscitationFlg = false;
	return ActionBase::State::RUN;

	
}

//�h������
void SiroboResuscitationAction::Resuscitation()
{
	siroboOwner->resuscitationTime = 0;
	siroboOwner->SetHp(siroboOwner->GetMaxHp());
	siroboOwner->SetState(Sirobo::StateType::TYPE_STAND_BY);
}

//�h���X�V����
void SiroboResuscitationAction::UpdateResuscitation()
{
	siroboOwner->resuscitationTime+=TK_Lib::Window::GetElapsedTime();

	//�v���C���[���h�����鎞��
	const float MaxResuscitationTime = 1;

	if (siroboOwner->resuscitationTime >= MaxResuscitationTime)
	{
		Resuscitation();
	}

}

//�����ڕW���������Ă��܂����ꍇ
ActionBase::State SiroboResuscitationAction::DeleteTarget()
{
	return Run();
}
//�I������
void SiroboResuscitationAction::End()
{
	siroboOwner->resuscitationTime = 0;
}

//Imgui�f�o�b�O
void SiroboResuscitationAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Resuscitation");
	ImGui::Text("ResuscitationTime=%f", siroboOwner->resuscitationTime);
	ImGui::End();
}