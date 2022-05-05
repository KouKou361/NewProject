#pragma once
#include "ActionBase.h"
class Sirobo;

//�s���������N���X
class  SiroboActionBase:public ActionBase
{
public:
	SiroboActionBase(){}
	SiroboActionBase(Sirobo* sirobo) :siroboOwner(sirobo) {};
	~SiroboActionBase(){}
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
	Sirobo* siroboOwner = nullptr;
};

