#include "MinionActionBase.h"
#include "MinionPlayer.h"
ActionBase::State MinionActionBase::DeleteTarget()
{
	minionOwner->ResetNode();
	return ActionBase::State::Failed;
}