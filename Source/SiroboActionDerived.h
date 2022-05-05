#pragma once
#include "SiroboActionBase.h"
#include "Lib.h"
class EnemyBase;


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
//�V���{�A�v���C���[�̌�ɂ��Ă����i�����j
class SiroboFollowRun:public SiroboActionBase

{
public:
	SiroboFollowRun(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

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

	//�v���C���[�̓����蔻��
	void VsPlayer();
};






//�V���{�A�v���C���[�̌�ɂ��Ă����i�����j
class SiroboStandByAction :public SiroboActionBase
{
public:
	SiroboStandByAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

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

	//�v���C���[�̓����蔻��
	void VsPlayer();
};


// �P��
class SiroboBackAction : public SiroboActionBase
{
public:
	SiroboBackAction(Sirobo* sirobo) :SiroboActionBase(sirobo) {}

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
	//�v���C���[�����ɑ���
	void RunToThePlaye();
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




