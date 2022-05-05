#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//開始処理
void BossRollAttackStartAction::Start()
{
	//プレイヤーは攻撃目標にできない！（回転中はミニオンたちの攻撃は受けない！）
	owner->TargetFaild();

	//ボスの回転攻撃終了モーションの取得
	const int BossRollAttackStartAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->BossOpenGoToRoll);
	//回転攻撃アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossRollAttackStartAnimetion, false);
}

//実行処理
ActionBase::State BossRollAttackStartAction::Run()
{

	//プレイヤーの方向に向く
	PlayerToTurn();
	//攻撃モーション中
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//着地サウンド
		BossJumpDownSound();

		//行動続行
		return ActionBase::State::RUN;

	}

	//行動終了！次の行動へ遷移
	return ActionBase::State::COMPLETE;
}

//終了処理
void BossRollAttackStartAction::PlayerToTurn()
{
	//攻撃目標に向く
	VECTOR3 TargetPos=owner->GetTarget()->GetPos();
	VECTOR3 OwnerPos = owner->GetPos();
	owner->Turn(TargetPos- OwnerPos);
}

//終了処理
void BossRollAttackStartAction::End()
{

}

//デバッグ用
void BossRollAttackStartAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossRollAttackStartAction");
	ImGui::End();
}

//着地サウンド
void BossRollAttackStartAction::BossJumpDownSound()
{
	//サウンド
	float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());

	//ボスの登場サウンド開始
	const float BossJumpDownStartSound = 0.7f;
	//ボスの登場サウンド終了
	const float BossJumpDownEndSound = 0.72f;

	if (AnimetionRate >= BossJumpDownStartSound)
	{
		if (AnimetionRate <= BossJumpDownEndSound)
		{
			TK_Lib::Lib_Sound::SoundPlay("BossAttackStart", false);
		}
	}
}