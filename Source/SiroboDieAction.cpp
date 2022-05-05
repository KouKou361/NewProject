#include "SiroboActionDerived.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "Animetion.h"

//待機行動

//開始処理
void SiroboDieAction::Start()
{

	siroboOwner->SetMoveVec({0,0,0});
	//siroboOwner->SetTarget(nullptr);
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Die), false);
	siroboOwner->SetState(Sirobo::StateType::TYPE_DEAD);
	TK_Lib::Lib_Sound::SoundPlay("SiroboDown", false);
}

//実行処理
ActionBase::State SiroboDieAction::Run()
{
	if (siroboOwner->GetState() != Sirobo::StateType::TYPE_DEAD)
	{
		return ActionBase::State::FAILED;
	}
	return ActionBase::State::RUN;
	

	

}

//終了処理
void SiroboDieAction::End()
{

}

//Imguiデバッグ
void SiroboDieAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Die");
	ImGui::End();
}