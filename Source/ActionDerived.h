#pragma once
#include "ActionBase.h"
#include "Lib.h"
class EnemyBase;


//�ҋ@�s��
class IdleAction :public ActionBase
{
public:
	IdleAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();
};

// �ǐՍs��
class PursuitAction : public ActionBase
{
private:
	bool searchFlg=false;
	VECTOR3 targetPos = { 0,0,0 };
public:
	PursuitAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

private:

	//�^�[�Q�b�g�Ɍ������Đi�ށB
	bool PursuitTarget();


};

// �U���s��
class AttackAction : public ActionBase
{
public:
	AttackAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

	//DebugRender
	void DebugRender();
};

// �_���[�W�s��
class DamageAction : public ActionBase
{
public:
	DamageAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();
};


// ���S�s��
class DeadAction : public ActionBase
{
public:
	DeadAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();
};

//��]�U���J�n
class BossEntry : public ActionBase
{
public:
	BossEntry(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();
};

//��]�U���J�n
class BossRollAttackStartAction : public ActionBase
{
public:
	BossRollAttackStartAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();



	//Imgui�f�o�b�O
	void DebugImgui();
private:
	//
	void PlayerToTurn();
	//���n�T�E���h
	void BossJumpDownSound();
};

//��]�U��
class BossRollAttackAction : public ActionBase
{
private:

public:
	BossRollAttackAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

private:
	//�ǂɂԂ��������ǂ���
	bool ContactWall();
	//�O�i
	void Advance(const float AdvanceSpeed);
};

//��]�U���I��
class BossRollAttackEndAction : public ActionBase
{
public:
	BossRollAttackEndAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

private:
	//���n�T�E���h
	void BossJumpDownSound();
};


//�ҋ@�s��
class BossIdeiAction :public ActionBase
{
private:
	float ideiTimer=0;
public:
	BossIdeiAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();
};


//�{�X�̈ړ��s��
class BossWalkAction :public ActionBase
{
private:
	int timer = 0;
	VECTOR3 targetPos;//�ړ�����ڕW�n�_
public:
	BossWalkAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

	void Advance(const float AdvanceSpeed);
private:
	void SetTargetPos();
};


//�{�X�̎��S�s��
class BossDeadAction : public ActionBase
{
private:
	enum class EventDeleteState
	{
		NONE,
		STOP,//�~�܂�
		FIRE,//�R����
		EXPLOSION,//����
		END,
	};
	EventDeleteState state= EventDeleteState::NONE;
public:
	BossDeadAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

	void StateStop();
	void StateFire();
	void StateExplosion();
	void StateEnd();
};

//�{�X�̕��ʔj��
class BossSiteDieAction :public ActionBase
{
private:
	
public:
	BossSiteDieAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();
};









