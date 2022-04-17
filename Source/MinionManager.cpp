#pragma once
#include "MinionPlayer.h"

//初期化処理
void MinionManager::Init()
{
	Clear();
	IndexMinion = 0;
}
//更新処理
void MinionManager::Update()
{
	for (int i=0;i<minions.size();i++)
	{
		MinionPlayer* minion = minions.at(i).get();
		if (minion)
		{
			minion->Update();
		}

	}
	//破棄処理
//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する。
	for (shared_ptr<MinionPlayer> minion : remove)
	{
		//std::vectorから要素を破棄する場合はイレテーターで削除しなければならない
		std::vector<shared_ptr<MinionPlayer>>::iterator it = std::find(minions.begin(), minions.end(), minion);
		if (it != minions.end())
		{
			minions.erase(it);
		}
	}
	remove.clear();

}
//描画処理
void MinionManager::Render()
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		if (minion)
		{
			minion->Render();

			//Imgui
			//minion->ImguiDebug();
		}
	}
}
//モデル描画処理
void MinionManager::ModelRender()
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		if (minion)
		{
			minion->ModelRender();
		}
	}
}
//破棄処理
void MinionManager::Destroy(MinionPlayer* minion)
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		std::vector<shared_ptr<MinionPlayer>>::iterator it = std::find(minions.begin(), minions.end(), minion);
		if (it != minions.end())
		{
			shared_ptr<MinionPlayer> e = minion;
			remove.emplace_back(e);
		}
	}

}
void MinionManager::AllBack()
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		if (minion)
		{
			if (minion->GetState() == MinionPlayer::StateType::TYPE_DEAD)continue;
			//攻撃可能なミニオンの算出
			if (minion->GetState() != MinionPlayer::StateType::TYPE_STAND_BY)
			{
				minion->ResetNode();
			}
		}
	}
}
//ミニオンの攻撃OK行動のみ攻撃する
void MinionManager::OneAttack(MinionPlayer* minion)
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		if (minion)
		{
			//攻撃可能なミニオンの算出
			if (minion->GetState() == MinionPlayer::StateType::TYPE_STAND_BY)
			{
				minion->SetAttackStandBy(true);
				minion->ResetNode();
					break;
			}
		}
	}
}
void MinionManager::CollisionDebug()
{
	for (shared_ptr<MinionPlayer> minion : minions)
	{
		if (minion)
		{
			minion->CollisionDebug();
		}
	}
}

//全削除
void MinionManager::Clear()
{
	minions.clear();
	remove.clear();
}
//登録
void MinionManager::Register(shared_ptr<MinionPlayer> minion)
{
	minion->SetIndex(IndexMinion);
	minion->SetManager(this);
	minions.emplace_back(minion);
	IndexMinion++;
}
