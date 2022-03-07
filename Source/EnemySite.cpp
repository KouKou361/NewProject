#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"

#include "Scene.h"
#include"EffectManager.h"
#include "EffectBase.h"

void EnemySite::Init()
{
	SetQuaternion({ 0,0,0,1 });
	SetPos({ 0,0,0 });
	SetScale({ 0.05f,0.05f,0.05f });

	SetModel(-1);//-1�͕`�悵�Ȃ�
	SetHp(5);
	SetMaxHp(GetHp());
	speed = 0.4f;
	collisionRadius = 1.0f;
//	SetModel(TK_Lib::Load::GetModel("Boss"));
	SetEnemyTag(EnemyTag::BossSite);

	anime = make_unique<Animetion>();
	//�A�j���[�V�����ԍ�
	string AnimeIndex[] =
	{
		"Open",
		"OpenGoToRoll",
		"Idle",
		"CloseStopRoll",
		"Walk",
		"Close_RollLoop",
		"Close",
		anime->End,
	};
	//�A�j���[�V�����̓o�^
	for (int i = 0; anime->End != AnimeIndex[i]; i++)
	{
		anime->Register(i, AnimeIndex[i]);
	}
	SetTag(ObjectTag::TagEnemy);
	collisionRadius = 5;

	AttackMinions.clear();
	//SetCollisionRadius()

	//TK_Lib::Model::PlayAnimation(GetModel(), 2, true);


	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("", "root", 1, BehaviorTree::SelectRule::Priority, nullptr, nullptr);
	behaviorTree->AddNode("root", "Die", 0, BehaviorTree::SelectRule::Non, new DeadJudgement(this), new BossSiteDieAction(this));
}


//�X�V����
void EnemySite::Update()
{
	//���S�t���O��_���[�W�t���O�����Ă��Ȃ����m�F
	FlgCheak();

	SetMoveVec({ 0,0,0 });
	
	//�r�w�C�r�A�c���[�̍s������
	ActionBehaviorTree();
	//if (ActionNode == nullptr)
	//{
	//	ActionNode = behaviorTree->ActiveNodeInference(this, behaviordata.get());
	//	//if(ActionNode)ActionNode->ImguiDebug();
	//
	//}
	//if (ActionNode != nullptr)
	//{
	//	ActionNode = behaviorTree->Run(this, ActionNode, behaviordata.get());
	//}
	////�n�ʂ̕␳
	//VerticalCollision();
	////�G�̉�]
	//Turn(moveVec);
	////�G�̈ړ�
	//Move();
	////�ߋ��̒n�_�̕ۑ�
	//SetOldPos(GetPos());
	////�s��Ȃǂ̍X�V����
	//Charactor::Update();
}


//�_���[�W�𔻒�
bool EnemySite::AddDamage(int Damage, int SetinvincibleTime)
{
	//�̗͂�0�ȉ��Ȃ�
	if (GetHp() <= 0)return false;

	hp -= Damage;
	//���������c���Ă����Ȃ�
	if (hp >= 1)
	{
		//�ߋ��Ƀ_���[�W���󂯂��B
		oldDamageFlg = true;
		
		//�_���[�W�t���O�̃I��
		SetDamageFlg(true);
	}
	else//���S���Ă���Ȃ�
	{
		TargetFaild();
		//targetFlg = TargetFlg::Failed;
		//�_���[�W�t���O�̃I��
		SetDeadFlg(true);
		GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("Fire")->Play(GetPos(), 10);
	}
	return true;
}


