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
	bool searchFlg;
	VECTOR3 targetPos;
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

	void PlayerToTurn();

	//Imgui�f�o�b�O
	void DebugImgui();
};

//��]�U��
class BossRollAttackAction : public ActionBase
{
private:
	float rollTimer = 0;
	static constexpr float RollTimerMax = 180;
public:
	BossRollAttackAction(EnemyBase* enemy) :ActionBase(enemy) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�O�i
	void Advance(const float AdvanceSpeed);

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();
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
};


//�{�X�̎��S�s��
class BossDeadAction : public ActionBase
{
private:
	enum class EventDeleteState
	{
		STOP,//�~�܂�
		FIRE,//�R����
		EXPLOSION,//����
		END,
	};
	EventDeleteState state;
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









