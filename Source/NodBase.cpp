#include "NodeBase.h"
#include "BehaviorData.h"
#include "EnemyBase.h"
#include <assert.h>

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
	
		
	else 	return ActionBase::State::Failed;
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
	case BehaviorTree::SelectRule::Priority:
		result=SelectPriority(&list);
		break;
		//�����_��
	case BehaviorTree::SelectRule::Random:
		result = SelectRandom(&list);
		break;
		//�V�[�P���X
	case BehaviorTree::SelectRule::Sequence:
		result = SelectSequence(&list, data);
		break;
		//ONOFF
	case BehaviorTree::SelectRule::OnOff:
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
	// �V�[�P���X�����Ńm�[�h���w�肷��R�[�h�������ōl���ĕ⊮���Ă��������B
	// �q���g�Ƃ��Ď菇���L�ڂ��Ă��܂��B
	// �菇�@�F���݂̃m�[�h�̃V�[�P���X�̃X�e�b�v���擾
	//		   �X�e�b�v��int�^�A�V�[�P���X�X�e�b�v�̎擾�ɂ�data->GetSequenceStep()���g�p���邱��
	int step = 0;
	step = data->GetSequenceStep(GetName());

	// �菇�@�Ŏ擾�����X�e�b�v�����q�m�[�h���𒴂��Ă��邩
	if (step >= (int)children.size())
	{
		if (selectRule == BehaviorTree::SelectRule::SequentialLooping)step = 0;
		else return NULL;
		// �菇�A�FselectRule��SEQUENTIAL_LOOPING�̏ꍇ�Astep��0����
		// 		  ����ȊO��NULL�����^�[�����Ȃ���
	}

	// �Bstep�ԍ��̃m�[�h������
	for (auto itr = list->begin(); itr != list->end(); itr++)
	{
		//���g�̎q�m�[�h��step�Ԗڂ̃m�[�h���A���݂̎��s�\�m�[�h�ɂ��邩����
		if (children.at(step)->GetName() == (*itr)->GetName())
		{

			// �C�����������ʁA�Y���f�[�^������Ύ��g��data��sequenceStack�ɒǉ�
			data->PushSequenceNode(this);
			// �Ddata->setSequenceStep��getName()�̃L�[�f�[�^�ɃX�e�b�v�{�P���Z�b�g����
			data->SetSequenceStep(GetName(), step + 1);
			// �E���g�̎q�m�[�h��step�Ԗڂ̃m�[�h�����^�[��
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
		if (list->at(i)->OldSelect==false)
		{
			list->at(i)->OldSelect = true;
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
