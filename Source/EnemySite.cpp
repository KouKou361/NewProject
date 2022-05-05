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
	//ステータス設定
	SetStatus("Site");
	//モデル生成
	SetModel(-1);//-1は描画しない

	//アニメション設定
	SetAnimetion();

	//タグ付き
	SetEnemyTag(EnemyTag::BOSS_SITE);
	SetTag(ObjectTag::TAG_ENEMY);

	//シロボ達の攻撃を受けるリストをクリア（念のため）
	attackSirobo.clear();

	//behaviorTreeの設定
	SetBehaviorTree();

	
}


//更新処理
void EnemySite::Update()
{
	//死亡フラグやダメージフラグが来ていないか確認
	FlgCheak();

	SetMoveVec({ 0,0,0 });
	
	//ビヘイビアツリーの行動処理
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
	////地面の補正
	//VerticalCollision();
	////敵の回転
	//Turn(moveVec);
	////敵の移動
	//Move();
	////過去の地点の保存
	//SetOldPos(GetPos());
	////行列などの更新処理
	//Charactor::Update();
}


//ダメージを判定
bool EnemySite::AddDamage(int Damage, float SetinvincibleTime)
{
	//体力が0以下なら
	if (GetHp() <= 0)return false;

	hp -= Damage;
	//もし生き残っていたなら
	if (hp >= 1)
	{
		//過去にダメージを受けた。
		oldDamageFlg = true;
		
		//ダメージフラグのオン
		SetDamageFlg(true);
	}
	else//死亡しているなら
	{
		TargetFaild();
		//targetFlg = TargetFlg::Failed;
		//ダメージフラグのオン
		SetDeadFlg(true);
		GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("Fire")->Play(GetPos(), 10);
	}
	return true;
}

//アニメション設定
void EnemySite::SetAnimetion()
{
	anime = make_unique<Animetion>();
	//アニメーション番号
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
	//アニメーションの登録
	anime->AllAnimetionKey(&AnimeIndex[0]);
}

//behaviorTreeの設定
void EnemySite::SetBehaviorTree()
{
	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("",     "root", 1, BehaviorTree::SelectRule::PRIORITY, nullptr,                 nullptr);
	behaviorTree->AddNode("root", "Die" , 0, BehaviorTree::SelectRule::NONE,     new DeadJudgement(this), new BossSiteDieAction(this));
}




