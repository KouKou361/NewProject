#include "SiroboActionDerived.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "Animetion.h"

//待機行動

//開始処理
void SiroboBackAction::Start()
{
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Run), true);
	siroboOwner->SetState(Sirobo::StateType::TYPE_BACK);
}

//実行処理
ActionBase::State SiroboBackAction::Run()
{
	//プレイヤーの位置、ミニオンの位置
	XMVECTOR PlayerPos, MinionPos, V, NV, MoveVec;
	VECTOR3 playerPos = siroboOwner->GetPlayer()->GetPos();
	PlayerPos = XMLoadFloat3(&playerPos);
	VECTOR3 OwnerPos = siroboOwner->GetPos();
	MinionPos = XMLoadFloat3(&OwnerPos);
	V = XMVectorSubtract(PlayerPos, MinionPos);
	//プレイヤーとミニオンの位置ベクトルを正規化
	NV = XMVector3Normalize(V);
	MoveVec = XMVectorScale(NV, siroboOwner->GetSpeed());

	VECTOR3 Vec;
	XMStoreFloat3(&Vec, MoveVec);

	siroboOwner->SetMoveVec(Vec);

	//縦方向の当たり判定（Y方向）
	siroboOwner->VerticalCollision();

	if (siroboOwner->SearchPosition(siroboOwner->StandBySerchL, siroboOwner->GetPlayer()->GetPos()))
	{
		return ActionBase::State::FAILED;
	}
	return ActionBase::State::RUN;
}

//もし目標物が消えてしまった場合
ActionBase::State SiroboBackAction::DeleteTarget()
{
	//まあ　待機中は関係ないので
	return Run();
}
//終了処理
void SiroboBackAction::End()
{

}

//Imguiデバッグ
void SiroboBackAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Back");
	ImGui::End();
}