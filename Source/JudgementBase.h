#pragma once
class EnemyBase;

//�s������������N���X
class  JudgementBase
{
public:
	JudgementBase() {};
	JudgementBase(EnemyBase* enemy) :owner(enemy) {};

	//���s����
	virtual bool Judgement() = 0;

protected:
	EnemyBase* owner=nullptr;
};

