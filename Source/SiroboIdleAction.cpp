#include "SiroboActionDerived.h"
#include "SiroboPlayer.h"
#include "Player.h"
#include "Animetion.h"
//待機行動

//開始処理
void SiroboIdleAction::Start()
{
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(),siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Idle),true);
	siroboOwner->SetState(Sirobo::StateType::TYPE_IDLE);
}

//実行処理
ActionBase::State SiroboIdleAction::Run()
{
	//仲間になる範囲にいるなら
	if (siroboOwner->SearchPosition(siroboOwner->FollowSerchL, siroboOwner->GetPlayer()->GetPos()))
	{
		siroboOwner->SetTeam(Sirobo::Team::TEAM_PLAYER);
		return ActionBase::State::FAILED;
	}

	return ActionBase::State::RUN;

}

//終了処理
void SiroboIdleAction::End()
{

}
//もし目標物が消えてしまった場合
ActionBase::State SiroboIdleAction::DeleteTarget()
{
	//まあ　待機中は関係ないので
	return Run();
}

//Imguiデバッグ
void SiroboIdleAction::DebugImgui()
{
	//TK_Lib::Debug3D::Circle(siroboOwner->GetPos(), siroboOwner->FollowSerchL);
	ImGui::Begin("Sirobo");
	ImGui::Text("Idle");
	ImGui::End();
}