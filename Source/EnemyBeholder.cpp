#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"


//お蔵入りの敵
//浮遊物の敵でした。
//残念

void EnemyBeholder::Init()
{
	assert(L"エラー：お蔵入りの敵を生成しようとしました！");
//	SetQuaternion({ 0,0,0,1 });
//	SetPos({ 7,0,0 });
//	SetScale({ 0.025f,0.025f,0.025f });
//	speed = 0.4f;
//	collisionRadius = 1.0f;
//	SetModel(TK_Lib::Load::GetModel("Beholder"));
//
//	SetTag(ObjectTag::TAG_ENEMY);
//
//SetAnimetion()
// 
//	AttackSirobos.clear();
//
	//behaviorTreeの設定
	//SetBehaviorTree();
}


void EnemyBeholder::SetAnimetion()
{
	//	anime = make_unique<Animetion>();
//	//アニメーション番号
//	string AnimeIndex[] =
//	{
//		anime->Idle,//"IdeleNormal",
//		"IdeleBattle",
//		anime->Attack1,//"Attack01",
//		"Attack02ST",
//		"Attack02RPT",
//		"Attack03",
//		"WalkFWD",
//		"WalkLeft",
//		"WalkRight",
//		"WalkBWD",
//		anime->Run,//"Run",
//		"SeneseSomethingST",
//		"ScneneSomethingRPT",
//		"Taunting",
//		"Victory",
//		anime->Damage,//"GetHit",
//		"Dizzy",
//		anime->Die,//"Die",
//		anime->End,//"End",
//	};
//	//アニメーションの登録
//	for (int i = 0; anime->End != AnimeIndex[i]; i++)
//	{
//		anime->Register(i, AnimeIndex[i]);
//	}
}

//behaviorTreeの設定
void EnemyBeholder::SetBehaviorTree()
{
	//	behaviorTree = make_unique<BehaviorTree>();
//	behaviordata = make_unique<BehaviorData>();
//	behaviorTree->AddNode("", "root", 1, BehaviorTree::SelectRule::PRIORITY, nullptr, nullptr);
//	behaviorTree->AddNode("root", "idle", 1, BehaviorTree::SelectRule::NONE, new IdleJudgement(this), new IdleAction(this));
}
