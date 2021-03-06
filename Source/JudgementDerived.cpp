#include "JudgementDerived.h"
#include "EnemyBase.h"
//待機判定処理
bool IdleJudgement::Judgement()
{
	//無条件でTRUE
	return true;
}

//追跡判定処理
bool PursuitJudgement::Judgement()
{
	//もし攻撃されていた事があるなら
	if (owner->GetOldDamageFlg())return true;
	//索敵内にいればtrueを返す
	if (owner->SearchTarget(owner->GetSearchL()))
	{
		return true;
	}
	return false;
}

//攻撃判定処理
bool AttackJudgement::Judgement()
{
	//攻撃できる範囲にいるなら
	if (owner->SearchTarget(owner->GetAttackL()))
	{
		return true;
	}
	return false;
}
//ダメージ判定処理
bool DamageJudgement::Judgement()
{
	return owner->GetDamageFlg();
}

//死亡判定処理
bool DeadJudgement::Judgement()
{
	return owner->GetDeadFlg();
}

//回転攻撃判定処理（ボス専用）
bool BossRollAttackJudgement::Judgement()
{
	return true;
}