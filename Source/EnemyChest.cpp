#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"

void EnemyChest::Init()
{
	//�X�e�[�^�X�̐ݒ�
	SetStatus("Chest");
	//���f������
	SetModel(TK_Lib::Load::GetModel("ChestEnemy"));
	//�A�j���V�����ݒ�
	SetAnimetion();
	//�^�O�t��
	SetTag(ObjectTag::TAG_ENEMY);
	SetEnemyTag(EnemyTag::CHEAST);


	//�G���|�������ɁA�o������o���l�̐�
	const int DestroyExpNum = 30;
	ExpNum = DestroyExpNum;

	//�V���{�B�̍U�����󂯂郊�X�g���N���A�i�O�̂��߁j
	attackSirobo.clear();

	//behaviorTree�̐ݒ�
	SetBehaviorTree();
}


//�A�j���V�����ݒ�
void EnemyChest::SetAnimetion()
{
	anime = make_unique<Animetion>();
	//�A�j���[�V�����ԍ�
	string AnimeIndex[] =
	{
		anime->Idle,//"IdeleChest",
		"IdeleNormal",
		"IdeleBattle",
		anime->Attack1,//"Attack01",
		"Attack02",
		"Taunting",
		"Victory",
		"WalkFWD",
		"WalkBWD",
		"WalkLeft",
		"WalkRight",
		anime->Run,//"Run",
		"SeneseSomethingST",
		"ScneneSomethingRPT",
		anime->Damage,//"GetHit",
		"Dizzy",
		anime->Die,//"Die",
		anime->End,//"End",
	};
	//�A�j���[�V�����̓o�^
	anime->AllAnimetionKey(&AnimeIndex[0]);

}

//behaviorTree�̐ݒ�
void EnemyChest::SetBehaviorTree()
{

	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();

	behaviorTree->AddNode("", "root",       0, BehaviorTree::SelectRule::PRIORITY, nullptr, nullptr);
	behaviorTree->AddNode("root", "damage", 1, BehaviorTree::SelectRule::NONE,     new DamageJudgement(this), new DamageAction(this));
	behaviorTree->AddNode("root", "dead",   2, BehaviorTree::SelectRule::NONE,     new DeadJudgement(this),   new DeadAction(this));
	behaviorTree->AddNode("root", "attack", 3, BehaviorTree::SelectRule::NONE,     new AttackJudgement(this), new AttackAction(this));
	behaviorTree->AddNode("root", "pursuit",4, BehaviorTree::SelectRule::NONE,     new PursuitJudgement(this),new PursuitAction(this));
	behaviorTree->AddNode("root", "idle",   5, BehaviorTree::SelectRule::NONE,     new IdleJudgement(this),   new IdleAction(this));
}

