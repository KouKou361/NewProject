#include "SiroboActionBase.h"
#include "SiroboPlayer.h"
//‚à‚µ–Ú•W•¨‚ªÁ‚¦‚Ä‚µ‚Ü‚Á‚½ê‡
ActionBase::State SiroboActionBase::DeleteTarget()
{
	//s“®‚Ì•ÏX
	siroboOwner->ResetNode();
	return ActionBase::State::FAILED;
}