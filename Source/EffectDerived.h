#pragma once
#include "EffectBase.h"

class EffectFire :public EffectBase
{
private:
	int pointLight = 0;


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
	const float UpdateScale = 0.005f;//�G�t�F�N�g���傫���Ȃ�
	static constexpr float AlphaRate = 0.2f;
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
	const VECTOR3   VelocityRate = { 15.9f,20.3f ,15.9f };
	const VECTOR3 Acceleration = { 0.1f,-10.0f ,0.1f};
	const float PosUP = 5.0f;
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

