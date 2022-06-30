#pragma once
#include "SiroboJudgementBase.h"

class EnemyBase;


//�ҋ@�s��
class SiroboIdleJudgement :public SiroboJudgementBase
{
public:
	SiroboIdleJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};


// ���ԍs���J�n
class SiroboAlliesJudgement : public SiroboJudgementBase
{
public:
	SiroboAlliesJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};


//�v���C���[�̌��ɂ��Ă���
class SiroboFollowJudgement : public SiroboJudgementBase
{
public:
	SiroboFollowJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};


//���Ă����@�U��OK
class SiroboBackJudgement : public SiroboJudgementBase
{
public:
	SiroboBackJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};

//���Ă����@�U��OK
class SiroboStandByJudgement : public SiroboJudgementBase
{
public:
	SiroboStandByJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};


// �ǐՍs��
class SiroboPursuitJudgement : public SiroboJudgementBase
{
public:
	SiroboPursuitJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};

// �U���s��
class SiroboAttackJudgement : public SiroboJudgementBase
{
public:
	SiroboAttackJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};

// ��������s��
class SiroboThrowJudgement : public SiroboJudgementBase
{
public:
	SiroboThrowJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};

// ��������s��
class SiroboBattleJudgement : public SiroboJudgementBase
{
public:
	SiroboBattleJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};

//���S����
class SiroboDieJudgement : public SiroboJudgementBase
{
public:
	SiroboDieJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};


// �h������Ă��鎞�̔��菈��
class SiroboResuscitationJudgement : public SiroboJudgementBase
{
public:
	SiroboResuscitationJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//���菈��
	bool Judgement();
};





