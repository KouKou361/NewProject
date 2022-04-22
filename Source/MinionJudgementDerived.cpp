#include "MinionJudgementDerived.h"
#include "MinionPlayer.h"
#include "Player.h"
#include "EnemyManager.h"
#include "ObjectBase.h"
#include "ObjectManager.h"

//待機判定処理
bool MinionIdleJudgement::Judgement()
{
	//無条件でTRUE
	return true;
}

//仲間判定処理
bool MinionFollowJudgement::Judgement()
{
	//ミニオンがプレイヤーの味方なら
	if (minionOwner->GetTeam() == minionOwner->Team::TEAM_PLAYER)
	{
		return true;
	}
	return false;
}
bool MinionBackJudgement::Judgement()
{
	//もしプレイヤーの決められた範囲外なら
	if (!minionOwner->SearchPosition(minionOwner->StandBySerchL, minionOwner->GetPlayer()->GetPos()))
	{
		return true;
	}
	return false;
}

//ついていく　攻撃OK判定処理
bool MinionStandByJudgement::Judgement()
{
	//もしプレイヤーの決められた範囲なら
	if (minionOwner->SearchPosition(minionOwner->StandBySerchL, minionOwner->GetPlayer()->GetPos()))
	{
		return true;
	}
	return false;
}


//追跡判定処理
bool MinionPursuitJudgement::Judgement()
{
	return true;
}

//攻撃判定処理
bool MinionAttackJudgement::Judgement()
{

	VECTOR3 OutPos;

	//敵との当たり判定
	{
		EnemyBase* OutEnm = nullptr;

		if (minionOwner->GetManager()->GetEnemyManager()->CollisionEnemy(
			minionOwner->GetPos(),
			minionOwner->GetWeight(),
			minionOwner->GetCollisionRadius(),
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

		if (minionOwner->GetManager()->GetObjectManager()->CollisionObject(
			minionOwner->GetPos(),
			minionOwner->GetWeight(),
			minionOwner->GetCollisionRadius(),
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
bool MinionThrowJudgement::Judgement()
{
	return true;

}

//戦闘モード判定処理
bool MinionBattleJudgement::Judgement()
{
	if (minionOwner->GetAttackStandBy())
	{
		return true;
	}
	return false;
}

//死亡判定処理
bool MinionDieJudgement::Judgement()
{
	if (minionOwner->GetHp()<=0)
	{
		return true;
	}
	return false;
}

// 蘇生されている時の判定処理
bool MinionResuscitationJudgement::Judgement()
{
	//蘇生されている時状態なら
	if (minionOwner->GetState()==MinionPlayer::StateType::TYPE_RESUSCITATION)
	{
		return true;
	}
	return false;
}