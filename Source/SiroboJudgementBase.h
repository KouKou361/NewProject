#pragma once
#include "JudgementBase.h"
class Sirobo;
//�s������������N���X
class  SiroboJudgementBase:public JudgementBase
{
public:
	SiroboJudgementBase() {};
	SiroboJudgementBase(Sirobo* sirobo) :siroboOwner(sirobo) {};

	//���s����
	virtual bool Judgement() = 0;

protected:
	Sirobo* siroboOwner = nullptr;
};

