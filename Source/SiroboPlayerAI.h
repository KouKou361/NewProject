#pragma once
//ここはミニオンのAIクラス
#include "BehaviorTree.h"
#include "BehaviorData.h"
class Sirobo;
class Player;



class SiroboPlayerAI
{
public:
	SiroboPlayerAI() {};
	SiroboPlayerAI(
		Sirobo* sirobo,
		Player* player
	);
	~SiroboPlayerAI() {};

	//更新処理
	void Update();

	//行動のリセット
	void ResetNode();
private:

	
	NodeBase* actionNode = nullptr;
	unique_ptr<BehaviorTree> behaviorTree = nullptr;
	unique_ptr<BehaviorData> behaviordata = nullptr;

	Sirobo* owner=nullptr;
	Player* player = nullptr;



};