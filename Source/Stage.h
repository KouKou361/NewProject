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
		RENDER_MODEL,//描画
		NO_MAKE_SHADOW_MODEL,//影を生成しない描画
		COLISION_MODEL,//当たり判定
		NAV_MODEL,//ナビメッシュ
		END_MODEL,
	};

	int StageIndex[StageType::END_MODEL];
	int skyModel = 0;

	SceneGame* sceneGame;

	unique_ptr<Export> stageExport;
	std::shared_ptr<UINumTower> uiNumTower;
	std::shared_ptr<UITimer> uiTimer;



public:
	Stage() {};
	Stage(const string renderModel, const string noShadowRenderModel, const string collisionModel, const string navModel,
		const VECTOR3 pos, const VECTOR3 angle, const VECTOR3 scale, const string setData, SceneGame* scene);
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

	inline UITimer* GetUiTimer() { return uiTimer.get(); }
	inline UINumTower* GetNumTower() { return uiNumTower.get(); }
};

class TutoStage: public Stage
{
private:
	int tutoIndex = 0;
	std::vector<shared_ptr<Tuto>> tutoManager;
	shared_ptr<Tuto> nowTuto=nullptr;

	const int renderUiNumTower = 9;
public:
	TutoStage(){}
	TutoStage(const string renderModel, const string noShadowRenderModel, const string collisionModel, const string navModel,
		const VECTOR3 pos, const VECTOR3 angle, const VECTOR3 scale, const string setData, SceneGame* scene);
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
	LOOK_PLAYER,//プレイヤーを見る
	TURN_CAMERA_LOOK_FRONT,//カメラが回転して正面を見る
	LOOK_ENEMY,
	BACK_CAMERA,
	END
};



class BossStage : public Stage
{
private:
	float timer = 0;
	
	int smoke_driftTexture = -1;
	EventState eventState;
	int tutoIndex = 0;
	std::vector<shared_ptr<Tuto>> tutoManager;
	shared_ptr<Tuto> nowTuto = nullptr;

	const int renderUiNumTower = 9;
	//Boss
	EnemyBase* enm = nullptr;
	//カメラ
	CameraBossEntry* camera = nullptr;
public:
	BossStage() {}
	BossStage(const string renderModel, const string noShadowRenderModel, const string collisionModel, const string navModel,
		const VECTOR3 pos, const VECTOR3 angle, const VECTOR3 scale, const string setData, SceneGame* scene);
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
	inline EventState GetEventState() { return eventState; }
};
