#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"


//��������̓G
//���V���̓G�ł����B
//�c�O

void EnemyBeholder::Init()
{
	assert(L"�G���[�F��������̓G�𐶐����悤�Ƃ��܂����I");
//	SetQuaternion({ 0,0,0,1 });
//	SetPos({ 7,0,0 });
//	SetScale({ 0.025f,0.025f,0.025f });
//	speed = 0.4f;
//	collisionRadius = 1.0f;
//	SetModel(TK_Lib::Load::GetModel("Beholder"));
//
//	SetTag(ObjectTag::TAG_ENEMY);
//
//SetAnimetion()
// 
//	AttackSirobos.clear();
//
	//behaviorTree�̐ݒ�
	//SetBehaviorTree();
}


void EnemyBeholder::SetAnimetion()
{
	//	anime = make_unique<Animetion>();
//	//�A�j���[�V�����ԍ�
//	string AnimeIndex[] =
//	{
//		anime->Idle,//"IdeleNormal",
//		"IdeleBattle",
//		anime->Attack1,//"Attack01",
//		"Attack02ST",
//		"Attack02RPT",
//		"Attack03",
//		"WalkFWD",
//		"WalkLeft",
//		"WalkRight",
//		"WalkBWD",
//		anime->Run,//"Run",
//		"SeneseSomethingST",
//		"ScneneSomethingRPT",
//		"Taunting",
//		"Victory",
//		anime->Damage,//"GetHit",
//		"Dizzy",
//		anime->Die,//"Die",
//		anime->End,//"End",
//	};
//	//�A�j���[�V�����̓o�^
//	for (int i = 0; anime->End != AnimeIndex[i]; i++)
//	{
//		anime->Register(i, AnimeIndex[i]);
//	}
}

//behaviorTree�̐ݒ�
void EnemyBeholder::SetBehaviorTree()
{
	//	behaviorTree = make_unique<BehaviorTree>();
//	behaviordata = make_unique<BehaviorData>();
//	behaviorTree->AddNode("", "root", 1, BehaviorTree::SelectRule::PRIORITY, nullptr, nullptr);
//	behaviorTree->AddNode("root", "idle", 1, BehaviorTree::SelectRule::NONE, new IdleJudgement(this), new IdleAction(this));
}
