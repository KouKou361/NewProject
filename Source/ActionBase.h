#pragma once
class EnemyBase;
class Charactor;

//�s���������N���X
class  ActionBase
{
public:
	ActionBase(){}
	ActionBase(EnemyBase* enemy) :owner(enemy) {};

	
	virtual ~ActionBase() {}
	// ���s���
	enum class State
	{
		RUN,//���s��
		FAILED,		// ���s���s
		COMPLETE,	// ���s����
	};

	//���s�J�n����
	virtual void Start() = 0;

	//���s����
	virtual ActionBase::State Run() = 0;

	//���s�I������
	virtual void End() = 0;
	//Imgui
	virtual void DebugImgui()=0;
	//�f�o�b�O�p
	virtual void DebugRender() {};

	//�����ڕW���������Ă��܂����ꍇ
	virtual ActionBase::State DeleteTarget();

	//�����^�[�Q�b�g�����Ȃ��Ȃ��Ă��邩�ǂ���
	bool CheakTarget(const Charactor* chara);



protected:
	EnemyBase* owner=nullptr;
};
