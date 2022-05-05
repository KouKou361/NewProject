#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"

void EnemyTurtleShell::Init()
{
	
	//ステータス設定
	SetStatus("TurtleShell");
	//モデル生成
	SetModel(TK_Lib::Load::GetModel("TurtleShell"));

	//アニメション設定
	SetAnimetion();

	//タグ付き
	SetTag(ObjectTag::TAG_ENEMY);
	SetEnemyTag(EnemyTag::TURTLESHELL);

	//シロボ達の攻撃を受けるリストをクリア（念のため）
	attackSirobo.clear();

	//behaviorTreeの設定
	SetBehaviorTree();

	
	

}



//アニメション設定
void EnemyTurtleShell::SetAnimetion()
{
	anime = make_unique<Animetion>();
	//アニメーション番号
	string AnimeIndex[] =
	{
		anime->Idle,//"IdeleNormal",
		"IdeleBattle",
		anime->Attack1,//"Attack01",
		"Attack02",
		"WalkFWD",
		"Defend",
		"DefendGetHit",
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
	//アニメーションの登録
	anime->AllAnimetionKey(&AnimeIndex[0]);


}

//behaviorTreeの設定
void EnemyTurtleShell::SetBehaviorTree()
{
	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("",     "root",   0, BehaviorTree::SelectRule::PRIORITY, nullptr,                   nullptr);
	behaviorTree->AddNode("root", "damage", 1, BehaviorTree::SelectRule::NONE,     new DamageJudgement(this), new DamageAction(this));
	behaviorTree->AddNode("root", "dead",   2, BehaviorTree::SelectRule::NONE,     new DeadJudgement(this),   new DeadAction(this));
	behaviorTree->AddNode("root", "attack", 3, BehaviorTree::SelectRule::NONE,     new AttackJudgement(this), new AttackAction(this));
	behaviorTree->AddNode("root", "pursuit",4, BehaviorTree::SelectRule::NONE,     new PursuitJudgement(this),new PursuitAction(this));
																			       
																			       
	behaviorTree->AddNode("root", "idle",   5, BehaviorTree::SelectRule::NONE,     new IdleJudgement(this),   new IdleAction(this));
}

