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
			obj->Update();

			obj->Judge();

			if (obj->GetIsFunction() == IsFunction::IS_TRUE)
			{
				if (obj->GetState()!= ObjectFunctionState::State_Run)
				{
					obj->SetState(ObjectFunctionState::State_Start);
				}

				switch (obj->GetState())
				{
				case ObjectFunctionState::State_Start:obj->Start();
					obj->SetState(ObjectFunctionState::State_Run);
					break;
				case ObjectFunctionState::State_Run:obj->Run();
					break;
				case ObjectFunctionState::State_End:
				case ObjectFunctionState::State_None:
					break;
				}
			}
			//もしFunctionが呼ばれないなら
			else
			{
				if (obj->GetState() != ObjectFunctionState::State_None)
				{
					//終了処理
					obj->End();
					obj->SetState(ObjectFunctionState::State_None);
				}

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