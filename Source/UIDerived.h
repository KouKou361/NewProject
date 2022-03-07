#pragma once
#include "UIBase.h"

//プレイヤーの体力
class UIPlayerHP:public UIBase
{
public:
	UIPlayerHP() {};
	~UIPlayerHP() {};

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
};

//攻撃目標のカーソル
class UITargetCursur :public UIBase
{
public:
	UITargetCursur() {};
	~UITargetCursur() {};

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
};


//目標の体力のカーソル
class UITargetHP :public UIBase
{
public:
	UITargetHP() {};
	~UITargetHP() {};

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
};

//ミニオンのダウン状態のヘルプアイコン
class UIMinionDownHelp :public UIBase
{
public:
	UIMinionDownHelp() {};
	~UIMinionDownHelp() {};

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
};

//敵に攻撃しているミニオンの数
class UIMinionAttack :public UIBase
{
public:
	UIMinionAttack() {};
	~UIMinionAttack() {};

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
};

//タワーの数
class UINumTower :public UIBase
{
private:
	bool TowerSound = true;
	int FontUI = -1;
	float BlinkingTimer = 0;
public:
	UINumTower(SceneGame* scene) { this->scene = scene; }
	UINumTower() {};
	~UINumTower() {};

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();

	void SetBlinkingTimer(float timer) { BlinkingTimer = timer; }
};


//時間制限UI
class UITimer :public UIBase
{
private:
	int FontUI=-1;
	int GameTimer=0;
	int MaxGameTimer = 0;
	float FrameTimer=0;
	float FontScaleTimer = 0;
public:
	UITimer() {};
	~UITimer() {};



	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();

	//ゲームオーバーの時間設定
	void SetGameOverTimer(int timer);

	void AddGameOverTimer(int addTimer);
	int GetGameTimer() { return GameTimer; }
};


class UINextMessage :public UIBase
{
	const VECTOR2 FontOffset = { 50,70 };
	VECTOR2 centerScale;
	VECTOR2 S1 = { 256 / 3,256 / 3 };
	VECTOR2 S2 = { (256 / 3) * 2,(256 / 3) * 2 };
	VECTOR2 Scale = { 1,1 };
public:
	UINextMessage() {};
	~UINextMessage() {};

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
};

class UITuto :public UIBase
{
	const VECTOR2 FontOffset = { 50,100 };
	const VECTOR2 NextFontOffset = { 1300,250 };
	VECTOR2 centerScale;
	VECTOR2 S1 = { 256 / 3,256 / 3 };
	VECTOR2 S2 = { (256 / 3) * 2,(256 / 3) * 2 };
	VECTOR2 Scale = { 1,1 };



	
public:

	UITuto() {};
	~UITuto() {};

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
};

//スクリーンに方向を示す
class UI2DDirection :public UIBase
{
	VECTOR3 targetWorldPos;
	VECTOR2 targetScreenPos;
	//半径
	const float UICenterR = 250.0f;
	float targetAngle;


public:
	UI2DDirection(SceneGame* scene) { this->scene = scene; }
	UI2DDirection() {};
	~UI2DDirection() {};

	//位置の設定
	void SetTargetPos(const VECTOR3 pos);
	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
};









