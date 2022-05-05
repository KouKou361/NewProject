#pragma once
#include "UIBase.h"

//(�v�f�[�^)
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
private:
	VECTOR4 GageCut = {0,0,0,0};
	VECTOR4 GageblackCut = { 0,0,0,0 };
	
};

//�~�j�I���̃_�E����Ԃ̃w���v�A�C�R��
class UISiroboDownHelp :public UIBase
{
public:
	UISiroboDownHelp() {};
	~UISiroboDownHelp() {};

	//������
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
};

//�G�ɍU�����Ă���~�j�I���̐�
class UISiroboAttack :public UIBase
{
public:
	UISiroboAttack() {};
	~UISiroboAttack() {};

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
	bool towerSound = true;
	int fontUI = -1;
	float breakingTimer = 0;
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

	inline void SetBlinkingTimer(float timer) { breakingTimer = timer; }
private:
	//�e�L�X�g�̕\��
	void RenderText();
};


//���Ԑ���UI
class UITimer :public UIBase
{
private:
	int fontUI=-1;
	float gameTimer=0;
	float maxGameTimer = 0;
	float fontScaleTimer = 0;
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
	void SetGameOverTimer(float timer);

	void AddGameOverTimer(float addTimer);
	inline  float GetGameTimer() { return gameTimer; }
private:
	//�t�H���g�̑傫���̍X�V����
	void UpdateFontScaleTimer();

	//�Q�[�W�̕\��
	void GaugeRender();
	//�Q�[���I�[�o�[�^�C�}�[�̕\��
	void TextRender();
	//�X�N���[�������ς��ɏo�邨�����ȃQ�[���I�[�o�[�^�C�}�[�̕\��
	void BigGameOverTimeText(float RenderTime);
	//�Q�[���I�[�o�[�e�L�X�g
	void GameOverText();

};


class UINextMessage :public UIBase
{
	const VECTOR2 FontOffset = { 50,70 };
	VECTOR2 centerScale;
	VECTOR2 s1 = { 256 / 3,256 / 3 };
	VECTOR2 s2 = { (256 / 3) * 2,(256 / 3) * 2 };
	VECTOR2 scale = { 1,1 };
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
	VECTOR2 s1 = { 256 / 3,256 / 3 };
	VECTOR2 s2 = { (256 / 3) * 2,(256 / 3) * 2 };
	VECTOR2 scale = { 1,1 };



	
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
	VECTOR3 targetWorldPos = {0,0,0};
	VECTOR2 targetScreenPos = {0,0};

	float targetAngle=0;


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
private:
	//�X�N���[�����W�Ń^�[�Q�b�g�̌������Z�o
	void SetTargetAngle();

};









