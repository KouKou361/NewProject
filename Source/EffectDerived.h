#pragma once
#include "EffectBase.h"

class EffectFire :public EffectBase
{
private:
	int pointLight = 0;


public:
	EffectFire() {};
	~EffectFire() {};

	//初期化処理
	void Init();
	//更新処理
	void Play(VECTOR3 Pos, int Num);
	//更新処理
	void Update();
};

class EffectThrow :public EffectBase
{
private:

public:
	EffectThrow() {};
	~EffectThrow() {};

	//初期化処理
	void Init();
	//更新処理
	void Play(VECTOR3 Pos, int Num);
	//更新処理
	void Update();
};

class EffectAttack :public EffectBase
{
private:
	const float UpdateScale = 0.005f;//エフェクトが大きくなる
	static constexpr float AlphaRate = 0.2f;
public:
	EffectAttack() {};
	~EffectAttack() {};

	//初期化処理
	void Init();
	//更新処理
	void Play(VECTOR3 Pos, int Num);
	//更新処理
	void Update();
};

class EffectThowSmoke :public EffectBase
{
private:

public:
	EffectThowSmoke() {};
	~EffectThowSmoke() {};

	//初期化処理
	void Init();
	//更新処理
	void Play(VECTOR3 Pos, int Num);
	//更新処理
	void Update();
};

class EffectTowerBreak :public EffectBase
{
private:

public:
	EffectTowerBreak() {};
	~EffectTowerBreak() {};

	//初期化処理
	void Init();
	//更新処理
	void Play(VECTOR3 Pos, int Num);
	//更新処理
	void Update();
};

class EffectStageClear :public EffectBase
{
private:

public:
	EffectStageClear() {};
	~EffectStageClear() {};

	//初期化処理
	void Init();
	//更新処理
	void Play(VECTOR3 Pos, int Num);
	//更新処理
	void Update();
};

class EffectBossFire :public EffectBase
{
private:
	const VECTOR3   VelocityRate = { 15.9f,20.3f ,15.9f };
	const VECTOR3 Acceleration = { 0.1f,-10.0f ,0.1f};
	const float PosUP = 5.0f;
public:
	EffectBossFire() {};
	~EffectBossFire() {};

	//初期化処理
	void Init();
	//更新処理
	void Play(VECTOR3 Pos, int Num);
	//更新処理
	void Update();
};

class EffectBossExplosion :public EffectBase
{
private:
	VECTOR2 testSlider = { 1,1 };
	VECTOR2 testSlider2 = { 1,-1 };
public:
	EffectBossExplosion() {};
	~EffectBossExplosion() {};

	//初期化処理
	void Init();
	//更新処理
	void Play(VECTOR3 Pos, int Num);
	//更新処理
	void Update();
};

class EffectBossSiteBreak :public EffectBase
{
private:
	VECTOR2 testSlider = { 1,1 };
	VECTOR2 testSlider2 = { 1,-1 };
public:
	EffectBossSiteBreak() {};
	~EffectBossSiteBreak() {};

	//初期化処理
	void Init();
	//更新処理
	void Play(VECTOR3 Pos, int Num);
	//更新処理
	void Update();
};

