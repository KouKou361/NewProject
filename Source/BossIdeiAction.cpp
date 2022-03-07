#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"


//開始処理
void BossIdeiAction::Start()
{
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->Idle), true);
	timer = 0;
}

//実行処理
ActionBase::State BossIdeiAction::Run()
{
	timer++;
	constexpr float TimeMax = 300;
	if (timer >= TimeMax)
	{
		return ActionBase::State::Failed;
	}
	return ActionBase::State::Run;

}

//終了処理
void BossIdeiAction::End()
{

}

//デバッグ用
void BossIdeiAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossIdeiAction");
	ImGui::End();
}