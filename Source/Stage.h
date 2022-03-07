#pragma once

#include "Lib.h"
#include <string>
#include "Export.h"
class SceneGame;
class Tuto;
class UINumTower;
class UITimer;
class EnemyBase;
class CameraBossEntry;

using namespace std;

class Stage
{
protected:

	//ステージタイプ
	enum StageType
	{
		RenderModel,//描画
		NoMakeShadowModel,//影を生成しない描画
		CollisionModel,//当たり判定
		NavModel,//ナビメッシュ
		EndModel,
	};

	int StageIndex[StageType::EndModel];
	unique_ptr<Export> stageExport;
	SceneGame* sceneGame;

	std::shared_ptr<UINumTower> uiNumTower;

	std::shared_ptr<UITimer> uiTimer;

	int SkyModel = 0;

public:
	Stage() {};
	Stage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel,
		VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale,string SetData, SceneGame* scene);
	~Stage() {};
	//初期化処理
	virtual void Init();
	//更新処理
	virtual void Update();
	//描画
	virtual void Render();
	//描画
	virtual void ModelRender();
	//終了処理
	virtual void End();
	//クリア判定
	virtual bool ClearJudge();

	UITimer* GetUiTimer() { return uiTimer.get(); }
	UINumTower* GetNumTower() { return uiNumTower.get(); }
};

class TutoStage: public Stage
{
private:
	int TutoIndex = 0;
	std::vector<shared_ptr<Tuto>> TutoManager;
	shared_ptr<Tuto> nowTuto=nullptr;

	const int RenderUiNumTower = 9;
public:
	TutoStage(){}
	TutoStage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel,
		VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale, string SetData, SceneGame* scene);
	~TutoStage() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画
	void Render();
	//描画
	void ModelRender();
	//終了処理
	void End();
	//次のチュートリアルへ移行する。
	void NextTuto();

	//クリア判定
	bool ClearJudge();
};

enum class EventState
{
	LookPlayer,//プレイヤーを見る
	TurnCameraLookFront,//カメラが回転して正面を見る
	LookEnemy,
	BackCamera,
	End
};



class BossStage : public Stage
{
private:
	float timer = 0;
	
	int smoke_driftTexture = -1;
	EventState eventState;
	int TutoIndex = 0;
	std::vector<shared_ptr<Tuto>> TutoManager;
	shared_ptr<Tuto> nowTuto = nullptr;

	const int RenderUiNumTower = 9;
	//Boss
	EnemyBase* enm = nullptr;
	//カメラ
	CameraBossEntry* camera = nullptr;
public:
	BossStage() {}
	BossStage(string RenderModel, string NoShadowRenderModel, string CollisionModel, string NavModel,
		VECTOR3 Pos, VECTOR3 Angle, VECTOR3 Scale, string SetData, SceneGame* scene);
	~BossStage() {};

	//初期化処理
	void Init();
	//更新処理
	void Update();
	//描画
	void Render();
	//描画
	void ModelRender();
	//終了処理
	void End();
	//クリア判定
	bool ClearJudge();

	//現在進行中のイベントを返す
	EventState GetEventState() { return eventState; }
};
