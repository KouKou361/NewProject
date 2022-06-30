#pragma once
#include "SiroboActionBase.h"
#include "Lib.h"
#include "StandByAnimetion.h"
class EnemyBase;

class BaseStandByAnimetion;
class WalkStandByAnimetion;
class RunStandByAnimetion;
class IdelStandByAnimetion;

//待機行動
class SiroboIdleAction :public SiroboActionBase
{
public:
	SiroboIdleAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//もし目標物が消えてしまった場合
	ActionBase::State DeleteTarget();

	//Imguiデバッグ
	void DebugImgui();
};




//攻撃OK行動
class SiroboStandByAction :public SiroboActionBase
{
private:
	BaseStandByAnimetion* current=nullptr;

	WalkStandByAnimetion* walk = nullptr;
	RunStandByAnimetion*  run = nullptr;
	IdelStandByAnimetion* idei = nullptr;
	float speed = 0.0f;
public:
	SiroboStandByAction(Sirobo* minion) :SiroboActionBase(minion) {
		walk = new WalkStandByAnimetion(minion);
		run = new RunStandByAnimetion(minion);
		idei = new IdelStandByAnimetion(minion);
	}

	~SiroboStandByAction()
	{
		delete walk;
		walk = nullptr;
		delete run;
		run = nullptr;
		delete idei;
		idei = nullptr;
	}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

	//もし目標物が消えてしまった場合
	ActionBase::State DeleteTarget();
private:
	//群衆
	void Flock();
	//シロボ同士の当たり判定
	void SiroboVsSirobo();
	//プレイヤーとの当たり判定
	void VsPlayer();
	//適切なアニメーションに移行する。
	void AllAppropriateAnimesion();
	//適切なアニメーションに移行する。
	bool AppropriateAnimesion(BaseStandByAnimetion* anime);
};


// 撤退
class SiroboBackAction : public SiroboActionBase
{
public:
	SiroboBackAction(Sirobo* minion) :SiroboActionBase(minion) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

	//もし目標物が消えてしまった場合
	ActionBase::State DeleteTarget();
};


// 追跡行動
class SiroboPursuitAction : public SiroboActionBase
{
private:
	bool searchFlg=false;
	VECTOR3 targetPos = {0,0,0};
public:
	SiroboPursuitAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();


};

// 攻撃行動
class SiroboAttackAction : public SiroboActionBase
{
public:
	SiroboAttackAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

private:
	//引っ付き処理
	bool Stick();

	//攻撃目標に対して攻撃する
	void AttackTarget();
};

// 投げられる行動
class SiroboThrowAction : public SiroboActionBase
{
private:

	float velocity = 0.0f;

public:
	SiroboThrowAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

	//もし目標物が消えてしまった場合
	virtual ActionBase::State DeleteTarget();

private:
	//当たり判定処理
	bool HitCollision();

	//モデルの当たり判定
	bool HitCollisioinModel();

	//敵の当たり判定
	bool HitEnemy();

	//オブジェクトの当たり判定
	bool HitObject();

	//放物線を描いて進む初速度設定
	void SetFirstVelocity();

	//重力の適応
	void AddGravity();

	//目標地点に進む
	void TargetToMove();

};

// 追跡行動
class SiroboDieAction : public SiroboActionBase
{
private:
	bool searchFlg=false;
	VECTOR3 targetPos = {0,0,0};
public:
	SiroboDieAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();


};

// 蘇生されている時の行動処理
class SiroboResuscitationAction : public SiroboActionBase
{
private:
	bool searchFlg = false;
	VECTOR3 targetPos = {0,0,0};
public:
	SiroboResuscitationAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

	//もし目標物が消えてしまった場合
	ActionBase::State DeleteTarget();
private:

	//蘇生処理
	void Resuscitation();

	//蘇生更新処理
	void UpdateResuscitation();
};




