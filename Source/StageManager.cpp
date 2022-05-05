#pragma once
#include "StageManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "ObjectFunctionManager.h"
#include "ObjectManager.h"
#include "Collision.h"
#include "Scene.h"

//初期化処理
void StageManager::Init()
{
	nowStage = nullptr;
	Clear();


}
//更新処理
void StageManager::Update()
{
	
	if (TK_Lib::Lib_Fade::GetFadeVolume() >= 1.0f)
	{
		TK_Lib::Lib_Fade::FadeOutBegin(0.02f);
	}
	nowStage->Update();
}
//描画処理
void StageManager::Render()
{
	nowStage->Render();
}
//モデル描画処理
void StageManager::ModelRender()
{
	nowStage->ModelRender();
}
//全削除
void StageManager::Clear()
{
	stages.clear();
}


void StageManager::GoNextStage()
{
	//現在のステージ
	int StageIndex = -1;

	for (int i = 0; i < stages.size(); i++)
	{
		Stage* stage = stages.at(i).get();
		if (stage == nowStage)
		{
			StageIndex = i;
			StageIndex++;
			break;
		}
	}

	//全てのゲームをクリアしたのでClearシーンへ
	if (StageIndex >= stages.size())
	{
		sceneGame->SetGameClear(true);
		return;
	}

	if (StageIndex>=stages.size())
	{
		assert(!L"存在しないステージを触ろうとしました。");
	}

	if (StageIndex==-1)
	{
		assert(!L"存在しないステージを触ろうとしました。");
	}
	

	ChangeStage(StageIndex);

}
void StageManager::ChangeStage(int StageIndex)
{
	//すべてのステージデータをリセットする。
	sceneGame->GetObjectFunctionManager()->Clear();
	sceneGame->GetEnemyManager()->Clear();
	sceneGame->GetEffectManager()->StageReset();
	sceneGame->GetObjectManager()->Clear();
	TK_Lib::SpotLight::Clear();
	Collision::Instance().Clear();
	
	if (nowStage != nullptr)
	{
		nowStage->End();
	}
	//プレイヤーのリセット
	sceneGame->GetPlayer()->ResetPlayer();

	//シーンの切り替え
	nowStage = stages.at(StageIndex).get();
	nowStage->Init();
	
}
//登録
int StageManager::Register(shared_ptr<Stage> stage)
{
	int size = static_cast<int>(stages.size());
	stages.emplace_back(stage);
	//今の番号を返す
	return size;
}
