#include "MinionActionDerived.h"
#include "Player.h"
#include "MinionPlayer.h"
#include "Animetion.h"

//�ҋ@�s��

//�J�n����
void MinionBackAction::Start()
{
	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(), minionOwner->GetAnime()->GetIndex(minionOwner->GetAnime()->Run), true);
	minionOwner->SetState(MinionPlayer::StateType::TYPE_BACK);
}

//���s����
ActionBase::State MinionBackAction::Run()
{
	//�v���C���[�̈ʒu�A�~�j�I���̈ʒu
	XMVECTOR PlayerPos,MinionPos,V,NV,MoveVec;
	VECTOR3 playerPos = minionOwner->GetPlayer()->GetPos();
	PlayerPos = XMLoadFloat3(&playerPos);
	VECTOR3 OwnerPos = minionOwner->GetPos();
	MinionPos = XMLoadFloat3(&OwnerPos);
	V=XMVectorSubtract(PlayerPos,MinionPos);
	//�v���C���[�ƃ~�j�I���̈ʒu�x�N�g���𐳋K��
	NV = XMVector3Normalize(V);
	MoveVec=XMVectorScale(NV, minionOwner->GetSpeed());

	VECTOR3 Vec;
	XMStoreFloat3(&Vec,MoveVec);

	minionOwner->SetMoveVec(Vec);

	if (minionOwner->SearchPosition(minionOwner->StandBySerchL, minionOwner->GetPlayer()->GetPos()))
	{
		return ActionBase::State::Failed;
	}
	return ActionBase::State::Run;
}

//�����ڕW���������Ă��܂����ꍇ
ActionBase::State MinionBackAction::DeleteTarget()
{
	//�܂��@�ҋ@���͊֌W�Ȃ��̂�
	return Run();
}
//�I������
void MinionBackAction::End()
{

}

//Imgui�f�o�b�O
void MinionBackAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Back");
	ImGui::End();
}