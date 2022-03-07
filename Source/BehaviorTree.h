#pragma once

#include <string>
#include <memory>


using namespace std;

class Charactor;
class NodeBase;
class BehaviorData;
class JudgementBase;
class ActionBase;

//�����p
class BehaviorTree
{
public:
	//�I�����[��
	enum class SelectRule
	{
		Non,
		Priority,//�D�揇��
		Sequence,//�V�[�P���X
		SequentialLooping,
		Random,//�����_��
		OnOff,//ON,OFF

	};
public:
	BehaviorTree();
	virtual ~BehaviorTree() {};

	//�m�[�h�̒ǉ�
	void AddNode(std::string searchName, std::string entryName, int priority, SelectRule selectRule, JudgementBase* judgment, ActionBase* action, bool OnOff=false);
	// ���s�m�[�h�𐄘_����
	NodeBase* ActiveNodeInference(Charactor* enemy, BehaviorData* data);
	//���s
	NodeBase* Run(Charactor* enemy,NodeBase* actionNode, BehaviorData* data);


private:
	// �m�[�h�S�폜
	void NodeAllClear(NodeBase* delNode);

	NodeBase* SequenceBack(NodeBase* sequenceNode, Charactor* enemy, BehaviorData* data);
private:
	// ���[�g�m�[�h
	std::shared_ptr<NodeBase> root;
};
