#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"

//��������̓G
//���S�ɔ������ăV���{�B�Ƀ_���[�W��^����G�ł����B
//�c�O
void EnemyBoom::Init()
{
	assert(L"�G���[�F��������̓G�𐶐����悤�Ƃ��܂����I");
	//SetQuaternion({ 0,0,0,1 });
	//SetPos({ 7,0,0 });
	//SetScale({ 0.025f,0.025f,0.025f });
	//speed = 0.4f;
	//collisionRadius = 1.0f;
	//SetModel(TK_Lib::Load::GetModel("Boom"));
	
	//SetTag(ObjectTag::TAG_ENEMY);
	//SetEnemyTag(EnemyTag::BOMB);
	//AttackSirobos.clear();


	//behaviorTree�̐ݒ�
	//SetBehaviorTree();
}

void EnemyBoom::SetAnimetion()
{
	//
		//anime = make_unique<Animetion>();
		////�A�j���[�V�����ԍ�
		//string AnimeIndex[] =
		//{
		//	anime->Idle,//"IdeleNormal",
		//	anime->Run,//"Walk",
		//	anime->Damage,//"Damage"
		//	anime->Attack1,//"Attack01",
		//	anime->End,
		//};
		////�A�j���[�V�����̓o�^
		//for (int i = 0; anime->End != AnimeIndex[i]; i++)
		//{
		//	anime->Register(i, AnimeIndex[i]);
		//}
}

//behaviorTree�̐ݒ�
void EnemyBoom::SetBehaviorTree()
{
	//
//behaviorTree = make_unique<BehaviorTree>();
//behaviordata = make_unique<BehaviorData>();
//behaviorTree->AddNode("", "root", 1, BehaviorTree::SelectRule::PRIORITY, nullptr, nullptr);
}

