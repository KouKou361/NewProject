#pragma once
#include "JudgementBase.h"
class MinionPlayer;
//行動処理判定基底クラス
class  MinionJudgementBase:public JudgementBase
{
public:
	MinionJudgementBase() {};
	MinionJudgementBase(MinionPlayer* minion) :minionOwner(minion) {};

	//実行処理
	virtual bool Judgement() = 0;

protected:
	MinionPlayer* minionOwner = nullptr;
};

