#include "ActionBase.h"
#include "SiroboPlayer.h"

//�����ڕW���������Ă��܂����ꍇ
ActionBase::State ActionBase::DeleteTarget()
{
	return State::FAILED;
}

//�����^�[�Q�b�g�����Ȃ��Ȃ��Ă��邩�ǂ���
bool ActionBase::CheakTarget(const Charactor* chara)
{
	if (chara == nullptr)
	{
		return (DeleteTarget() == State::FAILED) ? true:false;
	}
	return false;
}
