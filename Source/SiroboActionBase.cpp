#include "SiroboActionBase.h"
#include "SiroboPlayer.h"
//もし目標物が消えてしまった場合
ActionBase::State SiroboActionBase::DeleteTarget()
{
	//行動の変更
	siroboOwner->ResetNode();
	return ActionBase::State::FAILED;
}