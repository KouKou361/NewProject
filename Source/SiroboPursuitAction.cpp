#include "SiroboActionDerived.h"
#include "Player.h"
#include "SiroboPlayer.h"


//待機行動

//開始処理
void SiroboPursuitAction::Start()
{
//	siroboOwner->SetState(SiroboPlayer::StateType::);
}

//実行処理
ActionBase::State SiroboPursuitAction::Run()
{
	return ActionBase::State::RUN;
}

//終了処理
void SiroboPursuitAction::End()
{

}

//Imguiデバッグ
void SiroboPursuitAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Pursuit");
	ImGui::End();
}