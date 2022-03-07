#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"

void EnemyDummy::Init()
{
	SetQuaternion({ 0,0,0,1 });
	//pos = { 7,0,0 };

	//SetPos({ 7,0,0 });
	SetScale({ 0.025f,0.025f,0.025f });
	speed = 0.4f;
	collisionRadius = 1.0f;
	SetModel(TK_Lib::Load::GetModel("Dummy"));

	SetHp(7);
	SetMaxHp(GetHp());

	SetTag(ObjectTag::TagEnemy);
	SetEnemyTag(EnemyTag::Dummy);

	//AttackNode = "EyeBall";

	//�~�j�I�����U�����Ă���ő吔
	SetMaxBeAttacked(2);

	anime = make_unique<Animetion>();
	//�A�j���[�V�����ԍ�
	string AnimeIndex[] =
	{
		//anime->Idle,//"IdeleNormal",
		//"IdeleBattle",
		//anime->Attack1,//"Attack01",
		//"Attack02",
		//"WalkFWD",
		//"WalkBWD",
		//"WalkLeft",
		//"WalkRight",
		//anime->Run,//"RunFWD",
		//"SeneseSomethingST",
		//"ScneneSomethingRPT",
		//"Taunt",
		//"Victory",
		anime->Damage,//"GetHit",
		//"Dizzy",
		anime->Die,//"Die",
		anime->End//"End",
	};
	//�A�j���[�V�����̓o�^
	for (int i = 0; anime->End != AnimeIndex[i]; i++)
	{
		anime->Register(i, AnimeIndex[i]);
	}

	AttackMinions.clear();

	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("", "root", 0, BehaviorTree::SelectRule::Priority, nullptr, nullptr);
	behaviorTree->AddNode("root", "damage", 1, BehaviorTree::SelectRule::Non, new DamageJudgement(this), new DamageAction(this));
	behaviorTree->AddNode("root", "dead", 2, BehaviorTree::SelectRule::Non, new DeadJudgement(this), new DeadAction(this));
	//behaviorTree->AddNode("root", "attack", 3, BehaviorTree::SelectRule::Non, new AttackJudgement(this), new AttackAction(this));
	//behaviorTree->AddNode("root", "pursuit", 4, BehaviorTree::SelectRule::Non, new PursuitJudgement(this), new PursuitAction(this));
	//behaviorTree->AddNode("root", "idle", 5, BehaviorTree::SelectRule::Non, new IdleJudgement(this), new IdleAction(this));

}