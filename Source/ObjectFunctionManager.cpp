#include "ObjectFunctionManager.h"
//����������
void ObjectFunctionManager::Init()
{
	Clear();
}
//�X�V����
void ObjectFunctionManager::Update()
{
	for (int i=0;i< objectFunctiones.size();i++)
	{
		shared_ptr<ObjectFunctionBase> obj = objectFunctiones.at(i);
		if (obj)
		{
			obj->Update();

			obj->Judge();

			if (obj->GetIsFunction() == IsFunction::IS_TRUE)
			{
				if (obj->GetState()!= ObjectFunctionState::STATE_RUN)
				{
					obj->SetState(ObjectFunctionState::STATE_START);
				}

				switch (obj->GetState())
				{
				case ObjectFunctionState::STATE_START:obj->Start();
					obj->SetState(ObjectFunctionState::STATE_RUN);
					break;
				case ObjectFunctionState::STATE_RUN:obj->Run();
					break;
				case ObjectFunctionState::STATE_END:
				case ObjectFunctionState::STATE_NONE:
					break;
				}
			}
			//����Function���Ă΂�Ȃ��Ȃ�
			else
			{
				if (obj->GetState() != ObjectFunctionState::STATE_NONE)
				{
					//�I������
					obj->End();
					obj->SetState(ObjectFunctionState::STATE_NONE);
				}

			}

		
		}
	
	}

	//�j������
    //�X�V�������I�������ɔj�����X�g�ɐς܂ꂽ�I�u�W�F�N�g���폜����B
	for (shared_ptr<ObjectFunctionBase> obj : remove)
	{
		//std::vector����v�f��j������ꍇ�̓C���e�[�^�[�ō폜���Ȃ���΂Ȃ�Ȃ�
		std::vector<shared_ptr<ObjectFunctionBase>>::iterator it = std::find(objectFunctiones.begin(), objectFunctiones.end(), obj);
		if (it != objectFunctiones.end())
		{
			objectFunctiones.erase(it);
		}
	}
	remove.clear();
}
//�S�폜
void ObjectFunctionManager::Clear()
{
	objectFunctiones.clear();
	remove.clear();
}
//�o�^
void ObjectFunctionManager::Register(shared_ptr<ObjectFunctionBase> objectFunction)
{
	objectFunction->Init();
	objectFunctiones.emplace_back(objectFunction);
}
//�j������
void ObjectFunctionManager::Destroy(ObjectFunctionBase* objectFunction)
{
	remove.emplace_back(objectFunction);
}
//�����蔻��f�o�b�O
void ObjectFunctionManager::CollisionDebug()
{
	for (int i = 0; i < GetobjectFunctionesSize(); i++)
	{
		ObjectFunctionBase* objFunction = GetobjectFunctionesIndex(i);
		objFunction->CollisionRender();
	}
}