#pragma once
#include "ActionBase.h"
class MinionPlayer;

//�s���������N���X
class  MinionActionBase:public ActionBase
{
public:
	MinionActionBase(){}
	MinionActionBase(MinionPlayer* minion) :minionOwner(minion) {};
	~MinionActionBase(){}
	// ���s���
	enum class State
	{
		Run,//���s��
		Failed,		// ���s���s
		Complete,	// ���s����
	};

	//���s�J�n����
	virtual void Start() = 0;

	//���s����
	virtual ActionBase::State Run() = 0;

	//���s�I������
	virtual void End() = 0;

	//Imgui
	virtual void DebugImgui() = 0;

	//�����ڕW���������Ă��܂����ꍇ
	virtual ActionBase::State DeleteTarget();

protected:
	MinionPlayer* minionOwner = nullptr;
};

