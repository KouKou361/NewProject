#pragma once
//ここはミニオンのAIクラス
#include "BehaviorTree.h"
#include "BehaviorData.h"
class MinionPlayer;
class Player;



class MinionPlayerAI
{
public:
	MinionPlayerAI() {};
	MinionPlayerAI(
		MinionPlayer* minion,
		Player* player
	);
	~MinionPlayerAI() {};
	void Update();
	void ResetNode();
private:

	
	NodeBase* actionNode = nullptr;
	unique_ptr<BehaviorTree> behaviorTree = nullptr;
	unique_ptr<BehaviorData> behaviordata = nullptr;

	MinionPlayer* owner;
	Player* player;



};