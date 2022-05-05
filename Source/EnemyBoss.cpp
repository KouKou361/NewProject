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

	//�X�e�[�^�X�ݒ�
	SetStatus("Boss");
	//���f������
	SetModel(TK_Lib::Load::GetModel("Boss"));
	//�ʒu�i���ʁj
	SetPos({ 0,0,-40 });
	//�A�j���V�����ݒ�
	SetAnimetion();

	//���ʂ̓o�^
	AddSite("left_plate");
	AddSite("rear_plate");
	AddSite("right_plate");

	//�����̏�Ԃ͍s�����Ȃ�
	actionFlg = false;

	//�U�����󂯂���
	TargetComplete();

	//�V���{�B�̍U�����󂯂郊�X�g���N���A�i�O�̂��߁j
	attackSirobo.clear();

	//�^�O�t��
	SetTag(ObjectTag::TAG_ENEMY);
	SetEnemyTag(EnemyTag::BOSS);

	//behaviorTree�̐ݒ�
	SetBehaviorTree();
}

//�~�j�I����������U�������A�܂��U���ڕW�ɂł���B
void EnemyBoss::TargetComplete()
{
	targetFlg = TargetFlg::FAILED;

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

	//�����q�I�u�W�F�N�g�����S���Ă���Ȃ�
	CheakChildrenDie();

	SetMoveVec({ 0,0,0 });

	//�r�w�C�r�A�c���[�̍s������
	ActionBehaviorTree();

	//���ʒB�̈ʒu�X�V����
	UpdateAllSiteSetPosition();

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
	//���Ɏ��S���Ă���Ȃ�
	if (GetDeadFlg())return;

	//�S�Ă̎q�I�u�W�F�N�g�����S���Ă��邩�m�F
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
		if (TK_Lib::Camera::IsCamera(GetPos()))
		{
			TK_Lib::Draw::Model(GetModel(), ShaderType::Shader_MakeShadow);
		}

	}
}


//�A�j���V�����ݒ�
void EnemyBoss::SetAnimetion()
{
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
	anime->AllAnimetionKey(&AnimeIndex[0]);
}

//�{�X��p���ʂ̒ǉ�
void EnemyBoss::AddSite(string setSiteName)
{
	std::shared_ptr<EnemySite> enm;
	enm = make_shared<EnemySite>(GetSceneGame());
	GetSceneGame()->GetEnemyManager()->Register(enm);
	enm->parent = this;
	enm->siteName= setSiteName;
	this->children.push_back(enm.get());
}

//�{�X��p���ʒB�̈ʒu�X�V����
void EnemyBoss::UpdateAllSiteSetPosition()
{
	for (int i = 0; i < children.size(); i++)
	{
		EnemyBase* enm = children.at(i);
		EnemySite* site = dynamic_cast<EnemySite*>(enm);
		if (site == nullptr)continue;

		ModelResource::NodeTest* node = nullptr;
		node = TK_Lib::Model::FindNode(GetModel(), site->siteName.c_str());
		if (node == nullptr)assert(!L"node��nullptr�ł�");

		
		VECTOR3 Pos;
		//�ʒu�̎Z�o
		{
			Pos.x = node->worldTransform._41;
			Pos.y = node->worldTransform._42;
			Pos.z = node->worldTransform._43;
		}
		//�ʒu�̍X�V����
		site->SetPos(Pos);

	}
}

//behaviorTree�̐ݒ�
void EnemyBoss::SetBehaviorTree()
{
	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();	         
	behaviorTree->AddNode("", "root",                  1,BehaviorTree::SelectRule::ON_OFF,   nullptr, nullptr);
												         								     
	behaviorTree->AddNode("root", "Battle",            1,BehaviorTree::SelectRule::RANDOM,   nullptr, nullptr, true);
												         
	//======================================	         
	//�o��s��									         
	behaviorTree->AddNode("root", "Entry",             2,BehaviorTree::SelectRule::SEQUENCE, nullptr, nullptr, false);
	behaviorTree->AddNode("Entry", "EntryActoin",      0,BehaviorTree::SelectRule::NONE,     nullptr, new BossEntry(this), false);
	behaviorTree->AddNode("Entry", "AttackRollStart",  1,BehaviorTree::SelectRule::NONE,     nullptr, new BossRollAttackStartAction(this));
	behaviorTree->AddNode("Entry", "AttackRoll",       2,BehaviorTree::SelectRule::NONE,     nullptr, new BossRollAttackAction(this));
	behaviorTree->AddNode("Entry", "AttackRollEnd",    3,BehaviorTree::SelectRule::NONE,     nullptr, new BossRollAttackEndAction(this));

	//���S
	behaviorTree->AddNode("root", "Die",               3,BehaviorTree::SelectRule::NONE,     new DeadJudgement(this), new BossDeadAction(this), false);

	//=======================================
	//�ړ���ҋ@
	behaviorTree->AddNode("Battle", "Walk_Idei",       0,BehaviorTree::SelectRule::SEQUENCE, nullptr, nullptr);
	behaviorTree->AddNode("Walk_Idei", "Walk",         1,BehaviorTree::SelectRule::NONE,     nullptr, new BossWalkAction(this));
	behaviorTree->AddNode("Walk_Idei", "Idei",         2,BehaviorTree::SelectRule::NONE,     nullptr, new BossIdeiAction(this));


	//=======================================
	//�ړ���U��
	behaviorTree->AddNode("Battle", "Walk_Attack", 0,    BehaviorTree::SelectRule::SEQUENCE, nullptr, nullptr);
	behaviorTree->AddNode("Walk_Attack", "Walk", 1,      BehaviorTree::SelectRule::NONE,     nullptr, new BossWalkAction(this));
	behaviorTree->AddNode("Walk_Attack", "Attack", 3,    BehaviorTree::SelectRule::SEQUENCE, new BossRollAttackJudgement(this), nullptr);
	behaviorTree->AddNode("Attack", "AttackRollStart", 1,BehaviorTree::SelectRule::NONE,     nullptr, new BossRollAttackStartAction(this));
	behaviorTree->AddNode("Attack", "AttackRoll", 2,     BehaviorTree::SelectRule::NONE,     nullptr, new BossRollAttackAction(this));
	behaviorTree->AddNode("Attack", "AttackRollEnd", 3,  BehaviorTree::SelectRule::NONE,     nullptr, new BossRollAttackEndAction(this));


	//=======================================
	//��]�U����ҋ@
	behaviorTree->AddNode("Battle", "Attack", 3,         BehaviorTree::SelectRule::SEQUENCE, new BossRollAttackJudgement(this), nullptr);
	behaviorTree->AddNode("Attack", "AttackRollStart", 1,BehaviorTree::SelectRule::NONE,     nullptr, new BossRollAttackStartAction(this));
	behaviorTree->AddNode("Attack", "AttackRoll", 2,     BehaviorTree::SelectRule::NONE,     nullptr, new BossRollAttackAction(this));
	behaviorTree->AddNode("Attack", "AttackRollEnd", 3,  BehaviorTree::SelectRule::NONE,     nullptr, new BossRollAttackEndAction(this));
	behaviorTree->AddNode("Attack", "Idei", 2,           BehaviorTree::SelectRule::NONE,     nullptr, new BossIdeiAction(this));
}

