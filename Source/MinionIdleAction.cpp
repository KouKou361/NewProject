#include "MinionActionDerived.h"
#include "MinionPlayer.h"
#include "Player.h"
#include "Animetion.h"
//待機行動

//開始処理
void MinionIdleAction::Start()
{
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(),minionOwner->GetAnime()->GetIndex(minionOwner->GetAnime()->Idle),true);
	minionOwner->SetState(MinionPlayer::StateType::TYPE_IDLE);
}

//実行処理
ActionBase::State MinionIdleAction::Run()
{
	//仲間になる範囲にいるなら
	if (minionOwner->SearchPosition(minionOwner->FollowSerchL, minionOwner->GetPlayer()->GetPos()))
	{
		minionOwner->SetTeam(MinionPlayer::Team::TEAM_PLAYER);
		return ActionBase::State::FAILED;
	}

	return ActionBase::State::RUN;

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