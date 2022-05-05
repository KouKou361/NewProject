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
	//�X�e�[�^�X�ݒ�
	SetStatus("Site");
	//���f������
	SetModel(-1);//-1�͕`�悵�Ȃ�

	//�A�j���V�����ݒ�
	SetAnimetion();

	//�^�O�t��
	SetEnemyTag(EnemyTag::BOSS_SITE);
	SetTag(ObjectTag::TAG_ENEMY);

	//�V���{�B�̍U�����󂯂郊�X�g���N���A�i�O�̂��߁j
	attackSirobo.clear();

	//behaviorTree�̐ݒ�
	SetBehaviorTree();

	
}


//�X�V����
void EnemySite::Update()
{
	//���S�t���O��_���[�W�t���O�����Ă��Ȃ����m�F
	FlgCheak();

	SetMoveVec({ 0,0,0 });
	
	//�r�w�C�r�A�c���[�̍s������
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
	////�n�ʂ̕␳
	//VerticalCollision();
	////�G�̉�]
	//Turn(moveVec);
	////�G�̈ړ�
	//Move();
	////�ߋ��̒n�_�̕ۑ�
	//SetOldPos(GetPos());
	////�s��Ȃǂ̍X�V����
	//Charactor::Update();
}


//�_���[�W�𔻒�
bool EnemySite::AddDamage(int Damage, float SetinvincibleTime)
{
	//�̗͂�0�ȉ��Ȃ�
	if (GetHp() <= 0)return false;

	hp -= Damage;
	//���������c���Ă����Ȃ�
	if (hp >= 1)
	{
		//�ߋ��Ƀ_���[�W���󂯂��B
		oldDamageFlg = true;
		
		//�_���[�W�t���O�̃I��
		SetDamageFlg(true);
	}
	else//���S���Ă���Ȃ�
	{
		TargetFaild();
		//targetFlg = TargetFlg::Failed;
		//�_���[�W�t���O�̃I��
		SetDeadFlg(true);
		GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("Fire")->Play(GetPos(), 10);
	}
	return true;
}

//�A�j���V�����ݒ�
void EnemySite::SetAnimetion()
{
	anime = make_unique<Animetion>();
	//�A�j���[�V�����ԍ�
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
	//�A�j���[�V�����̓o�^
	anime->AllAnimetionKey(&AnimeIndex[0]);
}

//behaviorTree�̐ݒ�
void EnemySite::SetBehaviorTree()
{
	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("",     "root", 1, BehaviorTree::SelectRule::PRIORITY, nullptr,                 nullptr);
	behaviorTree->AddNode("root", "Die" , 0, BehaviorTree::SelectRule::NONE,     new DeadJudgement(this), new BossSiteDieAction(this));
}




