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
		NONE,
		PRIORITY,//�D�揇��
		SEQUENCE,//�V�[�P���X
		SEQUETIAL_LOOPING,
		RANDOM,//�����_��
		ON_OFF,//ON,OFF

	};
public:
	BehaviorTree();
	virtual ~BehaviorTree() {};

	//�m�[�h�̒ǉ�
	void AddNode(const std::string searchName, const std::string entryName, const int priority, const SelectRule selectRule, JudgementBase* judgment, ActionBase* action, const bool onOff=false);
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
