#pragma once
#include "JudgementBase.h"
class Sirobo;
//行動処理判定基底クラス
class  SiroboJudgementBase:public JudgementBase
{
public:
	SiroboJudgementBase() {};
	SiroboJudgementBase(Sirobo* sirobo) :siroboOwner(sirobo) {};

	//実行処理
	virtual bool Judgement() = 0;

protected:
	Sirobo* siroboOwner = nullptr;
};

