#include "MinionPlayerAI.h"
#include "Player.h"
#include "MinionPlayer.h"
#include "NodeBase.h"
#include "MinionActionDerived.h"
#include "MinionJudgementDerived.h"
//����������
MinionPlayerAI::MinionPlayerAI(
	MinionPlayer* minion,
	Player* player
)
{
	owner = minion;
	player = player;
	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();

	behaviorTree->AddNode("", "root", 0, BehaviorTree::SelectRule::PRIORITY, nullptr, nullptr);

	//���A�N�V����
	behaviorTree->AddNode("root",   "Resuscitation", 0, BehaviorTree::SelectRule::PRIORITY, new MinionResuscitationJudgement(owner), new MinionResuscitationAction(owner));
	behaviorTree->AddNode("root",   "Die",           1, BehaviorTree::SelectRule::PRIORITY, new MinionDieJudgement(owner), new MinionDieAction(owner));
	behaviorTree->AddNode("root",   "Follow",        2, BehaviorTree::SelectRule::PRIORITY, new MinionFollowJudgement(owner), nullptr);

	//�U��
	behaviorTree->AddNode("Follow", "Battle",        3, BehaviorTree::SelectRule::SEQUENCE, new MinionBattleJudgement(owner),nullptr);
	behaviorTree->AddNode("Battle", "Throw",         0, BehaviorTree::SelectRule::NONE, new MinionThrowJudgement(owner), new MinionThrowAction(owner));
	behaviorTree->AddNode("Battle", "Attack",        0, BehaviorTree::SelectRule::NONE, new MinionAttackJudgement(owner), new MinionAttackAction(owner));

	//�A��
	behaviorTree->AddNode("Follow", "Stand by",      4, BehaviorTree::SelectRule::PRIORITY, new MinionStandByJudgement(owner), new MinionStandByAction(owner));
	behaviorTree->AddNode("Follow", "Back",          5, BehaviorTree::SelectRule::PRIORITY, new MinionBackJudgement(owner), new MinionBackAction(owner));

	 
	 behaviorTree->AddNode("root", "Idle", 3, BehaviorTree::SelectRule::PRIORITY, new MinionIdleJudgement(owner), new MinionIdleAction(owner));
	  //  behaviorTree->AddNode("follow", "attack", 1, BehaviorTree::SelectRule::Non, new MinionAttackJudgement(owner), new MinionAttackAction(owner));

	//
	//
	//       - idle(�v���C���[���߂��ɂ����猩���ɂȂ�)
	// 
	// 
	//root-- 
	// 
	// 
	//       - follow - stand by  (���Ă����@�U��OK)
	// 	              - attack�@�@(�U��)
	// 	              - back�@�@�@(�P��)
	// 	              - throw�@ �@(������)
	//
}
//�X�V����
void MinionPlayerAI::Update()
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
void MinionPlayerAI::ResetNode()
{
	//ActionNode = nullptr;
	actionNode->NodeActionEnd();
	actionNode = behaviorTree->ActiveNodeInference(owner, behaviordata.get());

	//behaviordata->Init();
}

