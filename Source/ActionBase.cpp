#include "ActionBase.h"
#include "MinionPlayer.h"

//�����ڕW���������Ă��܂����ꍇ
ActionBase::State ActionBase::DeleteTarget()
{
	return State::Failed;
}

//�����^�[�Q�b�g�����Ȃ��Ȃ��Ă�����
bool ActionBase::CheakTarget(Charactor* chara)
{
	if (chara == nullptr)
	{
		return (DeleteTarget() == State::Failed) ? true:false;
	}
}
