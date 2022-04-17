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
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->Idle), false);
	owner->SetDeathTime(2);
	state = EventDeleteState::STOP;
}

//実行処理
ActionBase::State BossDeadAction::Run()
{
	//もし死亡アニメーションが終了したなら
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))return ActionBase::State::Run;


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
		return ActionBase::State::Failed;
		break;
	}


	return ActionBase::State::Run;
}
//止まる
void BossDeadAction::StateStop()
{
	//死亡時間の更新
	if (owner->UpdateDeathTime())
	{
		owner->SetDeathTime(3);
		state = EventDeleteState::FIRE;
	}
}
//燃える
void BossDeadAction::StateFire()
{
	owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossFire")->Play(owner->GetPos(), 3);
	//死亡時間の更新
	if (owner->UpdateDeathTime())
	{
		owner->SetDeathTime(3);
		state = EventDeleteState::EXPLOSION;
	}
}
//爆発
void BossDeadAction::StateExplosion()
{
	owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossExplosion")->Play(owner->GetPos(), 5);
	//死亡時間の更新
	if (owner->UpdateDeathTime())
	{
		state = EventDeleteState::END;
	}
}
//終了
void BossDeadAction::StateEnd()
{
	owner->Destroy();
}

//終了処理
void BossDeadAction::End()
{
	std::shared_ptr<FunctionEnd> objFunction = make_shared<FunctionEnd>(owner->GetSceneGame());
	owner->GetSceneGame()->GetObjectFunctionManager()->Register(objFunction);
	objFunction->SetPos(owner->GetPos());

}

//デバッグ用
void BossDeadAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossDeadAction");
	ImGui::End();
}
