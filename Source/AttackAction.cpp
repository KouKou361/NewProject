#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//開始処理
void AttackAction::Start()
{
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->Attack1), false);
}

//実行処理
ActionBase::State AttackAction::Run()
{

	VECTOR3 Vec =owner->GetTarget()->GetPos()- owner->GetPos();
	owner->Turn(Vec);

	//攻撃モーション中
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		owner->AttackCircleNode(owner->GetAttackNode(), owner->GetAttackRadius(), 0.0f, 0.5f);
		return ActionBase::State::Run;

	}

	return ActionBase::State::Failed;
}
void AttackAction::DebugRender()
{
	TK_Lib::Debug3D::Circle(owner->GetPos(), owner->GetAttackRadius());
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
