#include "ActionBase.h"
#include "MinionPlayer.h"

//もし目標物が消えてしまった場合
ActionBase::State ActionBase::DeleteTarget()
{
	return State::FAILED;
}

//もしターゲットがいなくなっていたら
bool ActionBase::CheakTarget(Charactor* chara)
{
	if (chara == nullptr)
	{
		return (DeleteTarget() == State::FAILED) ? true:false;
	}
	return false;
}
