#pragma once
//�����̓~�j�I����AI�N���X
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

	//�X�V����
	void Update();

	//�s���̃��Z�b�g
	void ResetNode();
private:

	
	NodeBase* actionNode = nullptr;
	unique_ptr<BehaviorTree> behaviorTree = nullptr;
	unique_ptr<BehaviorData> behaviordata = nullptr;

	Sirobo* owner=nullptr;
	Player* player = nullptr;



};