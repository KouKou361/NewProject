#pragma once
#include "EffectBase.h"

class EffectFire :public EffectBase
{
private:
	int PointLight = 0;

public:
	EffectFire() {};
	~EffectFire() {};

	//����������
	void Init();
	//�X�V����
	void Play(VECTOR3 Pos, int Num);
	//�X�V����
	void Update();
};

class EffectThrow :public EffectBase
{
private:

public:
	EffectThrow() {};
	~EffectThrow() {};

	//����������
	void Init();
	//�X�V����
	void Play(VECTOR3 Pos, int Num);
	//�X�V����
	void Update();
};

class EffectAttack :public EffectBase
{
private:

public:
	EffectAttack() {};
	~EffectAttack() {};

	//����������
	void Init();
	//�X�V����
	void Play(VECTOR3 Pos, int Num);
	//�X�V����
	void Update();
};

class EffectThowSmoke :public EffectBase
{
private:

public:
	EffectThowSmoke() {};
	~EffectThowSmoke() {};

	//����������
	void Init();
	//�X�V����
	void Play(VECTOR3 Pos, int Num);
	//�X�V����
	void Update();
};

class EffectTowerBreak :public EffectBase
{
private:

public:
	EffectTowerBreak() {};
	~EffectTowerBreak() {};

	//����������
	void Init();
	//�X�V����
	void Play(VECTOR3 Pos, int Num);
	//�X�V����
	void Update();
};

class EffectStageClear :public EffectBase
{
private:

public:
	EffectStageClear() {};
	~EffectStageClear() {};

	//����������
	void Init();
	//�X�V����
	void Play(VECTOR3 Pos, int Num);
	//�X�V����
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

	//����������
	void Init();
	//�X�V����
	void Play(VECTOR3 Pos, int Num);
	//�X�V����
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

	//����������
	void Init();
	//�X�V����
	void Play(VECTOR3 Pos, int Num);
	//�X�V����
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

	//����������
	void Init();
	//�X�V����
	void Play(VECTOR3 Pos, int Num);
	//�X�V����
	void Update();
};

