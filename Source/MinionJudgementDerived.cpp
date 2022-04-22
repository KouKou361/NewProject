#include "MinionJudgementDerived.h"
#include "MinionPlayer.h"
#include "Player.h"
#include "EnemyManager.h"
#include "ObjectBase.h"
#include "ObjectManager.h"

//�ҋ@���菈��
bool MinionIdleJudgement::Judgement()
{
	//��������TRUE
	return true;
}

//���Ԕ��菈��
bool MinionFollowJudgement::Judgement()
{
	//�~�j�I�����v���C���[�̖����Ȃ�
	if (minionOwner->GetTeam() == minionOwner->Team::TEAM_PLAYER)
	{
		return true;
	}
	return false;
}
bool MinionBackJudgement::Judgement()
{
	//�����v���C���[�̌��߂�ꂽ�͈͊O�Ȃ�
	if (!minionOwner->SearchPosition(minionOwner->StandBySerchL, minionOwner->GetPlayer()->GetPos()))
	{
		return true;
	}
	return false;
}

//���Ă����@�U��OK���菈��
bool MinionStandByJudgement::Judgement()
{
	//�����v���C���[�̌��߂�ꂽ�͈͂Ȃ�
	if (minionOwner->SearchPosition(minionOwner->StandBySerchL, minionOwner->GetPlayer()->GetPos()))
	{
		return true;
	}
	return false;
}


//�ǐՔ��菈��
bool MinionPursuitJudgement::Judgement()
{
	return true;
}

//�U�����菈��
bool MinionAttackJudgement::Judgement()
{

	VECTOR3 OutPos;

	//�G�Ƃ̓����蔻��
	{
		EnemyBase* OutEnm = nullptr;

		if (minionOwner->GetManager()->GetEnemyManager()->CollisionEnemy(
			minionOwner->GetPos(),
			minionOwner->GetWeight(),
			minionOwner->GetCollisionRadius(),
			OutPos, OutEnm)
			)
		{
			//�����G�́u�~�j�I�����U���ł���ő吔�v�ɒB���Ă���Ȃ�
			if (OutEnm->GetNumBeAttacked() >= OutEnm->GetMaxBeAttacked())
			{
				return false;
			}
			return true;
		}

	}

	//Object�Ƃ̓����蔻��
	{
		ObjectBase* OutObj = nullptr;

		if (minionOwner->GetManager()->GetObjectManager()->CollisionObject(
			minionOwner->GetPos(),
			minionOwner->GetWeight(),
			minionOwner->GetCollisionRadius(),
			OutPos, OutObj)
			)
		{
			//�����G�́u�~�j�I�����U���ł���ő吔�v�ɒB���Ă���Ȃ�
			if (OutObj->GetNumBeAttacked() >= OutObj->GetMaxBeAttacked())
			{
				return false;
			}
			return true;
		}

	}

	
	return false;
}

//��������s��
bool MinionThrowJudgement::Judgement()
{
	return true;

}

//�퓬���[�h���菈��
bool MinionBattleJudgement::Judgement()
{
	if (minionOwner->GetAttackStandBy())
	{
		return true;
	}
	return false;
}

//���S���菈��
bool MinionDieJudgement::Judgement()
{
	if (minionOwner->GetHp()<=0)
	{
		return true;
	}
	return false;
}

// �h������Ă��鎞�̔��菈��
bool MinionResuscitationJudgement::Judgement()
{
	//�h������Ă��鎞��ԂȂ�
	if (minionOwner->GetState()==MinionPlayer::StateType::TYPE_RESUSCITATION)
	{
		return true;
	}
	return false;
}