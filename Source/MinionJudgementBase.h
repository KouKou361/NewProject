#pragma once
#include "JudgementBase.h"
class MinionPlayer;
//�s������������N���X
class  MinionJudgementBase:public JudgementBase
{
public:
	MinionJudgementBase() {};
	MinionJudgementBase(MinionPlayer* minion) :minionOwner(minion) {};

	//���s����
	virtual bool Judgement() = 0;

protected:
	MinionPlayer* minionOwner = nullptr;
};

