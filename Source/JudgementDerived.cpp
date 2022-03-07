#include "JudgementDerived.h"
#include "EnemyBase.h"
//�ҋ@���菈��
bool IdleJudgement::Judgement()
{
	//��������TRUE
	return true;
}

//�ǐՔ��菈��
bool PursuitJudgement::Judgement()
{
	//�����U������Ă�����������Ȃ�
	if (owner->GetOldDamageFlg())return true;
	//���G���ɂ����true��Ԃ�
	if (owner->SearchTarget(owner->GetSearchL()))
	{
		return true;
	}
	return false;
}

//�U�����菈��
bool AttackJudgement::Judgement()
{
	if (owner->SearchTarget(owner->GetAttackL()))
	{
		return true;
	}
	return false;
}
//�_���[�W���菈��
bool DamageJudgement::Judgement()
{
	return owner->GetDamageFlg();
}

//���S���菈��
bool DeadJudgement::Judgement()
{
	return owner->GetDeadFlg();
}

//��]�U�����菈��
bool BossRollAttackJudgement::Judgement()
{
	return true;
}