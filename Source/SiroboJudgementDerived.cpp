#include "SiroboJudgementDerived.h"
#include "SiroboPlayer.h"
#include "Player.h"
#include "EnemyManager.h"
#include "ObjectBase.h"
#include "ObjectManager.h"

//待機判定処理
bool SiroboIdleJudgement::Judgement()
{
	//無条件でTRUE
	return true;
}

//仲間判定処理
bool SiroboFollowJudgement::Judgement()
{
	//ミニオンがプレイヤーの味方なら
	if (siroboOwner->GetTeam() == static_cast<Sirobo::Team>(Sirobo::Team::TEAM_PLAYER))
	{
		return true;
	}
	return false;
}
bool SiroboBackJudgement::Judgement()
{
	//もしプレイヤーの決められた範囲外なら
	if (!siroboOwner->SearchPosition(siroboOwner->StandBySerchL, siroboOwner->GetPlayer()->GetPos()))
	{
		return true;
	}
	return false;
}

//ついていく　攻撃OK判定処理
bool SiroboStandByJudgement::Judgement()
{
	//もしプレイヤーの決められた範囲なら
	if (siroboOwner->SearchPosition(siroboOwner->StandBySerchL, siroboOwner->GetPlayer()->GetPos()))
	{
		return true;
	}
	return false;
}


//追跡判定処理
bool SiroboPursuitJudgement::Judgement()
{
	return true;
}

//攻撃判定処理
bool SiroboAttackJudgement::Judgement()
{

	VECTOR3 OutPos;

	//敵との当たり判定
	{
		EnemyBase* OutEnm = nullptr;

		if (siroboOwner->GetManager()->GetEnemyManager()->CollisionEnemy(
			siroboOwner->GetPos(),
			siroboOwner->GetWeight(),
			siroboOwner->GetCollisionRadius(),
			OutPos, OutEnm)
			)
		{
			//もし敵の「ミニオンが攻撃できる最大数」に達しているなら
			if (OutEnm->GetNumBeAttacked() >= OutEnm->GetMaxBeAttacked())
			{
				return false;
			}
			return true;
		}

	}

	//Objectとの当たり判定
	{
		ObjectBase* OutObj = nullptr;

		if (siroboOwner->GetManager()->GetObjectManager()->CollisionCircleObject(
			siroboOwner->GetPos(),
			siroboOwner->GetWeight(),
			siroboOwner->GetCollisionRadius(),
			OutPos, OutObj)
			)
		{
			//もし敵の「ミニオンが攻撃できる最大数」に達しているなら
			if (OutObj->GetNumBeAttacked() >= OutObj->GetMaxBeAttacked())
			{
				return false;
			}
			return true;
		}

	}

	
	return false;
}

//投げられる行動
bool SiroboThrowJudgement::Judgement()
{
	return true;

}

//戦闘モード判定処理
bool SiroboBattleJudgement::Judgement()
{
	if (siroboOwner->GetAttackStandBy())
	{
		return true;
	}
	return false;
}

//死亡判定処理
bool SiroboDieJudgement::Judgement()
{
	if (siroboOwner->GetHp()<=0)
	{
		return true;
	}
	return false;
}

// 蘇生されている時の判定処理
bool SiroboResuscitationJudgement::Judgement()
{
	//蘇生されている時状態なら
	if (siroboOwner->GetState()==Sirobo::StateType::TYPE_RESUSCITATION)
	{
		return true;
	}
	return false;
}