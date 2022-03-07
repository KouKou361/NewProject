#pragma once
#include "MinionJudgementBase.h"

class EnemyBase;


//�ҋ@�s��
class MinionIdleJudgement :public MinionJudgementBase
{
public:
	MinionIdleJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//���菈��
	bool Judgement();
};


// ���ԍs���J�n
class MinionFollowJudgement : public MinionJudgementBase
{
public:
	MinionFollowJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//���菈��
	bool Judgement();
};

//���Ă����@�U��OK
class MinionBackJudgement : public MinionJudgementBase
{
public:
	MinionBackJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//���菈��
	bool Judgement();
};

//���Ă����@�U��OK
class MinionStandByJudgement : public MinionJudgementBase
{
public:
	MinionStandByJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//���菈��
	bool Judgement();
};



// �ǐՍs��
class MinionPursuitJudgement : public MinionJudgementBase
{
public:
	MinionPursuitJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//���菈��
	bool Judgement();
};

// �U���s��
class MinionAttackJudgement : public MinionJudgementBase
{
public:
	MinionAttackJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//���菈��
	bool Judgement();
};

// ��������s��
class MinionThrowJudgement : public MinionJudgementBase
{
public:
	MinionThrowJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//���菈��
	bool Judgement();
};

// ��������s��
class MinionBattleJudgement : public MinionJudgementBase
{
public:
	MinionBattleJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//���菈��
	bool Judgement();
};

//���S����
class MinionDieJudgement : public MinionJudgementBase
{
public:
	MinionDieJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//���菈��
	bool Judgement();
};


// �h������Ă��鎞�̔��菈��
class MinionResuscitationJudgement : public MinionJudgementBase
{
public:
	MinionResuscitationJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//���菈��
	bool Judgement();
};





