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
	//ステータスの設定
	SetStatus("Dummy");
	//モデル生成
	SetModel(TK_Lib::Load::GetModel("Dummy"));
	//アニメション設定
	SetAnimetion();

	//タグ付き
	SetTag(ObjectTag::TAG_ENEMY);
	SetEnemyTag(EnemyTag::DUMMY_ENEMY);

	//シロボ達の攻撃を受けるリストをクリア（念のため）
	attackSirobo.clear();

	//behaviorTreeの設定
	SetBehaviorTree();


}


//アニメション設定
void EnemyDummy::SetAnimetion()
{

	anime = make_unique<Animetion>();
	//アニメーション番号
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
	//アニメーションの登録
	anime->AllAnimetionKey(&AnimeIndex[0]);


}

//behaviorTreeの設定
void EnemyDummy::SetBehaviorTree()
{
	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("", "root",       0, BehaviorTree::SelectRule::PRIORITY, nullptr,                   nullptr);
	behaviorTree->AddNode("root", "damage", 1, BehaviorTree::SelectRule::NONE,     new DamageJudgement(this), new DamageAction(this));
	behaviorTree->AddNode("root", "dead",   2, BehaviorTree::SelectRule::NONE,     new DeadJudgement(this),   new DeadAction(this));
}

