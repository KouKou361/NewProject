#pragma once
#include "UIBase.h"

//�v���C���[�̗̑�
class UIPlayerHP:public UIBase
{
public:
	UIPlayerHP() {};
	~UIPlayerHP() {};

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
};

//�U���ڕW�̃J�[�\��
class UITargetCursur :public UIBase
{
public:
	UITargetCursur() {};
	~UITargetCursur() {};

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
};


//�ڕW�̗̑͂̃J�[�\��
class UITargetHP :public UIBase
{
public:
	UITargetHP() {};
	~UITargetHP() {};

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
};

//�~�j�I���̃_�E����Ԃ̃w���v�A�C�R��
class UIMinionDownHelp :public UIBase
{
public:
	UIMinionDownHelp() {};
	~UIMinionDownHelp() {};

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
};

//�G�ɍU�����Ă���~�j�I���̐�
class UIMinionAttack :public UIBase
{
public:
	UIMinionAttack() {};
	~UIMinionAttack() {};

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
};

//�^���[�̐�
class UINumTower :public UIBase
{
private:
	bool TowerSound = true;
	int FontUI = -1;
	float BlinkingTimer = 0;
public:
	UINumTower(SceneGame* scene) { this->scene = scene; }
	UINumTower() {};
	~UINumTower() {};

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();

	void SetBlinkingTimer(float timer) { BlinkingTimer = timer; }
};


//���Ԑ���UI
class UITimer :public UIBase
{
private:
	int FontUI=-1;
	int GameTimer=0;
	int MaxGameTimer = 0;
	float FrameTimer=0;
	float FontScaleTimer = 0;
public:
	UITimer() {};
	~UITimer() {};



	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();

	//�Q�[���I�[�o�[�̎��Ԑݒ�
	void SetGameOverTimer(int timer);

	void AddGameOverTimer(int addTimer);
	int GetGameTimer() { return GameTimer; }
};


class UINextMessage :public UIBase
{
	const VECTOR2 FontOffset = { 50,70 };
	VECTOR2 centerScale;
	VECTOR2 S1 = { 256 / 3,256 / 3 };
	VECTOR2 S2 = { (256 / 3) * 2,(256 / 3) * 2 };
	VECTOR2 Scale = { 1,1 };
public:
	UINextMessage() {};
	~UINextMessage() {};

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
};

class UITuto :public UIBase
{
	const VECTOR2 FontOffset = { 50,100 };
	const VECTOR2 NextFontOffset = { 1300,250 };
	VECTOR2 centerScale;
	VECTOR2 S1 = { 256 / 3,256 / 3 };
	VECTOR2 S2 = { (256 / 3) * 2,(256 / 3) * 2 };
	VECTOR2 Scale = { 1,1 };



	
public:

	UITuto() {};
	~UITuto() {};

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
};

//�X�N���[���ɕ���������
class UI2DDirection :public UIBase
{
	VECTOR3 targetWorldPos;
	VECTOR2 targetScreenPos;
	//���a
	const float UICenterR = 250.0f;
	float targetAngle;


public:
	UI2DDirection(SceneGame* scene) { this->scene = scene; }
	UI2DDirection() {};
	~UI2DDirection() {};

	//�ʒu�̐ݒ�
	void SetTargetPos(const VECTOR3 pos);
	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
};









