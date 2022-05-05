#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//開始処理
void AttackAction::Start()
{
	//攻撃アニメーション番号の取得
	const int AttackAnimetionIndex = owner->GetAnime()->GetIndex(owner->GetAnime()->Attack1);
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), AttackAnimetionIndex, false);
}

//実行処理
ActionBase::State AttackAction::Run()
{
	//敵の方向に向く
	VECTOR3 Vec =owner->GetTarget()->GetPos()- owner->GetPos();
	owner->Turn(Vec);


	//攻撃モーション中に攻撃する。
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//攻撃開始レート
		constexpr float AttackStartTime = 0.0f;
		//攻撃終了レート
		constexpr float AttackEndTime   = 0.5f;

		//攻撃処理
		owner->AttackCircleNode(owner->GetAttackNode(), owner->GetAttackRadius(), AttackStartTime, AttackEndTime);
		return ActionBase::State::RUN;

	}

	return ActionBase::State::FAILED;
}
void AttackAction::DebugRender()
{
	//TK_Lib::Debug3D::Circle(owner->GetPos(), owner->GetAttackRadius());
}

//終了処理
void AttackAction::End()
{

}

//デバッグ用
void AttackAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("Attack");
	ImGui::End();
}
