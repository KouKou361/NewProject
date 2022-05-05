#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "Scene.h"
#include"EffectManager.h"
#include "EffectBase.h"



class EnemyBase;

//開始処理
void BossSiteDieAction::Start()
{
	//アニメーションの再生
	//TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->Die), false);
	//owner->SetDeadFlg(false);
	//owner->SetDeathTime(1.0f);

}

//実行処理
ActionBase::State BossSiteDieAction::Run()
{
	//エフェクトの数
	const int EffectNum = 1;
	//煙エフェクトの出現
	owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossSiteBreak")->Play(owner->GetPos(), EffectNum);
	//行動続行
	return ActionBase::State::RUN;
}

//終了処理
void BossSiteDieAction::End()
{

}

//デバッグ用
void BossSiteDieAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossSiteDieAction");
	ImGui::End();
}
