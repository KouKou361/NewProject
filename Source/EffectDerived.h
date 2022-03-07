#pragma once
#include "EffectBase.h"

class EffectFire :public EffectBase
{
private:
	int PointLight = 0;

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
	VECTOR2 testSlider  = {1,1};
	VECTOR2 testSlider2 = {1,-1};
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

