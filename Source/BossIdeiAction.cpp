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
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->Idle), true);
	ideiTimer = 0;
}

//実行処理
ActionBase::State BossIdeiAction::Run()
{
	//待機終了時間
	constexpr float TimeMax = 5;
	//待機時間の更新処理
	ideiTimer += TK_Lib::Window::GetElapsedTime();


	if (ideiTimer >= TimeMax)
	{
		//待機終了！次のステートに移行
		return ActionBase::State::FAILED;
	}
	return ActionBase::State::RUN;

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