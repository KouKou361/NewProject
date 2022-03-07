#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"

void EnemyBeholder::Init()
{
	SetQuaternion({ 0,0,0,1 });
	SetPos({ 7,0,0 });
	SetScale({ 0.025f,0.025f,0.025f });
	speed = 0.4f;
	collisionRadius = 1.0f;
	SetModel(TK_Lib::Load::GetModel("Beholder"));

	SetTag(ObjectTag::TagEnemy);

	anime = make_unique<Animetion>();
	//�A�j���[�V�����ԍ�
	string AnimeIndex[] =
	{
		anime->Idle,//"IdeleNormal",
		"IdeleBattle",
		anime->Attack1,//"Attack01",
		"Attack02ST",
		"Attack02RPT",
		"Attack03",
		"WalkFWD",
		"WalkLeft",
		"WalkRight",
		"WalkBWD",
		anime->Run,//"Run",
		"SeneseSomethingST",
		"ScneneSomethingRPT",
		"Taunting",
		"Victory",
		anime->Damage,//"GetHit",
		"Dizzy",
		anime->Die,//"Die",
		anime->End,//"End",
	};
	//�A�j���[�V�����̓o�^
	for (int i = 0; anime->End != AnimeIndex[i]; i++)
	{
		anime->Register(i, AnimeIndex[i]);
	}
	AttackMinions.clear();

	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("", "root", 1, BehaviorTree::SelectRule::Priority, nullptr, nullptr);
	behaviorTree->AddNode("root", "idle", 1, BehaviorTree::SelectRule::Non, new IdleJudgement(this), new IdleAction(this));
}