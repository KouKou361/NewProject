#pragma once
//�����̃N���X�̈Ӗ��̓V���{���ҋ@���̎��ɓK�؂ȃA�j���[�V�����ɂ���ׂɂ���
class Sirobo;

class BaseStandByAnimetion
{
public:
	BaseStandByAnimetion(){}
	BaseStandByAnimetion(Sirobo* sirobo) :siroboOwner(sirobo) {};
	~BaseStandByAnimetion(){}
protected:
	Sirobo* siroboOwner = nullptr;
public:
	virtual void Init()=0;
	virtual bool Judge(const float Speed) = 0;
};

//����
class WalkStandByAnimetion:public BaseStandByAnimetion
{
public:
	WalkStandByAnimetion() {}
	WalkStandByAnimetion(Sirobo* sirobo) :BaseStandByAnimetion(sirobo) {};
	~WalkStandByAnimetion() {};
public:
	//�؂�ւ�������̏���
	void Init();
	//�؂�ւ�菈��
	bool Judge(const float Speed);
};
//����
class RunStandByAnimetion :public BaseStandByAnimetion
{
public:
	RunStandByAnimetion() {};
	RunStandByAnimetion(Sirobo* sirobo) :BaseStandByAnimetion(sirobo) {};
	~RunStandByAnimetion() {};
public:
	//�؂�ւ�������̏���
	void Init();
	//�؂�ւ�菈��
	bool Judge(const float Speed);
};
//�~�܂�
class IdelStandByAnimetion :public BaseStandByAnimetion
{
public:
	IdelStandByAnimetion() {};
	IdelStandByAnimetion(Sirobo* sirobo) :BaseStandByAnimetion(sirobo) {};
	~IdelStandByAnimetion() {};
public:
	//�؂�ւ�������̏���
	void Init();
	//�؂�ւ�菈��
	bool Judge(const float Speed);
};