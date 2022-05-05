#include "SiroboJudgementDerived.h"
#include "SiroboPlayer.h"
#include "Player.h"
#include "EnemyManager.h"
#include "ObjectBase.h"
#include "ObjectManager.h"

//�ҋ@���菈��
bool SiroboIdleJudgement::Judgement()
{
	//��������TRUE
	return true;
}

//���Ԕ��菈��
bool SiroboFollowJudgement::Judgement()
{
	//�~�j�I�����v���C���[�̖����Ȃ�
	if (siroboOwner->GetTeam() == static_cast<Sirobo::Team>(Sirobo::Team::TEAM_PLAYER))
	{
		return true;
	}
	return false;
}
bool SiroboBackJudgement::Judgement()
{
	//�����v���C���[�̌��߂�ꂽ�͈͊O�Ȃ�
	if (!siroboOwner->SearchPosition(siroboOwner->StandBySerchL, siroboOwner->GetPlayer()->GetPos()))
	{
		return true;
	}
	return false;
}

//���Ă����@�U��OK���菈��
bool SiroboStandByJudgement::Judgement()
{
	//�����v���C���[�̌��߂�ꂽ�͈͂Ȃ�
	if (siroboOwner->SearchPosition(siroboOwner->StandBySerchL, siroboOwner->GetPlayer()->GetPos()))
	{
		return true;
	}
	return false;
}


//�ǐՔ��菈��
bool SiroboPursuitJudgement::Judgement()
{
	return true;
}

//�U�����菈��
bool SiroboAttackJudgement::Judgement()
{

	VECTOR3 OutPos;

	//�G�Ƃ̓����蔻��
	{
		EnemyBase* OutEnm = nullptr;

		if (siroboOwner->GetManager()->GetEnemyManager()->CollisionEnemy(
			siroboOwner->GetPos(),
			siroboOwner->GetWeight(),
			siroboOwner->GetCollisionRadius(),
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

		if (siroboOwner->GetManager()->GetObjectManager()->CollisionCircleObject(
			siroboOwner->GetPos(),
			siroboOwner->GetWeight(),
			siroboOwner->GetCollisionRadius(),
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
bool SiroboThrowJudgement::Judgement()
{
	return true;

}

//�퓬���[�h���菈��
bool SiroboBattleJudgement::Judgement()
{
	if (siroboOwner->GetAttackStandBy())
	{
		return true;
	}
	return false;
}

//���S���菈��
bool SiroboDieJudgement::Judgement()
{
	if (siroboOwner->GetHp()<=0)
	{
		return true;
	}
	return false;
}

// �h������Ă��鎞�̔��菈��
bool SiroboResuscitationJudgement::Judgement()
{
	//�h������Ă��鎞��ԂȂ�
	if (siroboOwner->GetState()==Sirobo::StateType::TYPE_RESUSCITATION)
	{
		return true;
	}
	return false;
}