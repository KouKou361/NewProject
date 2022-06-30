#pragma once
#include "SiroboActionBase.h"
#include "Lib.h"
#include "StandByAnimetion.h"
class EnemyBase;

class BaseStandByAnimetion;
class WalkStandByAnimetion;
class RunStandByAnimetion;
class IdelStandByAnimetion;

//�ҋ@�s��
class SiroboIdleAction :public SiroboActionBase
{
public:
	SiroboIdleAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//�����ڕW���������Ă��܂����ꍇ
	ActionBase::State DeleteTarget();

	//Imgui�f�o�b�O
	void DebugImgui();
};




//�U��OK�s��
class SiroboStandByAction :public SiroboActionBase
{
private:
	BaseStandByAnimetion* current=nullptr;

	WalkStandByAnimetion* walk = nullptr;
	RunStandByAnimetion*  run = nullptr;
	IdelStandByAnimetion* idei = nullptr;
	float speed = 0.0f;
public:
	SiroboStandByAction(Sirobo* minion) :SiroboActionBase(minion) {
		walk = new WalkStandByAnimetion(minion);
		run = new RunStandByAnimetion(minion);
		idei = new IdelStandByAnimetion(minion);
	}

	~SiroboStandByAction()
	{
		delete walk;
		walk = nullptr;
		delete run;
		run = nullptr;
		delete idei;
		idei = nullptr;
	}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

	//�����ڕW���������Ă��܂����ꍇ
	ActionBase::State DeleteTarget();
private:
	//�Q�O
	void Flock();
	//�V���{���m�̓����蔻��
	void SiroboVsSirobo();
	//�v���C���[�Ƃ̓����蔻��
	void VsPlayer();
	//�K�؂ȃA�j���[�V�����Ɉڍs����B
	void AllAppropriateAnimesion();
	//�K�؂ȃA�j���[�V�����Ɉڍs����B
	bool AppropriateAnimesion(BaseStandByAnimetion* anime);
};


// �P��
class SiroboBackAction : public SiroboActionBase
{
public:
	SiroboBackAction(Sirobo* minion) :SiroboActionBase(minion) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

	//�����ڕW���������Ă��܂����ꍇ
	ActionBase::State DeleteTarget();
};


// �ǐՍs��
class SiroboPursuitAction : public SiroboActionBase
{
private:
	bool searchFlg=false;
	VECTOR3 targetPos = {0,0,0};
public:
	SiroboPursuitAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();


};

// �U���s��
class SiroboAttackAction : public SiroboActionBase
{
public:
	SiroboAttackAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

private:
	//�����t������
	bool Stick();

	//�U���ڕW�ɑ΂��čU������
	void AttackTarget();
};

// ��������s��
class SiroboThrowAction : public SiroboActionBase
{
private:

	float velocity = 0.0f;

public:
	SiroboThrowAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

	//�����ڕW���������Ă��܂����ꍇ
	virtual ActionBase::State DeleteTarget();

private:
	//�����蔻�菈��
	bool HitCollision();

	//���f���̓����蔻��
	bool HitCollisioinModel();

	//�G�̓����蔻��
	bool HitEnemy();

	//�I�u�W�F�N�g�̓����蔻��
	bool HitObject();

	//��������`���Đi�ޏ����x�ݒ�
	void SetFirstVelocity();

	//�d�͂̓K��
	void AddGravity();

	//�ڕW�n�_�ɐi��
	void TargetToMove();

};

// �ǐՍs��
class SiroboDieAction : public SiroboActionBase
{
private:
	bool searchFlg=false;
	VECTOR3 targetPos = {0,0,0};
public:
	SiroboDieAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();


};

// �h������Ă��鎞�̍s������
class SiroboResuscitationAction : public SiroboActionBase
{
private:
	bool searchFlg = false;
	VECTOR3 targetPos = {0,0,0};
public:
	SiroboResuscitationAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

	//�����ڕW���������Ă��܂����ꍇ
	ActionBase::State DeleteTarget();
private:

	//�h������
	void Resuscitation();

	//�h���X�V����
	void UpdateResuscitation();
};




