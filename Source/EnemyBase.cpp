#include "EnemyBase.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "ActionDerived.h"
#include "JudgementDerived.h"
#include "NodeBase.h"
#include "Animetion.h"
#include "UIDerived.h"
#include "MinionPlayer.h"
#include "Scene.h"

//����������
void EnemyBase::Init()
{
	SetQuaternion({ 0,0,0,1 });
	SetPos({ 7,0,0 });
	SetScale({ 0.025f,0.025f,0.025f });
	speed = 0.4f;
	collisionRadius = 1.0f;
	SetModel(TK_Lib::Load::GetModel("Slime"));

	anime = make_unique<Animetion>();

	SetTag(ObjectTag::TAG_ENEMY);
	
	behaviorTree = make_unique<BehaviorTree>();
	behaviordata = make_unique<BehaviorData>();
	behaviorTree->AddNode("","root",1, BehaviorTree::SelectRule::PRIORITY,nullptr,nullptr);
	behaviorTree->AddNode("root", "idle", 1, BehaviorTree::SelectRule::NONE,new IdleJudgement(this), new IdleAction(this));
	behaviorTree->AddNode("root", "attack", 1, BehaviorTree::SelectRule::NONE, new AttackJudgement(this), new AttackAction(this));
	behaviorTree->AddNode("root", "pursuit", 1, BehaviorTree::SelectRule::NONE, new PursuitJudgement(this), new PursuitAction(this));
}
//�X�V����
void EnemyBase::Update()
{

	//���S�t���O��_���[�W�t���O�����Ă��Ȃ����m�F
	FlgCheak();

	SetMoveVec({ 0,0,0 });

	//�r�w�C�r�A�c���[�̍s������
	ActionBehaviorTree();
	//�n�ʂ̕␳
	//VerticalCollision();
	//�G�̉�]
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
		ResetNode();
	}
	if (GetDeadFlg() == true)
	{
		ResetNode();
	}

}


//�����蔻��
void EnemyBase::AttackCircleNode(string nodeName, float circleL, float startTime, float EndTime)
{


	float endAnimetionTime = TK_Lib::Model::GetEndAnimetionTime(GetModel());
	float AnimetionTime= TK_Lib::Model::GetAnimetionTime(GetModel());

	if (endAnimetionTime == 0)assert(L"0�Ŋ���Z���悤�Ƃ��܂���");
	//�A�j���[�V�����^�C����0�`1�܂ł̔䗦�ɒ���
	AnimetionTime /= endAnimetionTime;

	if (AnimetionTime <= startTime)return;
	if (AnimetionTime >= EndTime)return;


	ModelResource::NodeTest* node = nullptr;
	node = TK_Lib::Model::FindNode(GetModel(), nodeName.c_str());
	if (node == nullptr)assert(!L"node��nullptr�ł�");


	VECTOR3 Pos;
	Pos.x = node->worldTransform._41;
	Pos.y = node->worldTransform._42;
	Pos.z = node->worldTransform._43;

	AttackCircle(Pos, circleL);
}


void EnemyBase::AttackCircle(VECTOR3 pos, float circleL)
{
	//�����U�����ڕW�ɓ��������ꍇ
	if (VsTargetAttackCircle(pos, circleL))
	{
		GetTarget()->AddDamage(1, GetTarget()->GetMaxinvincibleTime());
	}
	TK_Lib::Debug3D::Circle(pos, circleL, VECTOR4{ 0,1,0,1 });
}

void EnemyBase::ResetNode()
{
	ActionNode = nullptr;
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
	if (ActionNode != nullptr)
	{
		ActionNode->ImguiDebug();
	}
}

bool EnemyBase::VsTargetAttackCircle(VECTOR3 Pos, float Radius)
{
	//�ڕW�܂ł̋������Z�o
	float TargetL;
	{
		VECTOR3 vec = GetTarget()->GetPos() - Pos;
		XMVECTOR Vec = XMLoadFloat3(&vec);
		Vec = XMVector3Length(Vec);
		XMStoreFloat(&TargetL, Vec);
	}
	//�ڕW�܂ł̋����Ɣ�ׂ�
	return TargetL <= Radius;
}


//���G�͈͂�Target�������TRUE��Ԃ�
bool EnemyBase::SearchTarget(float L)
{
	Actor* Target = GetTarget();
	//�����ڕW�����Ȃ�������G���[
	if (Target == nullptr)
	{
		assert(!L"No Target!");
		return false;
	}
	//���G�͈͂ɂ��邩�ǂ����𔻒f
	return SearchPosition(L,Target->GetPos());

}
//�r�w�C�r�A�c���[�̍s������
void EnemyBase::ActionBehaviorTree()
{

	if (actionFlg == false)return;

	if (ActionNode == nullptr)
	{

		ActionNode = behaviorTree->ActiveNodeInference(this, behaviordata.get());
		//if(ActionNode)ActionNode->ImguiDebug();
	}
	if (ActionNode != nullptr)
	{
		ActionNode = behaviorTree->Run(this, ActionNode, behaviordata.get());
	}


}
void EnemyBase::SetDamageFlg(bool flg) { 
	damageFlg = flg;
}
void EnemyBase::SetDeadFlg(bool flg) { deadFlg = flg; };
void  EnemyBase::Destroy()
{
	//�q�I�u�W�F�N�g���폜
	for (int i = 0; i < children.size(); i++)
	{
		GetSceneGame()->GetEnemyManager()->Destroy(children.at(i));
	}

     GetSceneGame()->GetEnemyManager()->Destroy(this);
}
bool EnemyBase::UpdateDeathTime()
{
	float DeltaTimer = TK_Lib::Window::GetElapsedTime();
	if (DeathTime > 0)
	{
		DeathTime -= DeltaTimer;
		//���S���Ԃ��o������
		if (DeathTime <= 0)
		{
			return true;
		}
	}
	return false;
}
//����������p���ɓ����Ă��邩�ǂ���
bool EnemyBase::IsDotAngle(const VECTOR3 Pos, const VECTOR3 vec, const float Angle)
{
	VECTOR3 v =  GetPos()-Pos;
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
	if (Angle >= dot)
	{
		return true;
	}
	return false;
	
	
}

void EnemyBase::HPRender(const int SpriteIndex, const VECTOR2 Pos)
{
	//const float HpSize = 70;
	//const  float TargetHpRatio = (static_cast<float>(GetHp()) / static_cast<float>(GetMaxHp())) * HpSize;
	////��
	//TK_Lib::Draw::Sprite(SpriteIndex, { Pos.x,Pos.y }, VECTOR2{ HpSize       ,10 }, VECTOR4{ 0,(60 / 4) * 3,942 / 3,60 / 4 });
	////�Q�[�W
	//TK_Lib::Draw::Sprite(SpriteIndex, { Pos.x,Pos.y }, VECTOR2{ TargetHpRatio,10 }, VECTOR4{ 0,0,942 / 3,60 / 4 });
}

bool EnemyBase::AddDamage(int Damage, int MaxinvincibleTime)
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
		//�_���[�W�t���O�̃I��
		SetDeadFlg(true);
	}
	return true;
}
//�U���ڕW�ɂł��悤�ɂȂ�
void EnemyBase::TargetComplete()
{
	targetFlg= TargetFlg::Complete;
}
//�U���ڕW�ɂł��Ȃ��悤�ɂȂ�
void EnemyBase::TargetFaild()
{
	targetFlg = TargetFlg::Failed;

	//�~�j�I���̋A��
	for (int i = 0; i < AttackMinions.size(); i++)
	{
		MinionPlayer* minion = AttackMinions.at(i);
		minion->ResetNode();
	}

	//�q�I�u�W�F�N�g���U���ڕW��������B
	for (int i = 0; i < children.size(); i++)
	{
		EnemyBase* enm = children.at(i);
		enm->TargetFaild();
	}
}