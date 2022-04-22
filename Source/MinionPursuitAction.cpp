#include "MinionActionDerived.h"
#include "Player.h"
#include "MinionPlayer.h"


//待機行動

//開始処理
void MinionPursuitAction::Start()
{
//	minionOwner->SetState(MinionPlayer::StateType::);
}

//実行処理
ActionBase::State MinionPursuitAction::Run()
{
	return ActionBase::State::RUN;
}

//終了処理
void MinionPursuitAction::End()
{

}

//Imguiデバッグ
void MinionPursuitAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Pursuit");
	ImGui::End();
}