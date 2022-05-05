#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

//開始処理
void PursuitAction::Start()
{
	searchFlg = true;
	targetPos = { 0,0,0 };

	//追尾（走る）モーションの取得
	const int RunAnimetionIndex = owner->GetAnime()->GetIndex(owner->GetAnime()->Run);
	//走るアニメーション再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), RunAnimetionIndex, true);

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
		return ActionBase::State::FAILED;
	}

	//目的地に移動！（経路探索）
	if (PursuitTarget())
	{
		//索敵範囲にいるなら
		return ActionBase::State::RUN;
	}


	
	return ActionBase::State::FAILED;


}

//ターゲットに向かって進む。
bool PursuitAction::PursuitTarget()
{
	//索敵範囲にいるなら（経路探索）
	if (owner->SearchTarget(owner->GetSearchL()))
	{
		//進む
		VECTOR3 Pos;
		owner->RouteSearch(Pos);
		owner->MoveOnPosition(Pos);
		return true;

	}
	return false;
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