#include "SiroboActionBase.h"
#include "SiroboPlayer.h"
//�����ڕW���������Ă��܂����ꍇ
ActionBase::State SiroboActionBase::DeleteTarget()
{
	//�s���̕ύX
	siroboOwner->ResetNode();
	return ActionBase::State::FAILED;
}