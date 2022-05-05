#pragma once
#include "Lib.h"
#include <string>
#include "UIDerived.h"
#include "Export.h"
class SceneGame;
class UI2DDirection;
using namespace std;

class Tuto
{

	
protected:
	SceneGame* sceneGame=nullptr;
	unique_ptr<UITuto>  TutoWindowUI = nullptr;
	std::unique_ptr<UINextMessage> uiNextMessage = nullptr;
	std::vector <string>textes;
	int textIndex = 0;
	float uiTimer = 0;
	std::shared_ptr<UI2DDirection> ui2DDirection = nullptr;
public:
	Tuto() {};
	Tuto(SceneGame* sceneGame);
	~Tuto() {};


	//初期化処理
	virtual void Init();
	//更新処理
	virtual void Update();
	//次のテキストに移行、終了判定処理
	virtual bool Judge();
	//描画
	virtual void Render();

	//テキストの追加
	inline void AddText(const string text) { textes.push_back(text); };
	//テキスト
	inline void SetText(const string text) { this->TutoWindowUI->SetText(text); }

	inline UITuto* GetUi() { return TutoWindowUI.get(); };

};
class MoveTuto:public Tuto
{
	class ClearCircle
	{
	public:
		VECTOR3 pos = {0,0,0};
		float radius=0;
		float weight = 0;
	};
	ClearCircle circle = {};
public:
	MoveTuto(SceneGame* sceneGame);
	~MoveTuto() {};
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//次のテキストに移行、終了判定処理
	bool Judge();
	//描画
	void Render();
};
class GetSiroboTuto :public Tuto
{
public:
	GetSiroboTuto(SceneGame* sceneGame);
	~GetSiroboTuto() {};
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//次のテキストに移行、終了判定処理
	bool Judge();
	//描画
	void Render();
private:
	void SummonSirobo();
};
class KillDummyEnemyTuto :public Tuto
{
	enum class TutoStep
	{
		STEP_TARGET_ENEMY,
		STEP_TARGET_CAMERA,
		STEP_ATTACK,
		STEP_END,
	};
private:
	TutoStep attackTutoStep = TutoStep::STEP_TARGET_ENEMY;
	int tutoTexture[static_cast<int>(TutoStep::STEP_END)];
public:
	KillDummyEnemyTuto(SceneGame* sceneGame);
	~KillDummyEnemyTuto() {};
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//次のテキストに移行、終了判定処理
	bool Judge();
	//描画
	void Render();
private:
	//ダミー敵の生成
	void SummonDummyEnemy();
};
class ResurectionSiroboTuto :public Tuto
{
public:
	ResurectionSiroboTuto(SceneGame* sceneGame);
	~ResurectionSiroboTuto() {};
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//次のテキストに移行、終了判定処理
	bool Judge();
	//描画
	void Render();
};

class KillEnemyTuto :public Tuto
{
public:
	KillEnemyTuto(SceneGame* sceneGame);
	~KillEnemyTuto() {};
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//UIの更新処理
	void UiTargetUpdate();
	//次のテキストに移行、終了判定処理
	bool Judge();
	//描画
	void Render();
private:
	//敵の生成
	void SummonEnemy();
	//オブジェクトの生成
	void SummonObject();
};


