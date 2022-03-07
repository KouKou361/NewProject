#pragma once

#include <vector>
#include <stack>
#include <map>
#include "BehaviorTree.h"

class NodeBase;

// Behavior�ۑ��f�[�^
class BehaviorData
{
public:
	// �R���X�g���N�^
	BehaviorData() { Init(); }
	// �V�[�P���X�m�[�h�̃v�b�V��
	void PushSequenceNode(NodeBase* node) { sequenceStack.push(node); }
	// �V�[�P���X�m�[�h�̃|�b�v
	NodeBase* PopSequenceNode();
	// �V�[�P���X�X�e�b�v�̃Q�b�^�[
	int GetSequenceStep(std::string name);
	// �V�[�P���X�X�e�b�v�̃Z�b�^�[
	void SetSequenceStep(std::string name, int step);
	// ������
	void Init();
private:
	// �V�[�P���X�m�[�h�X�^�b�N
	std::stack<NodeBase*> sequenceStack;				
	// ���s�V�[�P���X�̃X�e�b�v�}�b�v
	std::map<std::string, int> runSequenceStepMap;		
};

