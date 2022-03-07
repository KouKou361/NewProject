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
	SceneGame* sceneGame;
	unique_ptr<UITuto>  ui;
	std::unique_ptr<UINextMessage> uiNextMessage;
	std::vector <string>textes;
	int TextIndex = 0;
	int uiTimer = 0;
	std::shared_ptr<UI2DDirection> ui2DDirection;
public:
	Tuto() {};
	Tuto(SceneGame* sceneGame);
	~Tuto() {};
	//初期化処理
	virtual void Init();
	//更新処理
	virtual void Update();
	//テキスト
	void SetText(string text) { this->ui->SetText(text); }
	//次のテキストに移行、終了判定処理
	virtual bool Judge();
	//描画
	virtual void Render();
	//テキストの追加
	void AddText(string text) { textes.push_back(text); };

	UITuto* GetUi() { return ui.get(); };

};
class MoveTuto:public Tuto
{
	class ClearCircle
	{
	public:
		VECTOR3 Pos;
		float Radius;
		float Weight;
	};
	ClearCircle circle;
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
class GetMinionTuto :public Tuto
{
public:
	GetMinionTuto(SceneGame* sceneGame);
	~GetMinionTuto() {};
	//初期化処理
	void Init();
	//更新処理
	void Update();
	//次のテキストに移行、終了判定処理
	bool Judge();
	//描画
	void Render();
};
class KillDummyEnemyTuto :public Tuto
{
	enum
	{
		StepTargetEnemy,
		StepTargetCamera,
		StepAttack,
		StepEnd,
	};
private:
	int AttackTutoStep = 0;
	int TutoTexture[StepEnd];
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
};
class ResurectionMinionTuto :public Tuto
{
public:
	ResurectionMinionTuto(SceneGame* sceneGame);
	~ResurectionMinionTuto() {};
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
};


