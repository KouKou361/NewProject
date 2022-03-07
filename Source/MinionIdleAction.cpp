#include "MinionActionDerived.h"
#include "MinionPlayer.h"
#include "Player.h"
#include "Animetion.h"
//待機行動

//開始処理
void MinionIdleAction::Start()
{
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(),minionOwner->anime->GetIndex(minionOwner->anime->Idle),true);
	minionOwner->SetState(MinionPlayer::StateType::TypeIdle);
}

//実行処理
ActionBase::State MinionIdleAction::Run()
{
	//仲間になる範囲にいるなら
	if (minionOwner->SearchPosition(minionOwner->FollowSerchL, minionOwner->GetPlayer()->GetPos()))
	{
		minionOwner->SetTeam(MinionPlayer::Team::TeamPlayer);
		return ActionBase::State::Failed;
	}

	return ActionBase::State::Run;

}

//終了処理
void MinionIdleAction::End()
{

}
//もし目標物が消えてしまった場合
ActionBase::State MinionIdleAction::DeleteTarget()
{
	//まあ　待機中は関係ないので
	return Run();
}

//Imguiデバッグ
void MinionIdleAction::DebugImgui()
{
	//TK_Lib::Debug3D::Circle(minionOwner->GetPos(), minionOwner->FollowSerchL);
	ImGui::Begin("Minion");
	ImGui::Text("Idle");
	ImGui::End();
}