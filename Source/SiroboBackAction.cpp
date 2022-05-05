#include "SiroboActionDerived.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "Animetion.h"

//�ҋ@�s��

//�J�n����
void SiroboBackAction::Start()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Run), true);
	siroboOwner->SetState(Sirobo::StateType::TYPE_BACK);
}

//���s����
ActionBase::State SiroboBackAction::Run()
{
	//�v���C���[�����ɑ���
	RunToThePlaye();

	//�c�����̃��f�������蔻��iY�����j
	siroboOwner->VerticalCollision();

	if (siroboOwner->SearchPosition(siroboOwner->StandBySerchL, siroboOwner->GetPlayer()->GetPos()))
	{
		return ActionBase::State::FAILED;
	}
	return ActionBase::State::RUN;
}

//�����ڕW���������Ă��܂����ꍇ
ActionBase::State SiroboBackAction::DeleteTarget()
{
	//�܂��@�ҋ@���͊֌W�Ȃ��̂�
	return Run();
}
//�I������
void SiroboBackAction::End()
{

}

//Imgui�f�o�b�O
void SiroboBackAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Back");
	ImGui::End();
}

//�v���C���[�����ɑ���
void SiroboBackAction::RunToThePlaye()
{
	//�v���C���[�̈ʒu�A�~�j�I���̈ʒu
	XMVECTOR PlayerPos, SiroboPos, V, NV, MoveVec;
	VECTOR3 playerPos = siroboOwner->GetPlayer()->GetPos();
	PlayerPos = XMLoadFloat3(&playerPos);
	VECTOR3 OwnerPos = siroboOwner->GetPos();
	SiroboPos = XMLoadFloat3(&OwnerPos);
	V = XMVectorSubtract(PlayerPos, SiroboPos);
	//�v���C���[�ƃ~�j�I���̈ʒu�x�N�g���𐳋K��
	NV = XMVector3Normalize(V);
	MoveVec = XMVectorScale(NV, siroboOwner->GetSpeed());

	VECTOR3 Vec;
	XMStoreFloat3(&Vec, MoveVec);

	siroboOwner->SetMoveVec(Vec);
}