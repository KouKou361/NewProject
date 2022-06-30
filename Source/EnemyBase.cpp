#include "EnemyBase.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"
#include "UIDerived.h"
#include "SiroboPlayer.h"
#include "Scene.h"
#include "ExportScript.h"

////����������
//void EnemyBase::Init()
//{
//	SetQuaternion({ 0,0,0,1 });
//	SetPos({ 7,0,0 });
//	SetScale({ 0.025f,0.025f,0.025f });
//	speed = 0.4f;
//	collisionRadius = 1.0f;
//	SetModel(TK_Lib::Load::GetModel("Slime"));
//
//	anime = make_unique<Animetion>();
//
//	SetTag(ObjectTag::TAG_ENEMY);
//	
//	behaviorTree = make_unique<BehaviorTree>();
//	behaviordata = make_unique<BehaviorData>();
//	behaviorTree->AddNode("","root",1, BehaviorTree::SelectRule::PRIORITY,nullptr,nullptr);
//	behaviorTree->AddNode("root", "idle", 1, BehaviorTree::SelectRule::NONE,new IdleJudgement(this), new IdleAction(this));
//	behaviorTree->AddNode("root", "attack", 1, BehaviorTree::SelectRule::NONE, new AttackJudgement(this), new AttackAction(this));
//	behaviorTree->AddNode("root", "pursuit", 1, BehaviorTree::SelectRule::NONE, new PursuitJudgement(this), new PursuitAction(this));
//}

//CSV����f�[�^�����o���āA�X�e�[�^�X�̐ݒ肷��B
void EnemyBase::SetStatus(const string& searchName)
{
	//�f�[�^�̎擾
	EnemyStatusData* data = sceneGame->GetexportSCV()->GetEnemyStatusDataSearchName(searchName);

	//�X�e�[�^�X�̐ݒ�
	SetQuaternion({ 0,0,0,1 });
	SetScale({ data->GetScale(),data->GetScale(),data->GetScale() });
	SetHp(data->GetHp());
	SetMaxHp(GetHp());
	SetMaxBeAttacked(data->GetSiroboMaxBeAttacked());	//�~�j�I�����U�����Ă���ő吔
	attackNode = data->GetAttackNode();
	speed = data->GetSpeed();
	collisionRadius = data->GetCollisionRadius();
}
//�X�V����
void EnemyBase::Update()
{

	//���S�t���O��_���[�W�t���O�����Ă��Ȃ����m�F
	FlgCheak();
	//�i�ޕ����̏�����
	SetMoveVec({ 0,0,0 });

	//�r�w�C�r�A�c���[�̍s������
	ActionBehaviorTree();
	//�n�ʂ̕␳
	//VerticalCollision();
	
	//�G�̐i�ޕ����ɉ�]
	Turn(moveVec);
	//�G�̈ړ�
	Move();
	//�ߋ��̒n�_�̕ۑ�
	SetOldPos(GetPos());
	//�s��Ȃǂ̍X�V����
	Charactor::Update();
}
//���S�t���O��_���[�W�t���O�����Ă��Ȃ����m�F
void EnemyBase::FlgCheak()
{
	if (GetDamageFlg() == true)
	{
		//�s�������Z�b�g
		ResetNode();
	}
	if (GetDeadFlg() == true)
	{
		//�s�������Z�b�g
		ResetNode();
	}

}


//�G�̃{�[�����擾���čU���i�����蔻��j
void EnemyBase::AttackCircleNode(const string& nodeName, const float& circleL, const float& startTime,const float& endTime)
{
	
	//�A�j���[�V���������ǂ������m���߂�B�i�����A�j���[�V�����O�Ȃ�return�j
	{
		const float endAnimetionTime = TK_Lib::Model::GetEndAnimetionTime(GetModel());
		float AnimetionTime = TK_Lib::Model::GetAnimetionTime(GetModel());

		if (endAnimetionTime == 0)assert(L"0�Ŋ���Z���悤�Ƃ��܂���");
		//�A�j���[�V�����^�C����0�`1�܂ł̔䗦�ɒ���
		AnimetionTime /= endAnimetionTime;

		if (AnimetionTime <= startTime)return;
		if (AnimetionTime >= endTime)return;
	}



	//�{�[���̃m�[�h�擾
	ModelResource::NodeTest* node = nullptr;
	node = TK_Lib::Model::FindNode(GetModel(), nodeName.c_str());
	if (node == nullptr)assert(!L"node��nullptr�ł�");

	VECTOR3 Pos;
	Pos.x = node->worldTransform._41;
	Pos.y = node->worldTransform._42;
	Pos.z = node->worldTransform._43;

	//�U������
	AttackCircle(Pos, circleL);
}

//�U���ڕW�ɑ΂��čU���I
void EnemyBase::AttackCircle(const VECTOR3 &pos, const float& circleL)
{
	//�U���́i�܂����̃Q�[���ɍU���͂Ȃ�đ��݂��Ȃ����A�Ƃ肠�����p�ӂ��Ă����B�j
	const int AttackVolume = 1;

	//�����U�����ڕW�ɓ��������ꍇ
	if (VsTargetAttackCircle(pos, circleL))
	{
		GetTarget()->AddDamage(AttackVolume, GetTarget()->GetMaxinvincibleTime());
	}
	//TK_Lib::Debug3D::Circle(pos, circleL, VECTOR4{ 0,1,0,1 });
}

//�ʂ̍s���ֈڍs������B
void EnemyBase::ResetNode()
{
	actionNode = nullptr;
	//behaviordata->Init();
}

//�o�H�T��
void EnemyBase::RouteSearch(VECTOR3& OutPos)
{
	Collision::Instance().SearchRoat(GetPos(), OutPos);
}

//ImGui�̃f�o�b�O
void EnemyBase::ImguiDebug()
{
	if (actionNode != nullptr)
	{
		actionNode->ImguiDebug();
	}
}

bool EnemyBase::VsTargetAttackCircle(const VECTOR3& pos, const float& radius)
{
	//�ڕW�܂ł̋������Z�o
	float TargetL;
	{
		VECTOR3 vec = GetTarget()->GetPos() - pos;
		XMVECTOR Vec = XMLoadFloat3(&vec);
		Vec = XMVector3Length(Vec);
		XMStoreFloat(&TargetL, Vec);
	}
	//�ڕW�܂ł̋����Ɣ�ׂ�
	return TargetL <= radius;
}


//���G�͈͂�Target�������TRUE��Ԃ�
bool EnemyBase::SearchTarget(const float &l)
{
	Actor* Target = GetTarget();
	//�����ڕW�����Ȃ�������G���[
	if (Target == nullptr)
	{
		assert(!L"No Target!");
		return false;
	}
	//���G�͈͂ɂ��邩�ǂ����𔻒f
	return SearchPosition(l,Target->GetPos());

}
//�r�w�C�r�A�c���[�̍s������
void EnemyBase::ActionBehaviorTree()
{

	if (actionFlg == false)return;

	//�����s�����܂��Ă��Ȃ��Ȃ�V�����v�l����B
	if (actionNode == nullptr)
	{

		actionNode = behaviorTree->ActiveNodeInference(this, behaviordata.get());
		//if(ActionNode)ActionNode->ImguiDebug();
	}
	//�s�����J�n
	if (actionNode != nullptr)
	{
		actionNode = behaviorTree->Run(this, actionNode, behaviordata.get());
	}


}

//���ŏ���
void  EnemyBase::Destroy()
{
	//�q�I�u�W�F�N�g���폜
	for (int i = 0; i < children.size(); i++)
	{
		GetSceneGame()->GetEnemyManager()->Destroy(children.at(i));
	}

     GetSceneGame()->GetEnemyManager()->Destroy(this);
}
//���S���鎞�Ԃ̍X�V����
bool EnemyBase::UpdateDeathTime()
{
	const float DeltaTimer = TK_Lib::Window::GetElapsedTime();
	//���S���Ԃ��o������
	if (deathTime <= 0)
	{
		return true;
	}

	deathTime -= DeltaTimer;	
	return false;
}
//����������p���ɓ����Ă��邩�ǂ���
bool EnemyBase::IsDotAngle(const VECTOR3& pos, const VECTOR3& vec, const float& angle)
{
	VECTOR3 v =  GetPos()-pos;
	XMVECTOR Vec1 = XMLoadFloat3(&v);
	XMVECTOR NVec1 = XMVector3Normalize(Vec1);
	XMStoreFloat3(&v,NVec1);

	XMVECTOR Vec2 = XMLoadFloat3(&vec);
	XMVECTOR NVec2 = XMVector3Normalize(Vec2);
	XMStoreFloat3(&v, NVec2);

	XMVECTOR Dot=XMVector3Dot(NVec1, NVec2);
	float dot;
	XMStoreFloat(&dot, Dot);
	dot = acosf(dot);
	dot=XMConvertToDegrees(dot);
	//ImGui::Begin("aaa");
	//ImGui::Text("angle=%f", dot);
	//ImGui::Text("flg=%d", Angle >= dot);
	//ImGui::End();
	if (angle >= dot)
	{
		return true;
	}
	return false;
	
	
}

void EnemyBase::HPRender(const int& spriteIndex, const VECTOR2& pos)
{
	//const float HpSize = 70;
	//const  float TargetHpRatio = (static_cast<float>(GetHp()) / static_cast<float>(GetMaxHp())) * HpSize;
	////��
	//TK_Lib::Draw::Sprite(SpriteIndex, { Pos.x,Pos.y }, VECTOR2{ HpSize       ,10 }, VECTOR4{ 0,(60 / 4) * 3,942 / 3,60 / 4 });
	////�Q�[�W
	//TK_Lib::Draw::Sprite(SpriteIndex, { Pos.x,Pos.y }, VECTOR2{ TargetHpRatio,10 }, VECTOR4{ 0,0,942 / 3,60 / 4 });
}

bool EnemyBase::AddDamage(const int &damage,const float& maxInvincibleTime)
{
	//�̗͂�0�ȉ��Ȃ�
	if (GetHp() <= 0)return false;

	hp -= damage;
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
		//�_���[�W�t���O�̃I��
		SetDeadFlg(true);
	}
	return true;
}
//�U���ڕW�ɂł��悤�ɂȂ�
void EnemyBase::TargetComplete()
{
	targetFlg= TargetFlg::COMPLETE;
}
//�U���ڕW�ɂł��Ȃ��悤�ɂȂ�
void EnemyBase::TargetFaild()
{
	targetFlg = TargetFlg::FAILED;

	//�~�j�I���̋A��
	for (int i = 0; i < attackSirobo.size(); i++)
	{
		Sirobo* sirobo = attackSirobo.at(i);
		sirobo->ResetNode();
	}

	//�q�I�u�W�F�N�g���U���ڕW��������B
	for (int i = 0; i < children.size(); i++)
	{
		EnemyBase* enm = children.at(i);
		enm->TargetFaild();
	}
}