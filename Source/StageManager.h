#pragma once
#include "Stage.h"
#include "Manager.h"
#include <vector>
#include <memory>
class SceneGame;
using namespace std;
class StageManager :public Manager
{
public:
	StageManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };
	~StageManager() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//モデル描画処理
	void ModelRender();
	//全削除
	void Clear();
	//登録(返り値は)
	int Register(shared_ptr<Stage> enm);
	//ステージの変更
	void ChangeStage(int StageIndex);
	//次のステージへ移行
	void GoNextStage();
	//現在のステージのゲームクリアしているかどうか
	bool GetClearJudge() { return nowStage->ClearJudge(); }

	//敵の数の取得
	int GetStageSize() { return stages.size(); }
	//敵の数の取得
	Stage* GetStgeIndex(const int& index) { return stages.at(index).get(); }

	Stage* GetNowStage() { return nowStage; };


private:
	SceneGame* sceneGame = nullptr;
	Stage* nowStage=nullptr;
	vector<shared_ptr<Stage>>stages;
};
