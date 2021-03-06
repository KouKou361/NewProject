#include "ObjectFunctionManager.h"
//初期化処理
void ObjectFunctionManager::Init()
{
	Clear();
}
//更新処理
void ObjectFunctionManager::Update()
{
	for (int i=0;i< objectFunctiones.size();i++)
	{
		shared_ptr<ObjectFunctionBase> obj = objectFunctiones.at(i);
		if (obj)
		{
			//更新処理
			obj->Update();
			//関数オブジェクトを呼ぶか決める処理
			obj->Judge();
		
			if (obj->GetIsFunction() == IsFunction::IS_TRUE)
			{
				//JudgeがTrueの場合
				FunctionIsTrue(obj.get());
			}
			else
			{
				//JudgeがFalseの場合
				FunctionIsFalse(obj.get());
			}
		}
	
	}

	//破棄処理
    //更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する。
	for (shared_ptr<ObjectFunctionBase> obj : remove)
	{
		//std::vectorから要素を破棄する場合はイレテーターで削除しなければならない
		std::vector<shared_ptr<ObjectFunctionBase>>::iterator it = std::find(objectFunctiones.begin(), objectFunctiones.end(), obj);
		if (it != objectFunctiones.end())
		{
			objectFunctiones.erase(it);
		}
	}
	remove.clear();
}
//全削除
void ObjectFunctionManager::Clear()
{
	objectFunctiones.clear();
	remove.clear();
}
//登録
void ObjectFunctionManager::Register(shared_ptr<ObjectFunctionBase> objectFunction)
{
	objectFunction->Init();
	objectFunctiones.emplace_back(objectFunction);
}
//破棄処理
void ObjectFunctionManager::Destroy(ObjectFunctionBase* objectFunction)
{
	remove.emplace_back(objectFunction);
}
//当たり判定デバッグ
void ObjectFunctionManager::CollisionDebug()
{
	for (int i = 0; i < GetobjectFunctionesSize(); i++)
	{
		ObjectFunctionBase* objFunction = GetobjectFunctionesIndex(i);
		objFunction->CollisionRender();
	}
}

//JudgeがTrueの場合
void ObjectFunctionManager::FunctionIsTrue(ObjectFunctionBase* obj)
{

	if (obj->GetState() != ObjectFunctionState::STATE_RUN)
	{
		obj->SetState(ObjectFunctionState::STATE_START);
	}

	switch (obj->GetState())
	{
	case ObjectFunctionState::STATE_START:obj->Start();
		obj->SetState(ObjectFunctionState::STATE_RUN);
		break;
	case ObjectFunctionState::STATE_RUN:
		obj->Run();
		break;
	case ObjectFunctionState::STATE_END:
		break;
	case ObjectFunctionState::STATE_NONE:
		break;
	}

}
//JudgeがFalseの場合
void ObjectFunctionManager::FunctionIsFalse(ObjectFunctionBase* obj)
{
	
	//終了処理
	obj->End();
	obj->SetState(ObjectFunctionState::STATE_NONE);
	
}