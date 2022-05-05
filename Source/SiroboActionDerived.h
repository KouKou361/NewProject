#pragma once
#include "SiroboActionBase.h"
#include "Lib.h"
class EnemyBase;


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
//シロボ、プレイヤーの後についていく（歩き）
class SiroboFollowRun:public SiroboActionBase

{
public:
	SiroboFollowRun(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

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

	//プレイヤーの当たり判定
	void VsPlayer();
};






//シロボ、プレイヤーの後についていく（歩き）
class SiroboStandByAction :public SiroboActionBase
{
public:
	SiroboStandByAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

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

	//プレイヤーの当たり判定
	void VsPlayer();
};


// 撤退
class SiroboBackAction : public SiroboActionBase
{
public:
	SiroboBackAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

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
	//プレイヤー方向に走る
	void RunToThePlaye();
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




