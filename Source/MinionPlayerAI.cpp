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

	behaviorTree->AddNode("", "root", 0, BehaviorTree::SelectRule::Priority, nullptr, nullptr);

	//���A�N�V����
	behaviorTree->AddNode("root",   "Resuscitation", 0, BehaviorTree::SelectRule::Priority, new MinionResuscitationJudgement(owner), new MinionResuscitationAction(owner));
	behaviorTree->AddNode("root",   "Die",           1, BehaviorTree::SelectRule::Priority, new MinionDieJudgement(owner), new MinionDieAction(owner));
	behaviorTree->AddNode("root",   "Follow",        2, BehaviorTree::SelectRule::Priority, new MinionFollowJudgement(owner), nullptr);

	//�U��
	behaviorTree->AddNode("Follow", "Battle",        3, BehaviorTree::SelectRule::Sequence, new MinionBattleJudgement(owner),nullptr);
	behaviorTree->AddNode("Battle", "Throw",         0, BehaviorTree::SelectRule::Non, new MinionThrowJudgement(owner), new MinionThrowAction(owner));
	behaviorTree->AddNode("Battle", "Attack",        0, BehaviorTree::SelectRule::Non, new MinionAttackJudgement(owner), new MinionAttackAction(owner));

	//�A��
	behaviorTree->AddNode("Follow", "Stand by",      4, BehaviorTree::SelectRule::Priority, new MinionStandByJudgement(owner), new MinionStandByAction(owner));
	behaviorTree->AddNode("Follow", "Back",          5, BehaviorTree::SelectRule::Priority, new MinionBackJudgement(owner), new MinionBackAction(owner));

	 
	 behaviorTree->AddNode("root", "Idle", 3, BehaviorTree::SelectRule::Priority, new MinionIdleJudgement(owner), new MinionIdleAction(owner));
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
	if (ActionNode == nullptr)
	{
		ActionNode = behaviorTree->ActiveNodeInference(owner, behaviordata.get());
	}



	if (ActionNode != nullptr)
	{
		
		if (ActionNode)ActionNode->ImguiDebug();
		
		ActionNode = behaviorTree->Run(owner, ActionNode, behaviordata.get());
	}


}
void MinionPlayerAI::ResetNode()
{
	//ActionNode = nullptr;
	ActionNode->NodeActionEnd();
	ActionNode = behaviorTree->ActiveNodeInference(owner, behaviordata.get());

	//behaviordata->Init();
}

