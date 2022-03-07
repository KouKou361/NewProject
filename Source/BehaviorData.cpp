#include "BehaviorData.h"
#include "NodeBase.h"
#include "JudgementBase.h"
#include "ActionBase.h"

// �V�[�P���X�m�[�h�̃|�b�v
NodeBase* BehaviorData::PopSequenceNode()
{
	//�V�[�P���X�m�[�h�f�[�^�̎��o��

	// ��Ȃ�NULL
	if (sequenceStack.empty() != 0)
	{
		return NULL;
	}
	NodeBase* node = sequenceStack.top();
	if (node != NULL)
	{
		// ���o�����f�[�^���폜
		sequenceStack.pop();
	}
	return node;
}

// �V�[�P���X�X�e�b�v�̃Q�b�^�[
int BehaviorData::GetSequenceStep(std::string name)
{
	if (runSequenceStepMap.count(name) == 0)
	{
		//		runSequenceStepMap.at(name) = 0;

		runSequenceStepMap.insert(std::make_pair(name, 0));
	}

	return runSequenceStepMap.at(name);
}

// �V�[�P���X�X�e�b�v�̃Z�b�^�[
void BehaviorData::SetSequenceStep(std::string name, int step)
{
	runSequenceStepMap.at(name) = step;
}

// ������
void BehaviorData::Init()
{
	runSequenceStepMap.clear();
	while (sequenceStack.size() > 0)
	{
		sequenceStack.pop();
	}
}