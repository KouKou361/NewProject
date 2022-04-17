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
	//アニメーション番号
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
	//アニメーションの登録
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
	//初期の状態は行動しない
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
	//移動後待機
	behaviorTree->AddNode("Battle", "Walk_Idei", 0, BehaviorTree::SelectRule::SEQUENCE, nullptr, nullptr);
	behaviorTree->AddNode("Walk_Idei",   "Walk", 1, BehaviorTree::SelectRule::NONE     , nullptr, new BossWalkAction(this));
	behaviorTree->AddNode("Walk_Idei",   "Idei", 2, BehaviorTree::SelectRule::NONE     , nullptr, new BossIdeiAction(this));


	//=======================================
	//移動後攻撃
	behaviorTree->AddNode("Battle",      "Walk_Attack",     0, BehaviorTree::SelectRule::SEQUENCE, nullptr, nullptr);
	behaviorTree->AddNode("Walk_Attack", "Walk",            1, BehaviorTree::SelectRule::NONE, nullptr, new BossWalkAction(this));
	behaviorTree->AddNode("Walk_Attack", "Attack",          3, BehaviorTree::SelectRule::SEQUENCE, new BossRollAttackJudgement(this), nullptr);
    behaviorTree->AddNode("Attack",      "AttackRollStart", 1, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackStartAction(this));
    behaviorTree->AddNode("Attack",      "AttackRoll",      2, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackAction(this));
    behaviorTree->AddNode("Attack",      "AttackRollEnd",   3, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackEndAction(this));
	
	
	//=======================================
	//回転攻撃後待機
	behaviorTree->AddNode("Battle", "Attack", 3, BehaviorTree::SelectRule::SEQUENCE, new BossRollAttackJudgement(this), nullptr);
	behaviorTree->AddNode("Attack", "AttackRollStart", 1, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackStartAction(this));
	behaviorTree->AddNode("Attack", "AttackRoll",      2, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackAction(this));
	behaviorTree->AddNode("Attack", "AttackRollEnd",   3, BehaviorTree::SelectRule::NONE, nullptr, new BossRollAttackEndAction(this));
	behaviorTree->AddNode("Attack", "Idei",            2, BehaviorTree::SelectRule::NONE, nullptr, new BossIdeiAction(this));
}


void EnemyBoss::TargetComplete()
{
	targetFlg = TargetFlg::Failed;

	//子オブジェクトも攻撃目標から消す。
	for (int i = 0; i < children.size(); i++)
	{
		EnemyBase* enm = children.at(i);
		if (enm->GetHp() <= 0)
		{
			//攻撃目標出来ない
			enm->TargetFaild();
		}
		else
		{
			//攻撃目標出来る
			enm->TargetComplete();
		}
	}
}


//更新処理
void EnemyBoss::Update()
{


	CheakChildrenDie();

	SetMoveVec({ 0,0,0 });
	//ビヘイビアツリーの行動処理
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
		if (node == nullptr)assert(!L"nodeがnullptrです");
	

		VECTOR3 Pos;
		Pos.x = node->worldTransform._41;
		Pos.y = node->worldTransform._42;
		Pos.z = node->worldTransform._43;
		children.at(i)->SetPos(Pos);

	}
	//地面の補正
	VerticalCollision();
	//敵の移動
	Move();
	//過去の地点の保存
	SetOldPos(GetPos());
	//行列などの更新処理
	Charactor::Update();
}

//もし子オブジェクトが死亡しているなら
void EnemyBoss::CheakChildrenDie()
{

	if (GetDeadFlg())return;


	for (int i = 0; i < children.size(); i++)
	{
		EnemyBase* enm=children.at(i);
		//もし生きているなら
		if (enm->GetDeadFlg()==false)
		{
			return;
		}
		
	}

	//全ての子オブジェクトが死亡しているなら
	SetDeadFlg(true);
	//死亡フラグやダメージフラグが来ていないか確認
	FlgCheak();
}

//描画処理
void EnemyBoss::ModelRender()
{
	if (GetModel() >= 0)
	{
		//カメラより外にいるなら
		if (TK_Lib::Camera::IsCamera(GetPos(),35.0f))
		{
			TK_Lib::Draw::Model(GetModel(), ShaderType::Shader_MakeShadow);
		}

	}
}

