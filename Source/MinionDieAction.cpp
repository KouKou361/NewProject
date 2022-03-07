#include "MinionActionDerived.h"
#include "Player.h"
#include "MinionPlayer.h"
#include "Animetion.h"

//待機行動

//開始処理
void MinionDieAction::Start()
{

	minionOwner->SetMoveVec({0,0,0});
	//minionOwner->SetTarget(nullptr);
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(), minionOwner->anime->GetIndex(minionOwner->anime->Die), false);
	minionOwner->SetState(MinionPlayer::StateType::TypeDead);
	TK_Lib::Lib_Sound::SoundPlay("MinionDown", false);
}

//実行処理
ActionBase::State MinionDieAction::Run()
{
	if (minionOwner->GetState() != MinionPlayer::StateType::TypeDead)
	{
		return ActionBase::State::Failed;
	}
	return ActionBase::State::Run;
	

	

}

//終了処理
void MinionDieAction::End()
{

}

//Imguiデバッグ
void MinionDieAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Die");
	ImGui::End();
}