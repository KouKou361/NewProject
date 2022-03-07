#pragma once
#include "JudgementBase.h"

class EnemyBase;


//�ҋ@�s��
class IdleJudgement :public JudgementBase
{
public:
	IdleJudgement(EnemyBase* enemy) :JudgementBase(enemy) {}
	//���s����
	bool Judgement();
};

// �ǐՍs��
class PursuitJudgement : public JudgementBase
{
public:
	PursuitJudgement(EnemyBase* enemy) :JudgementBase(enemy) {}
	//���s����
	bool Judgement();
};

// �U���s��
class AttackJudgement : public JudgementBase
{
public:
	AttackJudgement(EnemyBase* enemy) :JudgementBase(enemy) {}
	//���s����
	bool Judgement();
};

//�_���[�W�s��
class DamageJudgement : public JudgementBase
{
public:
	DamageJudgement(EnemyBase* enemy) :JudgementBase(enemy) {}
	//���s����
	bool Judgement();
};

//���S�s��
class DeadJudgement : public JudgementBase
{
public:
	DeadJudgement(EnemyBase* enemy) :JudgementBase(enemy) {}
	//���s����
	bool Judgement();
};

//Boss��p
class BossRollAttackJudgement :public JudgementBase
{
public:
	BossRollAttackJudgement(EnemyBase* enemy) :JudgementBase(enemy) {}
	//���s����
	bool Judgement();
};

//Boss��p
class BossEntryJudgement :public JudgementBase
{
public:
	BossEntryJudgement(EnemyBase* enemy) :JudgementBase(enemy) {}
	//���s����
	bool Judgement();
};





