#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "Scene.h"
#include "EffectManager.h"
#include "EffectDerived.h"
#include "ObjectFunctionManager.h"
#include "ObjectFunctionDerive.h"


class EnemyBase;

//開始処理
void BossDeadAction::Start()
{
	//サウンド終了
	TK_Lib::Lib_Sound::SoundStop("BossRun");
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->Idle), false);
	state = EventDeleteState::STOP;
}

//実行処理
ActionBase::State BossDeadAction::Run()
{
	//死亡演出によって、状態変位
	switch (state)
	{
	case EventDeleteState::STOP://止まる
		StateStop();
		break;
	case EventDeleteState::FIRE://燃える
		StateFire();
		break;
	case EventDeleteState::EXPLOSION://爆発
		StateExplosion();
		break;
	case EventDeleteState::END://終了
		StateEnd();
		return ActionBase::State::FAILED;
		break;
	}


	return ActionBase::State::RUN;
}
//止まる状態
void BossDeadAction::StateStop()
{
	//死亡時間の更新
	if (owner->UpdateDeathTime())
	{
		//体力が０になってから消えてしまうまでの時間
		constexpr float DeathTime = 2.0f;
		//死亡タイムの設定
		owner->SetDeathTime(DeathTime);
		//次の状態へ
		state = EventDeleteState::FIRE;
	}
}
//燃える状態
void BossDeadAction::StateFire()
{
	//炎エフェクト
	owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossFire")->Play(owner->GetPos(), 3);
	//死亡時間の更新
	if (owner->UpdateDeathTime())
	{
		//体力が０になってから消えてしまうまでの時間
		constexpr float DeathTime = 3.0f;
		//死亡タイムの設定
		owner->SetDeathTime(DeathTime);
		// 次の状態へ
		state = EventDeleteState::EXPLOSION;
	}
}
//爆発状態
void BossDeadAction::StateExplosion()
{
	owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossExplosion")->Play(owner->GetPos(), 5);

	//死亡時間の更新
	if (owner->UpdateDeathTime())
	{
		// 次の状態へ
		state = EventDeleteState::END;
	}
}
//終了状態
void BossDeadAction::StateEnd()
{
	//消滅処理
	owner->Destroy();
}

//終了処理
void BossDeadAction::End()
{
	//ゲームクリアオブジェクトの生成
	{
		std::shared_ptr<FunctionEnd> objFunction = make_shared<FunctionEnd>(owner->GetSceneGame());
		owner->GetSceneGame()->GetObjectFunctionManager()->Register(objFunction);
		objFunction->SetPos(owner->GetPos());
	}

}

//デバッグ用
void BossDeadAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossDeadAction");
	ImGui::End();
}
