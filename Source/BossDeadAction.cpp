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

	//待機モーション番号の取得
	const int BossDeadIdeiIndex = owner->GetAnime()->GetIndex(owner->GetAnime()->Idle);
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossDeadIdeiIndex, false);
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
		//次の行動に移行
		return ActionBase::State::FAILED;
		break;
	}


	return ActionBase::State::RUN;
}

//終了処理
void BossDeadAction::End()
{
	const float Vibrationtime = 6.0f;
	const float VibrationVolume = 0.15f;
	//振動
	owner->GetSceneGame()->GetCameraManager()->SetVibration(VibrationVolume, Vibrationtime);
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


//止まる状態
void BossDeadAction::StateStop()
{
	//死亡時間の更新
	if (owner->UpdateDeathTime())
	{
		TK_Lib::Lib_Sound::SoundPlay("BossRoll", false);
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
	{
		//エフェクトの出す数
		const int EffectPlayNum = 3;
		//炎エフェクトの出現
		owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossFire")->Play(owner->GetPos(), EffectPlayNum);
	}

	//死亡時間の更新
	if (owner->UpdateDeathTime())
	{
		TK_Lib::Lib_Sound::SoundPlay("BossExplosion", false);

		const float MaskSpeed = 0.2f;
		owner->MaskStart(MaskSpeed);

		////体力が０になってから消えてしまうまでの時間
		//constexpr float DeathTime = 3.0f;
		////死亡タイムの設定
		//owner->SetDeathTime(DeathTime);
		// 次の状態へ
		state = EventDeleteState::EXPLOSION;
	}
}
//爆発状態
void BossDeadAction::StateExplosion()
{
	const float Vibrationtime = 0.1f;
	const float VibrationVolume = 0.5f;
	//振動
	owner->GetSceneGame()->GetCameraManager()->SetVibration(VibrationVolume, Vibrationtime);
	//爆発エフェクト
	{
		//エフェクトの出す数
		const int EffectPlayNum = 3;
		//炎エフェクトの出現
		owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossExplosion")->Play(owner->GetPos(), EffectPlayNum);
	}

	if (owner->GetMaskVolume() >= 1.0f)
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

