#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"

void EnemyChest::Init()
{
	SetQuaternion({ 0,0,0,1 });
	//SetPos({ 7,0,0 });
	SetScale({ 0.07f,0.07f,0.07f });
	speed = 0.4f;
	SetHp(20);
	SetMaxHp(GetHp());
	collisionRadius = 2.0f;
	SetModel(TK_Lib::Load::GetModel("ChestEnemy"));
	SetTag(ObjectTag::TAG_ENEMY);
	SetEnemyTag(EnemyTag::Cheast);

	AttackNode = "LowerTeethCTRL";
	anime = make_unique<Animetion>();
	//アニメーション番号
	string AnimeIndex[] =
	{
		anime->Idle,//"IdeleChest",
		"IdeleNormal",
		"IdeleBattle",
		anime->Attack1,//"Attack01",
		"Attack02",
		"Taunting",
		"Victory",
		"WalkFWD",
		"WalkBWD",
		"WalkLeft",
		"WalkRight",
		anime->Run,//"Run",
		"SeneseSomethingST",
		"ScneneSomethingRPT",
		anime->Damage,//"GetHit",
		"Dizzy",
		anime->Die,//"Die",
		anime->End,//"End",
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
	SetMaxBeAttacked(4);
}