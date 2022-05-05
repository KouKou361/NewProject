#include "ActionBase.h"
#include "SiroboPlayer.h"

//もし目標物が消えてしまった場合
ActionBase::State ActionBase::DeleteTarget()
{
	return State::FAILED;
}

//もしターゲットがいなくなっているかどうか
bool ActionBase::CheakTarget(const Charactor* chara)
{
	if (chara == nullptr)
	{
		return (DeleteTarget() == State::FAILED) ? true:false;
	}
	return false;
}
