#pragma once
#include "Tuto.h"
#include "Manager.h"
#include <vector>
#include <memory>
class SceneGame;
using namespace std;
class TutoManager :public Manager
{
public:
	TutoManager(SceneGame* sceneGame) { this->sceneGame = sceneGame; };
	~TutoManager() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//全削除
	void Clear();

	//敵の数の取得
	inline int GetStageSize() { return stages.size(); }
	//敵の数の取得
	inline Tuto* GetStgeIndex(const int& index) { return stages.at(index).get(); }

private:
	SceneGame* sceneGame = nullptr;
	Stage* nowStage = nullptr;
	vector<shared_ptr<Stage>>stages;
};
