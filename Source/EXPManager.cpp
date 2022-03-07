#include "EXPManager.h"
#include "EXP.h"
//初期化処理
void EXPManager::Init()
{

}
//更新処理
void EXPManager::Update()
{
	for (shared_ptr<EXP> exp : expes)
	{
		if (exp)
		{
			exp->Update();
		}

	}
	//破棄処理
//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する。
	for (shared_ptr<EXP> exp : remove)
	{
		//std::vectorから要素を破棄する場合はイレテーターで削除しなければならない
		std::vector<shared_ptr<EXP>>::iterator it = std::find(expes.begin(), expes.end(), exp);
		if (it != expes.end())
		{
			expes.erase(it);
		}
	}
	remove.clear();
}
//描画処理
void EXPManager::Render()
{
	for (shared_ptr<EXP> exp : expes)
	{
		if (exp)
		{
			exp->Render();

			//Imgui
			//exp->ImguiDebug();
		}
	}
}
//全削除
void EXPManager::Clear()
{
	for (int i = 0; i < GetexpesSize(); i++)
	{
		EXP* exp = GetexpesIndex(i);
	}

	expes.clear();
	remove.clear();
}

//登録
void EXPManager::Register(shared_ptr<EXP> exp,VECTOR3 Pos)
{
	exp->Init(Pos);
	exp->SetManager(scene);
	expes.emplace_back(exp);
}
//破棄処理
void EXPManager::Destroy(EXP* m_exp)
{
	for (shared_ptr<EXP> exp : expes)
	{
		std::vector<shared_ptr<EXP>>::iterator it = std::find(expes.begin(), expes.end(), exp);
		if (it->get() == m_exp)
		{
			shared_ptr<EXP> e = exp;
			remove.emplace_back(e);
		}
	}
}