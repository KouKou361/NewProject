#pragma once
#include "SiroboJudgementBase.h"

class EnemyBase;


//待機行動
class SiroboIdleJudgement :public SiroboJudgementBase
{
public:
	SiroboIdleJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};


// 仲間行動開始
class SiroboAlliesJudgement : public SiroboJudgementBase
{
public:
	SiroboAlliesJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};


//プレイヤーの後ろについていく
class SiroboFollowJudgement : public SiroboJudgementBase
{
public:
	SiroboFollowJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};


//ついていく　攻撃OK
class SiroboBackJudgement : public SiroboJudgementBase
{
public:
	SiroboBackJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};

//ついていく　攻撃OK
class SiroboStandByJudgement : public SiroboJudgementBase
{
public:
	SiroboStandByJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};


// 追跡行動
class SiroboPursuitJudgement : public SiroboJudgementBase
{
public:
	SiroboPursuitJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};

// 攻撃行動
class SiroboAttackJudgement : public SiroboJudgementBase
{
public:
	SiroboAttackJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};

// 投げられる行動
class SiroboThrowJudgement : public SiroboJudgementBase
{
public:
	SiroboThrowJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};

// 投げられる行動
class SiroboBattleJudgement : public SiroboJudgementBase
{
public:
	SiroboBattleJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};

//死亡判定
class SiroboDieJudgement : public SiroboJudgementBase
{
public:
	SiroboDieJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};


// 蘇生されている時の判定処理
class SiroboResuscitationJudgement : public SiroboJudgementBase
{
public:
	SiroboResuscitationJudgement(Sirobo* sirobo) :SiroboJudgementBase(sirobo) {}
	//判定処理
	bool Judgement();
};





