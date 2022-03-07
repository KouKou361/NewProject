#pragma once
#include "MinionJudgementBase.h"

class EnemyBase;


//待機行動
class MinionIdleJudgement :public MinionJudgementBase
{
public:
	MinionIdleJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//判定処理
	bool Judgement();
};


// 仲間行動開始
class MinionFollowJudgement : public MinionJudgementBase
{
public:
	MinionFollowJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//判定処理
	bool Judgement();
};

//ついていく　攻撃OK
class MinionBackJudgement : public MinionJudgementBase
{
public:
	MinionBackJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//判定処理
	bool Judgement();
};

//ついていく　攻撃OK
class MinionStandByJudgement : public MinionJudgementBase
{
public:
	MinionStandByJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//判定処理
	bool Judgement();
};



// 追跡行動
class MinionPursuitJudgement : public MinionJudgementBase
{
public:
	MinionPursuitJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//判定処理
	bool Judgement();
};

// 攻撃行動
class MinionAttackJudgement : public MinionJudgementBase
{
public:
	MinionAttackJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//判定処理
	bool Judgement();
};

// 投げられる行動
class MinionThrowJudgement : public MinionJudgementBase
{
public:
	MinionThrowJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//判定処理
	bool Judgement();
};

// 投げられる行動
class MinionBattleJudgement : public MinionJudgementBase
{
public:
	MinionBattleJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//判定処理
	bool Judgement();
};

//死亡判定
class MinionDieJudgement : public MinionJudgementBase
{
public:
	MinionDieJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//判定処理
	bool Judgement();
};


// 蘇生されている時の判定処理
class MinionResuscitationJudgement : public MinionJudgementBase
{
public:
	MinionResuscitationJudgement(MinionPlayer* minion) :MinionJudgementBase(minion) {}
	//判定処理
	bool Judgement();
};





