#include "EnemyBase.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"
#include "Scene.h"



void EnemyBoss::Init()
{
	SetQuaternion({ 0,0,0,1 });
	SetPos({ 0,0,-40 });
	SetScale({ 0.05f,0.05f,0.05f });
	speed = 0.4f;
	collisionRadius = 1.0f;
	SetModel(TK_Lib::Load::GetModel("Boss"));
	

	anime = make_unique<Animetion>();
	//�A�j���[�V�����ԍ�
	string AnimeIndex[] =
	{
		anime->BossOpen,
		anime->BossOpenGoToRoll,
		anime->Idle,
		anime->BossCloseStopRoll,
		anime->BossWalk,
		anime->BossClose_RollLoop,
		anime->BossClose,
		anime->End,
	};
	//�A�j���[�V�����̓o�^
	for (int i = 0; anime->End != AnimeIndex[i]; i++)
	{
		anime->Register(i, AnimeIndex[i]);
	}

	const char* SiteName[] =
	{
		"left_plate",
		"rear_plate",
		"right_plate",
	};
	for (auto name : SiteName)
	{
		std::shared_ptr<EnemySite> enm;
		enm = make_shared<EnemySite>(GetSceneGame());
		GetSceneGame()->GetEnemyManager()->Register(enm);
		enm->parent = this;
		this->children.push_back(enm.get());
	}
	//�����̏�Ԃ͍s�����Ȃ�
	actionFlg = false;
	TargetComplete();
	//targetFlg = TargetFlg::Failed;

	AttackMinions.clear();

	SetTag(ObjectTag::TAG_ENEMY);
	SetEnemyTag(EnemyTag::Boss);

	//TK_Lib::Model::PlayAnimation(GetModel(),0,true);


	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("", "root", 1, BehaviorTree::SelectRule::ON_OFF, nullptr, nullptr);

	behaviorTree->AddNode("root",   "Battle",          1, BehaviorTree::SelectRule::RANDOM,   nullptr, nullptr,            true);

	behaviorTree->AddNode("root",  "Entry",           2, BehaviorTree::SelectRule::SEQUENCE, nullptr, nullptr,            false);
	behaviorTree->AddNode("Entry", "EntryActoin",     0, BehaviorTree::SelectRule::NONE,      nullptr, new BossEntry(this),false);
	behaviorTree->AddNode("Entry", "AttackRollStart", 1, BehaviorTree::SelectRule::NONE,      nullptr, new BossRollAttackStartAction(this));
	behaviorTree->AddNode("Entry", "AttackRoll",      2, BehaviorTree::SelectRule::NONE,      nullptr, new BossRollAttackAction(this));
	behaviorTree->AddNode("Entry", "AttackRollEnd",   3, BehaviorTree::SelectRule::NONE,      nullptr, new BossRollAttackEndAction(this));

	behaviorTree->AddNode("root",   "Die",             3, BehaviorTree::SelectRule::NONE,    new DeadJudgement(this), new BossDeadAction(this),false);


	//=======================================
	//�ړ���ҋ@
	behaviorTree->AddNode("Battle", "Walk_Idei", 0, BehaviorTree::SelectRule::SEQUENCE, nullptr, nullptr);
	behaviorTree->AddNode("Walk_Idei",   "Walk", 1, BehaviorTree::SelectRule::NONE     , nullptr, new BossWalkAction(this));
	behaviorTree->AddNode("Walk_Idei",   "Idei", 2, BehaviorTree::SelectRule::NONE     , nullptr, new BossIdeiAction(this));


	//=======================================
	//�ړ���U��
	behaviorTree->AddNode("Battle",      "Walk_Attack",     0, BehaviorTree::SelectRule::SEQUENCE, nullptr, nullptr);
	behaviorTree->AddNode("Walk_Attack", "Walk",            1, BehaviorTree::SelectRule::NONE, nullptr, new BossWalkAction(this));
	behaviorTree->AddNode("Walk_Attack", "Attack",          3, BehaviorTree::SelectRule::SEQUENCE, new BossRollAttackJudgement(this), nullptr);
    behaviorTree->AddNode("Attack",      "AttackRollStart", 1, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackStartAction(this));
    behaviorTree->AddNode("Attack",      "AttackRoll",      2, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackAction(this));
    behaviorTree->AddNode("Attack",      "AttackRollEnd",   3, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackEndAction(this));
	
	
	//=======================================
	//��]�U����ҋ@
	behaviorTree->AddNode("Battle", "Attack", 3, BehaviorTree::SelectRule::SEQUENCE, new BossRollAttackJudgement(this), nullptr);
	behaviorTree->AddNode("Attack", "AttackRollStart", 1, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackStartAction(this));
	behaviorTree->AddNode("Attack", "AttackRoll",      2, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackAction(this));
	behaviorTree->AddNode("Attack", "AttackRollEnd",   3, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackEndAction(this));
	behaviorTree->AddNode("Attack", "Idei",            2, BehaviorTree::SelectRule::NONE, nullptr, new BossIdeiAction(this));
}


void EnemyBoss::TargetComplete()
{
	targetFlg = TargetFlg::Failed;

	//�q�I�u�W�F�N�g���U���ڕW��������B
	for (int i = 0; i < children.size(); i++)
	{
		EnemyBase* enm = children.at(i);
		if (enm->GetHp() <= 0)
		{
			//�U���ڕW�o���Ȃ�
			enm->TargetFaild();
		}
		else
		{
			//�U���ڕW�o����
			enm->TargetComplete();
		}
	}
}


//�X�V����
void EnemyBoss::Update()
{


	CheakChildrenDie();

	SetMoveVec({ 0,0,0 });
	//�r�w�C�r�A�c���[�̍s������
	ActionBehaviorTree();

	const char* SiteName[] =
	{
		"left_plate",
		"rear_plate",
		"right_plate",
	};

	for (int i=0;i<3;i++)
	{

		ModelResource::NodeTest* node = nullptr;
		node = TK_Lib::Model::FindNode(GetModel(), SiteName[i]);
		if (node == nullptr)assert(!L"node��nullptr�ł�");
	

		VECTOR3 Pos;
		Pos.x = node->worldTransform._41;
		Pos.y = node->worldTransform._42;
		Pos.z = node->worldTransform._43;
		children.at(i)->SetPos(Pos);

	}
	//�n�ʂ̕␳
	VerticalCollision();
	//�G�̈ړ�
	Move();
	//�ߋ��̒n�_�̕ۑ�
	SetOldPos(GetPos());
	//�s��Ȃǂ̍X�V����
	Charactor::Update();
}

//�����q�I�u�W�F�N�g�����S���Ă���Ȃ�
void EnemyBoss::CheakChildrenDie()
{

	if (GetDeadFlg())return;


	for (int i = 0; i < children.size(); i++)
	{
		EnemyBase* enm=children.at(i);
		//���������Ă���Ȃ�
		if (enm->GetDeadFlg()==false)
		{
			return;
		}
		
	}

	//�S�Ă̎q�I�u�W�F�N�g�����S���Ă���Ȃ�
	SetDeadFlg(true);
	//���S�t���O��_���[�W�t���O�����Ă��Ȃ����m�F
	FlgCheak();
}

//�`�揈��
void EnemyBoss::ModelRender()
{
	if (GetModel() >= 0)
	{
		//�J�������O�ɂ���Ȃ�
		if (TK_Lib::Camera::IsCamera(GetPos(),35.0f))
		{
			TK_Lib::Draw::Model(GetModel(), ShaderType::Shader_MakeShadow);
		}

	}
}

