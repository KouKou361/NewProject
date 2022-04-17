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

	//‰Šú‰»ˆ—
	void Init();
	//XVˆ—
	void Update();
	//•`‰æˆ—
	void Render();
	//‘Síœ
	void Clear();

	//“G‚Ì”‚Ìæ“¾
	inline int GetStageSize() { return stages.size(); }
	//“G‚Ì”‚Ìæ“¾
	inline Tuto* GetStgeIndex(const int& index) { return stages.at(index).get(); }

private:
	SceneGame* sceneGame = nullptr;
	Stage* nowStage = nullptr;
	vector<shared_ptr<Stage>>stages;
};
