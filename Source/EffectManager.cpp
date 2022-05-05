#pragma once
#include "EffectManager.h"
#include "EffectBase.h"
//初期化処理
void EffectManager::Init()
{
	updatePlayEffectPoses.clear();
	TK_Lib::Lib_Effect::Init(10);//エフェクトの設定
}

//毎フレームエフェクトをだすデータ登録
void EffectManager::UpdateEffectRegister(const VECTOR3& pos, const string &name,const int& num)
{
	UpdatePlayEffect efc;

	efc.pos = pos;
	efc.name = name;
	efc.playNum = num;

	updatePlayEffectPoses.push_back(efc);
}
//毎フレームエフェクトをだすエフェクトの更新処理
void EffectManager::PlayUpdateEffect()
{
	for (int i = 0; i < updatePlayEffectPoses.size(); i++)
	{
		UpdatePlayEffect UpdateEfc = updatePlayEffectPoses.at(i);
		EffectBase* efc= GetEffectFromSerchKey(UpdateEfc.name);		

		if (TK_Lib::Camera::IsCamera(UpdateEfc.pos))
		{
			efc->Play(UpdateEfc.pos, UpdateEfc.playNum);
		}

		

	}
}
//更新処理
void EffectManager::Update()
{
	//毎フレームエフェクトをだすエフェクトの更新処理
	PlayUpdateEffect();

	for (shared_ptr<EffectBase> efc : effects)
	{
		if (efc)
		{
			efc->Update();
		}
	}
	//破棄処理
    //更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する。
	for (shared_ptr<EffectBase> efc : remove)
	{
		//std::vectorから要素を破棄する場合はイレテーターで削除しなければならない
		std::vector<shared_ptr<EffectBase>>::iterator it = std::find(effects.begin(), effects.end(), efc);
		if (it != effects.end())
		{
			effects.erase(it);
		}
	}
	remove.clear();

}
//破棄処理
void EffectManager::Destroy(const EffectBase* efc)
{
	for (shared_ptr<EffectBase> m_efc : effects)
	{
		std::vector<shared_ptr<EffectBase>>::iterator it = std::find(effects.begin(), effects.end(), m_efc);
		if (it->get() == efc)
		{
			shared_ptr<EffectBase> e = m_efc;
			remove.emplace_back(e);
		}
	}
}
//ステージのリセット
void EffectManager::NotRender()
{
	for (shared_ptr<EffectBase> efc : effects)
	{
		std::vector<shared_ptr<EffectBase>>::iterator it = std::find(effects.begin(), effects.end(), efc);
		{
			shared_ptr<EffectBase> e = efc;
			e->NotRender();//非表示にする
		}
	}
}

//ステージのリセット
void EffectManager::StageReset()
{
	NotRender();//全て非表示にする
	remove.clear();
	updatePlayEffectPoses.clear();
}


//全削除
void EffectManager::Clear()
{
	for (int i = 0; i < GetEffectsSize(); i++)
	{
		GetEffectsIndex(i)->Delete();
	}
	effectIndexResources.clear();
	effects.clear();
	remove.clear();
	updatePlayEffectPoses.clear();
	TK_Lib::Lib_Effect::Init(10);


}
//登録した名前からエフェクト取得
EffectBase* EffectManager::GetEffectFromSerchKey(const string& searchName)
{
	return effectIndexResources.at(searchName);
}
//エフェクト登録
void EffectManager::Register(const shared_ptr<EffectBase>& efc, const string& registerName)
{
	efc->Init();
	effects.emplace_back(efc);
	effectIndexResources.insert(make_pair(registerName, efc.get()));
}