#pragma once
#include "MinionActionBase.h"
#include "Lib.h"
class EnemyBase;


//�ҋ@�s��
class MinionIdleAction :public MinionActionBase
{
public:
	MinionIdleAction(MinionPlayer* minion) :MinionActionBase(minion) {}

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
class MinionStandByAction :public MinionActionBase
{
public:
	MinionStandByAction(MinionPlayer* minion) :MinionActionBase(minion) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();



	//�I������
	void End();
	
	//�Q�O
	void Flock();

	void MinionVsMinion();
	void VsPlayer();

	//Imgui�f�o�b�O
	void DebugImgui();

	//�����ڕW���������Ă��܂����ꍇ
	ActionBase::State DeleteTarget();
};


// �P��
class MinionBackAction : public MinionActionBase
{
public:
	MinionBackAction(MinionPlayer* minion) :MinionActionBase(minion) {}

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
class MinionPursuitAction : public MinionActionBase
{
private:
	bool searchFlg;
	VECTOR3 targetPos;
public:
	MinionPursuitAction(MinionPlayer* minion) :MinionActionBase(minion) {}

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
class MinionAttackAction : public MinionActionBase
{
public:
	MinionAttackAction(MinionPlayer* minion) :MinionActionBase(minion) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�����t������
	bool EnemyStick();

	//�����t������
	bool Stick();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();
};

// ��������s��
class MinionThrowAction : public MinionActionBase
{
private:

	float velocity = 0.0f;

public:
	MinionThrowAction(MinionPlayer* minion) :MinionActionBase(minion) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//�����蔻�菈��
	bool HitCollision();

	//Imgui�f�o�b�O
	void DebugImgui();

	//�����ڕW���������Ă��܂����ꍇ
	virtual ActionBase::State DeleteTarget();


};

// �ǐՍs��
class MinionDieAction : public MinionActionBase
{
private:
	bool searchFlg;
	VECTOR3 targetPos;
public:
	MinionDieAction(MinionPlayer* minion) :MinionActionBase(minion) {}

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
class MinionResuscitationAction : public MinionActionBase
{
private:
	bool searchFlg;
	VECTOR3 targetPos;
public:
	MinionResuscitationAction(MinionPlayer* minion) :MinionActionBase(minion) {}

	//�J�n����
	void Start();

	//���s����
	ActionBase::State Run();

	//�I������
	void End();

	//Imgui�f�o�b�O
	void DebugImgui();

	//�h������
	void Resuscitation();
	//�h���X�V����
	void UpdateResuscitation();

	//�����ڕW���������Ă��܂����ꍇ
	ActionBase::State DeleteTarget();
};




