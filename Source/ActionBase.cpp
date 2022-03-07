#include "ActionBase.h"
#include "MinionPlayer.h"

//もし目標物が消えてしまった場合
ActionBase::State ActionBase::DeleteTarget()
{
	return State::Failed;
}

//もしターゲットがいなくなっていたら
bool ActionBase::CheakTarget(Charactor* chara)
{
	if (chara == nullptr)
	{
		return (DeleteTarget() == State::Failed) ? true:false;
	}
}
