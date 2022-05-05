#pragma once
#include "ActionBase.h"
#include "Lib.h"
class EnemyBase;


//待機行動
class IdleAction :public ActionBase
{
public:
	IdleAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();
};

// 追跡行動
class PursuitAction : public ActionBase
{
private:
	bool searchFlg=false;
	VECTOR3 targetPos = { 0,0,0 };
public:
	PursuitAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

private:

	//ターゲットに向かって進む。
	bool PursuitTarget();


};

// 攻撃行動
class AttackAction : public ActionBase
{
public:
	AttackAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

	//DebugRender
	void DebugRender();
};

// ダメージ行動
class DamageAction : public ActionBase
{
public:
	DamageAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();
};


// 死亡行動
class DeadAction : public ActionBase
{
public:
	DeadAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();
};

//回転攻撃開始
class BossEntry : public ActionBase
{
public:
	BossEntry(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();
};

//回転攻撃開始
class BossRollAttackStartAction : public ActionBase
{
public:
	BossRollAttackStartAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();



	//Imguiデバッグ
	void DebugImgui();
private:
	//
	void PlayerToTurn();
	//着地サウンド
	void BossJumpDownSound();
};

//回転攻撃
class BossRollAttackAction : public ActionBase
{
private:

public:
	BossRollAttackAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

private:
	//壁にぶつかったかどうか
	bool ContactWall();
	//前進
	void Advance(const float AdvanceSpeed);
};

//回転攻撃終了
class BossRollAttackEndAction : public ActionBase
{
public:
	BossRollAttackEndAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

private:
	//着地サウンド
	void BossJumpDownSound();
};


//待機行動
class BossIdeiAction :public ActionBase
{
private:
	float ideiTimer=0;
public:
	BossIdeiAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();
};


//ボスの移動行動
class BossWalkAction :public ActionBase
{
private:
	int timer = 0;
	VECTOR3 targetPos;//移動する目標地点
public:
	BossWalkAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

	void Advance(const float AdvanceSpeed);
private:
	void SetTargetPos();
};


//ボスの死亡行動
class BossDeadAction : public ActionBase
{
private:
	enum class EventDeleteState
	{
		NONE,
		STOP,//止まる
		FIRE,//燃える
		EXPLOSION,//爆発
		END,
	};
	EventDeleteState state= EventDeleteState::NONE;
public:
	BossDeadAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

	void StateStop();
	void StateFire();
	void StateExplosion();
	void StateEnd();
};

//ボスの部位破壊
class BossSiteDieAction :public ActionBase
{
private:
	
public:
	BossSiteDieAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();
};









