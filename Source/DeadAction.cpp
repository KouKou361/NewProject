#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"


class EnemyBase;

//開始処理
void DeadAction::Start()
{
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->Die), false);
	owner->SetDeadFlg(false);
	owner->SetDeathTime(1.0f);
}

//実行処理
ActionBase::State DeadAction::Run()
{

	//もし死亡アニメーションが終了したなら
	if (!TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//死亡時間の更新
		if (owner->UpdateDeathTime())
		{
			owner->Destroy();
			return ActionBase::State::Failed;
		}
	}


	return ActionBase::State::Run;
}

//終了処理
void DeadAction::End()
{

}

//デバッグ用
void DeadAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("Dead");
	ImGui::End();
}
