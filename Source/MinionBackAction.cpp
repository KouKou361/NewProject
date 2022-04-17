#include "MinionActionDerived.h"
#include "Player.h"
#include "MinionPlayer.h"
#include "Animetion.h"

//待機行動

//開始処理
void MinionBackAction::Start()
{
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(), minionOwner->GetAnime()->GetIndex(minionOwner->GetAnime()->Run), true);
	minionOwner->SetState(MinionPlayer::StateType::TYPE_BACK);
}

//実行処理
ActionBase::State MinionBackAction::Run()
{
	//プレイヤーの位置、ミニオンの位置
	XMVECTOR PlayerPos,MinionPos,V,NV,MoveVec;
	VECTOR3 playerPos = minionOwner->GetPlayer()->GetPos();
	PlayerPos = XMLoadFloat3(&playerPos);
	VECTOR3 OwnerPos = minionOwner->GetPos();
	MinionPos = XMLoadFloat3(&OwnerPos);
	V=XMVectorSubtract(PlayerPos,MinionPos);
	//プレイヤーとミニオンの位置ベクトルを正規化
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

//もし目標物が消えてしまった場合
ActionBase::State MinionBackAction::DeleteTarget()
{
	//まあ　待機中は関係ないので
	return Run();
}
//終了処理
void MinionBackAction::End()
{

}

//Imguiデバッグ
void MinionBackAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Back");
	ImGui::End();
}