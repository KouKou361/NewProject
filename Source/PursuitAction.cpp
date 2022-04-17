#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

//開始処理
void PursuitAction::Start()
{
	searchFlg = true;
	targetPos = { 0,0,0 };
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->Run), true);
}

//実行処理
ActionBase::State PursuitAction::Run()
{
	////もし攻撃されていた事があるなら
	//if (owner->GetOldDamageFlg())
	//{
	//	VECTOR3 Pos;
	//	owner->RouteSearch(Pos);
	//	owner->MoveOnPosition(Pos);
	//	return ActionBase::State::Run;
	//}

	//もし攻撃範囲内にいるなら
	if (owner->SearchTarget(owner->GetAttackL()))
	{
		return ActionBase::State::Failed;
	}
	//索敵範囲にいるなら
	if (owner->SearchTarget(owner->GetSearchL()))
	{
		VECTOR3 Pos;
		owner->RouteSearch(Pos);
		owner->MoveOnPosition(Pos);
		return ActionBase::State::Run;
	}
	return ActionBase::State::Failed;


}

//終了処理
void PursuitAction::End()
{

}


//デバッグ用
void PursuitAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("Pursuit");
	ImGui::End();
}