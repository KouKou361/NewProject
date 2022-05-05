#include "BehaviorTree.h"
#include "NodeBase.h"
#include "JudgementBase.h"
#include "BehaviorData.h"
#include "EnemyBase.h"

BehaviorTree::BehaviorTree()
{
}
//�m�[�h�̒ǉ�
void BehaviorTree::AddNode(std::string searchName, std::string entryName, int priority, SelectRule selectRule, JudgementBase* judgment, ActionBase* action,bool OnOff)
{
	if (searchName != "")
	{
		NodeBase* serchNode = root->SearchNode(searchName);

		if (serchNode != NULL)
		{
			//�Z���NodeBase�̎Z�o
			NodeBase* sibling = root->SearchNode(searchName);
			shared_ptr<NodeBase> addNode = make_shared<NodeBase>(entryName, serchNode, sibling, priority, selectRule, judgment, action, 0, OnOff);
			serchNode->AddChild(addNode);
		}
	}
	else
	{
		if (root == nullptr)
		{
			//�ŏ��̃m�[�h
			root = make_shared<NodeBase>(entryName, nullptr, nullptr, priority, selectRule, judgment, action, 0);
		}
		
	}
}
// ���s�m�[�h�𐄘_����
NodeBase* BehaviorTree::ActiveNodeInference(Charactor* enemy, BehaviorData* data)
{
	data->Init();
	return root->Inference(data);
}
NodeBase* BehaviorTree::Run(Charactor* enemy, NodeBase* actionNode, BehaviorData* data)
{
	
	ActionBase::State state = actionNode->Run(enemy);


	// ����I��
	if (state == ActionBase::State::COMPLETE)
	{
		// �V�[�P���X�̓r�����𔻒f
		NodeBase* sequenceNode = data->PopSequenceNode();

		// �r������Ȃ��Ȃ�I��
		if (sequenceNode == NULL)
		{
			return NULL;
		}
		else {
			// �r���Ȃ炻������n�߂�

			actionNode->NodeActionEnd();
			return SequenceBack(sequenceNode, enemy, data);
		}
		// ���s�͏I��
	}
	//���s���s
	else if (state == ActionBase::State::FAILED
		) {
		//���s�I������
		actionNode->NodeActionEnd();
		return NULL;
	}

	// ����ێ�
	return actionNode;
}
// �m�[�h�S�폜
void BehaviorTree::NodeAllClear(NodeBase* delNode)
{
	for (shared_ptr<NodeBase> node : delNode->children)
	{
		NodeAllClear(node.get());
	}
	delNode->children.clear();

}

// �V�[�P���X�m�[�h����̐��_�J�n
NodeBase* BehaviorTree::SequenceBack(NodeBase* sequenceNode, Charactor* enemy, BehaviorData* data)
{
	return sequenceNode->Inference(data);
}
