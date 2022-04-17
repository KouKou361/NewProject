#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"

void EnemyBoom::Init()
{
	SetQuaternion({ 0,0,0,1 });
	SetPos({ 7,0,0 });
	SetScale({ 0.025f,0.025f,0.025f });
	speed = 0.4f;
	collisionRadius = 1.0f;
	SetModel(TK_Lib::Load::GetModel("Boom"));

	anime = make_unique<Animetion>();
	//アニメーション番号
	string AnimeIndex[] =
	{
		anime->Idle,//"IdeleNormal",
		anime->Run,//"Walk",
		anime->Damage,//"Damage"
		anime->Attack1,//"Attack01",
		anime->End,
	};
	//アニメーションの登録
	for (int i = 0; anime->End != AnimeIndex[i]; i++)
	{
		anime->Register(i, AnimeIndex[i]);
	}
	SetTag(ObjectTag::TAG_ENEMY);
	SetEnemyTag(EnemyTag::Boom);
	AttackMinions.clear();

	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("", "root", 1, BehaviorTree::SelectRule::PRIORITY, nullptr, nullptr);
}