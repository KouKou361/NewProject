#include "SiroboPlayerAI.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "NodeBase.h"
#include "SiroboActionDerived.h"
#include "SiroboJudgementDerived.h"
//初期化処理
SiroboPlayerAI::SiroboPlayerAI(
	Sirobo* sirobo,
	Player* player
)
{
	owner = sirobo;
	player = player;
	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();

	behaviorTree->AddNode("", "root", 0, BehaviorTree::SelectRule::PRIORITY, nullptr, nullptr);

	//リアクション
	behaviorTree->AddNode("root",   "Resuscitation", 0, BehaviorTree::SelectRule::PRIORITY, new SiroboResuscitationJudgement(owner), new SiroboResuscitationAction(owner));
	behaviorTree->AddNode("root",   "Die",           1, BehaviorTree::SelectRule::PRIORITY, new SiroboDieJudgement(owner), new SiroboDieAction(owner));
	behaviorTree->AddNode("root",   "Follow",        2, BehaviorTree::SelectRule::PRIORITY, new SiroboFollowJudgement(owner), nullptr);

	//攻撃
	behaviorTree->AddNode("Follow", "Battle",        3, BehaviorTree::SelectRule::SEQUENCE, new SiroboBattleJudgement(owner),nullptr);
	behaviorTree->AddNode("Battle", "Throw",         0, BehaviorTree::SelectRule::NONE, new SiroboThrowJudgement(owner), new SiroboThrowAction(owner));
	behaviorTree->AddNode("Battle", "Attack",        0, BehaviorTree::SelectRule::NONE, new SiroboAttackJudgement(owner), new SiroboAttackAction(owner));

	//帰還
	behaviorTree->AddNode("Follow", "Stand by",      4, BehaviorTree::SelectRule::PRIORITY, new SiroboStandByJudgement(owner), new SiroboStandByAction(owner));
	behaviorTree->AddNode("Follow", "Back",          5, BehaviorTree::SelectRule::PRIORITY, new SiroboBackJudgement(owner), new SiroboBackAction(owner));

	 
	 behaviorTree->AddNode("root", "Idle", 3, BehaviorTree::SelectRule::PRIORITY, new SiroboIdleJudgement(owner), new SiroboIdleAction(owner));
	  //  behaviorTree->AddNode("follow", "attack", 1, BehaviorTree::SelectRule::Non, new siroboAttackJudgement(owner), new siroboAttackAction(owner));

	//
	//
	//       - idle(プレイヤーが近くにいたら見方になる)
	// 
	// 
	//root-- 
	// 
	// 
	//       - follow - stand by  (ついていく　攻撃OK)
	// 	              - attack　　(攻撃)
	// 	              - back　　　(撤退)
	// 	              - throw　 　(投げる)
	//
}
//更新処理
void SiroboPlayerAI::Update()
{
	if (actionNode == nullptr)
	{
		actionNode = behaviorTree->ActiveNodeInference(owner, behaviordata.get());
	}

	if (actionNode != nullptr)
	{
		
		if (actionNode)actionNode->ImguiDebug();
		
		actionNode = behaviorTree->Run(owner, actionNode, behaviordata.get());
	}


}

//行動のリセット
void SiroboPlayerAI::ResetNode()
{
	//ActionNode = nullptr;
	actionNode->NodeActionEnd();
	actionNode = behaviorTree->ActiveNodeInference(owner, behaviordata.get());

	//behaviordata->Init();
}

