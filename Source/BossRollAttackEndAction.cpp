#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//開始処理
void BossRollAttackEndAction::Start()
{
	//ボスの回転攻撃終了モーションの取得
	const int BossRollAttackEndAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->BossCloseStopRoll);
	//回転攻撃アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossRollAttackEndAnimetion, false);

	//プレイヤーは攻撃目標にできない！（回転中はミニオンたちの攻撃は受けない！）
	owner->TargetFaild();

}

//実行処理
ActionBase::State BossRollAttackEndAction::Run()
{

	//攻撃モーション中
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//着地サウンド
		BossJumpDownSound();
	
		//行動続行！
		return ActionBase::State::RUN;
	
	}

	//行動終了！別の行動へ遷移！
	return ActionBase::State::COMPLETE;
}

//終了処理
void BossRollAttackEndAction::End()
{
	//プレイヤーは攻撃目標にできる！
	owner->TargetComplete();
}

//デバッグ用
void BossRollAttackEndAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossRollAttackEndAction");
	ImGui::End();
}

//着地サウンド
void BossRollAttackEndAction::BossJumpDownSound()
{
	float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());

	//ボスの登場サウンド開始
	const float BossTranceformStartSound = 0.3f;
	//ボスの登場サウンド終了
	const float BossTranceformEndSound = 0.4f;

	if (AnimetionRate >= BossTranceformStartSound)
	{
		if (AnimetionRate <= BossTranceformEndSound)
		{
			//サウンド(ガシャン！)
			TK_Lib::Lib_Sound::SoundPlay("BossJumpDown", false);
		}
	}
}
