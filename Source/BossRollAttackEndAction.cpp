#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//開始処理
void BossRollAttackEndAction::Start()
{
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->BossCloseStopRoll), false);
	owner->TargetFaild();

}

//実行処理
ActionBase::State BossRollAttackEndAction::Run()
{
	

	owner->TargetFaild();
	//攻撃モーション中
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//サウンド
		float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());
		if (AnimetionRate >= 0.3f)
		{
			if (AnimetionRate <= 0.4f)
			{
				TK_Lib::Lib_Sound::SoundPlay("BossJumpDown", false);
			}
		}

		return ActionBase::State::RUN;
	
	}

	return ActionBase::State::COMPLETE;
}

//終了処理
void BossRollAttackEndAction::End()
{
	owner->TargetComplete();

}

//デバッグ用
void BossRollAttackEndAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossRollAttackEndAction");
	ImGui::End();
}
