#pragma once
class Player;
class BossStage;

//プレイヤーのステートマシン(基底クラス)
class PlayerState
{
public:
	PlayerState() {};
	~PlayerState() {};

	//初期化
	virtual void Start(Player* pl)=0;
	//更新
	virtual void Run(Player*pl) = 0;
	//終了
	virtual void End(Player* pl) = 0;
};

//プレイヤーの攻撃クラス
class AttackState:public PlayerState
{
private:
	//攻撃フラグ（一度に沢山の出てほしくないため）
	bool AttackFlg=false;
	//攻撃アニメーションのタイミング
	const float AttackTimeRate = 0.5f;
public:
	AttackState() {};
	~AttackState() {};

	//初期化
	void Start(Player* pl);
	//更新
	void Run(Player* pl);
	//終了
	void End(Player* pl);
private:
	void DownSpeed(Player* pl);
};

//プレイヤーのダメージクラス
class DamageState :public PlayerState
{
public:
	DamageState() {};
	~DamageState() {};
private:
	//初期化
	void Start(Player* pl);
	//更新
	void Run(Player* pl);
	//終了
	void End(Player* pl);
};

//プレイヤーの死亡クラス
class DeadState :public PlayerState
{
public:
	DeadState() {};
	~DeadState() {};

	//初期化
	void Start(Player* pl);
	//更新
	void Run(Player* pl);
	//終了
	void End(Player* pl);
};


//プレイヤーの待機クラス
class WaitState :public PlayerState
{
public:
	WaitState() {};
	~WaitState() {};

	//初期化
	void Start(Player* pl);
	//更新
	void Run(Player* pl);
	//終了
	void End(Player* pl);
};

//プレイヤーの移動クラス
class WalkState :public PlayerState
{
public:
	WalkState() {};
	~WalkState() {};

	//初期化
	void Start(Player* pl);
	//更新
	void Run(Player* pl);
	//終了
	void End(Player* pl);
};


//プレイヤーのボス専登場演出クラス
class BossEntryPlayerState :public PlayerState
{
	BossStage* stage = nullptr;
public:
	BossEntryPlayerState() {};
	~BossEntryPlayerState() {};

	void SetState(BossStage* stage) { this->stage = stage; }
	
	//初期化
	void Start(Player* pl);
	//更新
	void Run(Player* pl);
	//終了
	void End(Player* pl);
};




