#include "NodeBase.h"
#include "BehaviorData.h"
#include "EnemyBase.h"
#include <assert.h>

// �m�[�h����
NodeBase* NodeBase::SearchNode(std::string searchName)
{
	if (name == searchName)return this;

	//�ꉞ�@�q���N���X�ł�������������
	for (int i = 0; i < children.size(); i++)
	{
		NodeBase* child = GetChild(i)->SearchNode(searchName);

		if (child == nullptr)continue;

		if (child->name == searchName)
		{
			return child;
		}
	}

	assert("�����Ƀq�b�g���Ȃ�����");
	return nullptr;
}

//�m�[�h�̃A�N�V����
ActionBase::State NodeBase::Run(Charactor* enemy)
{
	if (enemy)
	{
		//�����^�[�Q�b�g�����Ȃ��Ȃ��Ă�����
		if (enemy->GetTarget() == nullptr)
		{
			return action->DeleteTarget();
		}


		return action->Run();
	}
	
		//���̍s���Ɉڍs�I
	else 	return ActionBase::State::FAILED;
}

//�m�[�h���_
NodeBase* NodeBase::Inference(BehaviorData* data)
{
	
	std::vector<NodeBase*> list;
	list.clear();
	NodeBase* result = nullptr;

	
	//�q�m�[�h�Ŏ��s�\�ȃm�[�h��T��
	
	
	for (int i = 0; i < children.size(); i++)
	{
		if (children.at(i)->judgement != nullptr)
		{
			if (children.at(i)->judgement->Judgement())
			{
				list.emplace_back(children.at(i).get());
			}
		}
		else {
			// ����N���X���Ȃ���Ζ������ɒǉ�
			list.emplace_back(children.at(i).get());
		}
	}

	//���[���̕���
	switch (selectRule)
	{
		//�D�揇��
	case BehaviorTree::SelectRule::PRIORITY:
		result=SelectPriority(&list);
		break;
		//�����_��
	case BehaviorTree::SelectRule::RANDOM:
		result = SelectRandom(&list);
		break;
		//�V�[�P���X
	case BehaviorTree::SelectRule::SEQUENCE:
		result = SelectSequence(&list, data);
		break;
		//ONOFF
	case BehaviorTree::SelectRule::ON_OFF:
		result = SelectOnOff(&list);
		break;
	}
	if (result!=nullptr)
	{
		//�s��������Ȃ�I������
		if (result->action != nullptr)
		{
			//�s���J�n����
			result->NodeActionStart();
			return result;
		}
		else
		{
			return result = result->Inference(data);
		}



	}
	return result;

}
//�m�[�h�̃A�N�V����
//bool NodeBase::Run()
//{
//	ActionBase::State state=
//}
//�����_���Ɉ�I������
NodeBase* NodeBase::SelectRandom(std::vector<NodeBase*> *list)
{
	int rnd = rand() % list->size();
	return list->at(rnd);
}
//�D�揇�ʂőI������
NodeBase* NodeBase::SelectPriority(std::vector<NodeBase*> *list)
{
	int MaxPriority = INT_MAX;
	NodeBase* SelectNode=nullptr;

	for (int i = 0; i < list->size(); i++)
	{
		if (MaxPriority >= list->at(i)->GetPriority())
		{
			SelectNode=list->at(i);
			MaxPriority = list->at(i)->GetPriority();
		}
		
	}
	return SelectNode;
}

// �V�[�P���X
NodeBase* NodeBase::SelectSequence(std::vector<NodeBase*>* list, BehaviorData* data)
{
	
	int step = 0;
	step = data->GetSequenceStep(GetName());

	if (step >= (int)children.size())
	{
		if (selectRule == BehaviorTree::SelectRule::SEQUETIAL_LOOPING)step = 0;
		else return NULL;
		
	}


	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
	
		if (children.at(step)->GetName() == (*itr)->GetName())
		{

		
			data->PushSequenceNode(this);
		
			data->SetSequenceStep(GetName(), step + 1);

			return children.at(step).get();
		}
	}

	return NULL;
}

//��x���I�����ꂽ���Ƃ��Ȃ��ꍇ�@�����I������
//���������ׂĈ�ʂ�I�����ꂽ���Ƃ�����Ȃ�SelectPriority()�őI������B
NodeBase* NodeBase::SelectOnOff(std::vector<NodeBase*>* list)
{
	int MaxPriority = INT_MAX;
	NodeBase* SelectNode = nullptr;

	for (int i = 0; i < list->size(); i++)
	{
		//�I�����ꂽ���Ƃ��Ȃ��ꍇ
		if (list->at(i)->oldSelect==false)
		{
			list->at(i)->oldSelect = true;
			return list->at(i);
		}


		if (MaxPriority >= list->at(i)->GetPriority())
		{
			SelectNode = list->at(i);
			MaxPriority = list->at(i)->GetPriority();
		}

	}
	return SelectNode;
}
