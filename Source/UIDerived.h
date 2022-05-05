#pragma once
#include "UIBase.h"

//(没データ)
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
private:
	VECTOR4 GageCut = {0,0,0,0};
	VECTOR4 GageblackCut = { 0,0,0,0 };
	
};

//ミニオンのダウン状態のヘルプアイコン
class UISiroboDownHelp :public UIBase
{
public:
	UISiroboDownHelp() {};
	~UISiroboDownHelp() {};

	//初期化
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
};

//敵に攻撃しているミニオンの数
class UISiroboAttack :public UIBase
{
public:
	UISiroboAttack() {};
	~UISiroboAttack() {};

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
	bool towerSound = true;
	int fontUI = -1;
	float breakingTimer = 0;
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

	inline void SetBlinkingTimer(float timer) { breakingTimer = timer; }
private:
	//テキストの表示
	void RenderText();
};


//時間制限UI
class UITimer :public UIBase
{
private:
	int fontUI=-1;
	float gameTimer=0;
	float maxGameTimer = 0;
	float fontScaleTimer = 0;
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
	void SetGameOverTimer(float timer);

	void AddGameOverTimer(float addTimer);
	inline  float GetGameTimer() { return gameTimer; }
private:
	//フォントの大きさの更新処理
	void UpdateFontScaleTimer();

	//ゲージの表示
	void GaugeRender();
	//ゲームオーバータイマーの表示
	void TextRender();
	//スクリーンいっぱいに出るおおきなゲームオーバータイマーの表示
	void BigGameOverTimeText(float RenderTime);
	//ゲームオーバーテキスト
	void GameOverText();

};


class UINextMessage :public UIBase
{
	const VECTOR2 FontOffset = { 50,70 };
	VECTOR2 centerScale;
	VECTOR2 s1 = { 256 / 3,256 / 3 };
	VECTOR2 s2 = { (256 / 3) * 2,(256 / 3) * 2 };
	VECTOR2 scale = { 1,1 };
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
	VECTOR2 s1 = { 256 / 3,256 / 3 };
	VECTOR2 s2 = { (256 / 3) * 2,(256 / 3) * 2 };
	VECTOR2 scale = { 1,1 };



	
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
	VECTOR3 targetWorldPos = {0,0,0};
	VECTOR2 targetScreenPos = {0,0};

	float targetAngle=0;


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
private:
	//スクリーン座標でターゲットの向きを算出
	void SetTargetAngle();

};









