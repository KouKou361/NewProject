#pragma once
#include "SiroboPlayer.h"

//初期化処理
void SiroboManager::Init()
{
	Clear();
	indexSirobo = 0;
}
//更新処理
void SiroboManager::Update()
{
	for (int i=0;i<sirobos.size();i++)
	{
		Sirobo* sirobo = sirobos.at(i).get();
		if (sirobo)
		{
			sirobo->Update();
		}

	}
	//破棄処理
//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する。
	for (shared_ptr<Sirobo> sirobo : remove)
	{
		//std::vectorから要素を破棄する場合はイレテーターで削除しなければならない
		std::vector<shared_ptr<Sirobo>>::iterator it = std::find(sirobos.begin(), sirobos.end(), sirobo);
		if (it != sirobos.end())
		{
			sirobos.erase(it);
		}
	}
	remove.clear();

}
//描画処理
void SiroboManager::Render()
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		if (sirobo)
		{
			sirobo->Render();

			//Imgui
			//sirobo->ImguiDebug();
		}
	}
}
//モデル描画処理
void SiroboManager::ModelRender()
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		if (sirobo)
		{
			sirobo->ModelRender();
		}
	}
}
//破棄処理
void SiroboManager::Destroy(Sirobo* sirobo)
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		std::vector<shared_ptr<Sirobo>>::iterator it = std::find(sirobos.begin(), sirobos.end(), sirobo);
		if (it != sirobos.end())
		{
			shared_ptr<Sirobo> e = sirobo;
			remove.emplace_back(e);
		}
	}

}
void SiroboManager::AllBack()
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		if (sirobo)
		{
			if (sirobo->GetState() == Sirobo::StateType::TYPE_DEAD)continue;
			//攻撃可能なミニオンの算出
			if (sirobo->GetState() != Sirobo::StateType::TYPE_STAND_BY)
			{
				sirobo->ResetNode();
			}
		}
	}
}
//ミニオンの攻撃OK行動のみ攻撃する
void SiroboManager::OneAttack(Sirobo* sirobo)
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		if (sirobo)
		{
			//攻撃可能なミニオンの算出
			if (sirobo->GetState() == Sirobo::StateType::TYPE_STAND_BY)
			{
				sirobo->SetAttackStandBy(true);
				sirobo->ResetNode();
					break;
			}
		}
	}
}
void SiroboManager::CollisionDebug()
{
	for (shared_ptr<Sirobo> sirobo : sirobos)
	{
		if (sirobo)
		{
			sirobo->CollisionDebug();
		}
	}
}

//全削除
void SiroboManager::Clear()
{
	sirobos.clear();
	remove.clear();
}
//登録
void SiroboManager::Register(shared_ptr<Sirobo> sirobo)
{
	sirobo->SetIndex(indexSirobo);
	sirobo->SetManager(this);
	sirobos.emplace_back(sirobo);
	indexSirobo++;
}
