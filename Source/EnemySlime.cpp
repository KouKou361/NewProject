#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"

void EnemySlime::Init()
{
	SetQuaternion({ 0,0,0,1 });
	//pos = { 7,0,0 };
	SetScale({ 0.025f,0.025f,0.025f });
	speed = 0.4f;
	collisionRadius = 1.0f;
	SetModel(TK_Lib::Load::GetModel("Slime"));

	SetHp(6);
	SetMaxHp(GetHp());

	SetTag(ObjectTag::TAG_ENEMY);
	SetEnemyTag(EnemyTag::Slime);

	AttackNode = "EyeBall";

	anime = make_unique<Animetion>();
	//アニメーション番号
	string AnimeIndex[] =
	{
		anime->Idle,//"IdeleNormal",
		"IdeleBattle",
		anime->Attack1,//"Attack01",
		"Attack02",
		"WalkFWD",
		"WalkBWD",
		"WalkLeft",
		"WalkRight",
		anime->Run,//"RunFWD",
		"SeneseSomethingST",
		"ScneneSomethingRPT",
		"Taunt",
		"Victory",
		anime->Damage,//"GetHit",
		"Dizzy",
		anime->Die,//"Die",
		anime->End//"End",
	};

	AttackMinions.clear();

	//アニメーションの登録
	for (int i = 0; anime->End != AnimeIndex[i]; i++)
	{
		anime->Register(i, AnimeIndex[i]);
	}

	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("", "root", 0, BehaviorTree::SelectRule::PRIORITY, nullptr, nullptr);
	behaviorTree->AddNode("root", "damage", 1, BehaviorTree::SelectRule::NONE, new DamageJudgement(this), new DamageAction(this));
	behaviorTree->AddNode("root", "dead", 2, BehaviorTree::SelectRule::NONE, new DeadJudgement(this), new DeadAction(this));
	behaviorTree->AddNode("root", "attack", 3, BehaviorTree::SelectRule::NONE, new AttackJudgement(this), new AttackAction(this));
	behaviorTree->AddNode("root", "pursuit", 4, BehaviorTree::SelectRule::NONE, new PursuitJudgement(this), new PursuitAction(this));
	behaviorTree->AddNode("root", "idle", 5, BehaviorTree::SelectRule::NONE, new IdleJudgement(this), new IdleAction(this));

	//ミニオンが攻撃してくる最大数
	SetMaxBeAttacked(3);
}