#pragma once
#include <string>
#include <vector>
#include <memory>
#include "BehaviorTree.h"
#include "ActionBase.h"
#include "JudgementBase.h"

using namespace std;


class NodeBase
{
protected:

	string                   name;	//�m�[�h�̖��O
	BehaviorTree::SelectRule selectRule;//�m�[�h�̑I�����[��
	NodeBase* parent = nullptr;//�e�m�[�h

	unique_ptr<ActionBase>   action = nullptr;//���s����
	unique_ptr<JudgementBase> judgement = nullptr;//���菈��
	NodeBase* sibling = nullptr;		// �Z��m�[�h

	unsigned int			 priority;		// �D�揇��
	int						 hierarchyNo;	// �K�w�ԍ�
	bool                     oldSelect = true;     //�ߋ��ɑI�����ꂽ���ǂ���
public:
	NodeBase() {};
	 //�R���X�g���N�^
	NodeBase(std::string name, NodeBase* parent, NodeBase* sibling, int priority,
		BehaviorTree::SelectRule selectRule, JudgementBase* judgment, ActionBase* action, int hierarchyNo, bool OnOff = true) :
		name(name), parent(parent), sibling(sibling), priority(priority),
		selectRule(selectRule), hierarchyNo(hierarchyNo), 
		children(NULL), oldSelect(OnOff)
	{
		this->judgement.reset(judgment);
		this->action.reset(action);
	}
	// �f�X�g���N�^
	~NodeBase() {};
	// ���O�Q�b�^�[
	std::string GetName() { return name; }
	// �e�m�[�h�Q�b�^�[
	NodeBase* GetParent() { return parent; }
	// �q�m�[�h�Q�b�^�[
	NodeBase* GetChild(int index) { return children.at(index).get(); };
	// �Z��m�[�h�Q�b�^�[
	NodeBase* GetSibling() { return sibling; }
	// �m�[�h����
	NodeBase* SearchNode(std::string searchName);
	// �K�w�ԍ��Q�b�^�[
	int GetHirerchyNo() { return hierarchyNo; }
	// �D�揇�ʃQ�b�^�[
	int GetPriority() { return priority; }
	// �q�m�[�h�ǉ�
	void AddChild(shared_ptr<NodeBase> child) { children.push_back(child); }

	std::vector<shared_ptr<NodeBase>>   children;// �q�m�[�h
		//�m�[�h���_
	NodeBase* Inference(BehaviorData* data);
	//�m�[�h�̃A�N�V����
	ActionBase::State Run(Charactor* enemy);

	//�A�N�V�����J�n����
	void NodeActionStart() { action->Start(); }
	//�A�N�V�����I������
	void NodeActionEnd() { action->End(); }
	//Debug�pImGui
	void ImguiDebug() { if (action)action->DebugImgui(); };
	//Debug�pRender
	void RenderDebug() { if (action)action->DebugImgui(); };


private:
	//�����_���Ɉ�I������
	NodeBase* SelectRandom(std::vector<NodeBase*> *list);
	//�D�揇�ʂőI������
	NodeBase* SelectPriority(std::vector<NodeBase*> *list);
	//�V�[�P���X
	NodeBase* SelectSequence(std::vector<NodeBase*>* list, BehaviorData* data);
	//ONOFF�I��
	NodeBase* SelectOnOff(std::vector<NodeBase*>* list);



};