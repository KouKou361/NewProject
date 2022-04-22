#pragma once
#include "MinionActionBase.h"
#include "Lib.h"
class EnemyBase;


//待機行動
class MinionIdleAction :public MinionActionBase
{
public:
	MinionIdleAction(MinionPlayer* minion) :MinionActionBase(minion) {}

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
class MinionStandByAction :public MinionActionBase
{
public:
	MinionStandByAction(MinionPlayer* minion) :MinionActionBase(minion) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();



	//終了処理
	void End();
	
	//群衆
	void Flock();

	void MinionVsMinion();
	void VsPlayer();

	//Imguiデバッグ
	void DebugImgui();

	//もし目標物が消えてしまった場合
	ActionBase::State DeleteTarget();
};


// 撤退
class MinionBackAction : public MinionActionBase
{
public:
	MinionBackAction(MinionPlayer* minion) :MinionActionBase(minion) {}

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
class MinionPursuitAction : public MinionActionBase
{
private:
	bool searchFlg;
	VECTOR3 targetPos;
public:
	MinionPursuitAction(MinionPlayer* minion) :MinionActionBase(minion) {}

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
class MinionAttackAction : public MinionActionBase
{
public:
	MinionAttackAction(MinionPlayer* minion) :MinionActionBase(minion) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//引っ付き処理
	bool EnemyStick();

	//引っ付き処理
	bool Stick();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();
};

// 投げられる行動
class MinionThrowAction : public MinionActionBase
{
private:

	float velocity = 0.0f;

public:
	MinionThrowAction(MinionPlayer* minion) :MinionActionBase(minion) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//当たり判定処理
	bool HitCollision();

	//Imguiデバッグ
	void DebugImgui();

	//もし目標物が消えてしまった場合
	virtual ActionBase::State DeleteTarget();


};

// 追跡行動
class MinionDieAction : public MinionActionBase
{
private:
	bool searchFlg;
	VECTOR3 targetPos;
public:
	MinionDieAction(MinionPlayer* minion) :MinionActionBase(minion) {}

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
class MinionResuscitationAction : public MinionActionBase
{
private:
	bool searchFlg;
	VECTOR3 targetPos;
public:
	MinionResuscitationAction(MinionPlayer* minion) :MinionActionBase(minion) {}

	//開始処理
	void Start();

	//実行処理
	ActionBase::State Run();

	//終了処理
	void End();

	//Imguiデバッグ
	void DebugImgui();

	//蘇生処理
	void Resuscitation();
	//蘇生更新処理
	void UpdateResuscitation();

	//もし目標物が消えてしまった場合
	ActionBase::State DeleteTarget();
};




