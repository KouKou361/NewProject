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

//初期化処理
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
//更新処理
void EnemyBase::Update()
{

	//死亡フラグやダメージフラグが来ていないか確認
	FlgCheak();

	SetMoveVec({ 0,0,0 });

	//ビヘイビアツリーの行動処理
	ActionBehaviorTree();
	//地面の補正
	//VerticalCollision();
	//敵の回転
	Turn(moveVec);
	//敵の移動
	Move();
	//過去の地点の保存
	SetOldPos(GetPos());
	//行列などの更新処理
	Charactor::Update();
}
//死亡フラグやダメージフラグが来ていないか確認
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


//当たり判定
void EnemyBase::AttackCircleNode(string nodeName, float circleL, float startTime, float EndTime)
{


	float endAnimetionTime = TK_Lib::Model::GetEndAnimetionTime(GetModel());
	float AnimetionTime= TK_Lib::Model::GetAnimetionTime(GetModel());

	if (endAnimetionTime == 0)assert(L"0で割り算しようとしました");
	//アニメーションタイムの0～1までの比率に直す
	AnimetionTime /= endAnimetionTime;

	if (AnimetionTime <= startTime)return;
	if (AnimetionTime >= EndTime)return;


	ModelResource::NodeTest* node = nullptr;
	node = TK_Lib::Model::FindNode(GetModel(), nodeName.c_str());
	if (node == nullptr)assert(!L"nodeがnullptrです");


	VECTOR3 Pos;
	Pos.x = node->worldTransform._41;
	Pos.y = node->worldTransform._42;
	Pos.z = node->worldTransform._43;

	AttackCircle(Pos, circleL);
}


void EnemyBase::AttackCircle(VECTOR3 pos, float circleL)
{
	//もし攻撃が目標に当たった場合
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

//経路探索
void EnemyBase::RouteSearch(VECTOR3& OutPos)
{
	Collision::Instance().SearchRoat(GetPos(), OutPos);
}

//ImGuiのデバッグ
void EnemyBase::ImguiDebug()
{
	if (ActionNode != nullptr)
	{
		ActionNode->ImguiDebug();
	}
}

bool EnemyBase::VsTargetAttackCircle(VECTOR3 Pos, float Radius)
{
	//目標までの距離を算出
	float TargetL;
	{
		VECTOR3 vec = GetTarget()->GetPos() - Pos;
		XMVECTOR Vec = XMLoadFloat3(&vec);
		Vec = XMVector3Length(Vec);
		XMStoreFloat(&TargetL, Vec);
	}
	//目標までの距離と比べる
	return TargetL <= Radius;
}


//索敵範囲にTargetがいればTRUEを返す
bool EnemyBase::SearchTarget(float L)
{
	Actor* Target = GetTarget();
	//もし目標がいなかったらエラー
	if (Target == nullptr)
	{
		assert(!L"No Target!");
		return false;
	}
	//索敵範囲にいるかどうかを判断
	return SearchPosition(L,Target->GetPos());

}
//ビヘイビアツリーの行動処理
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
	//子オブジェクトも削除
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
		//死亡時間が経ったら
		if (DeathTime <= 0)
		{
			return true;
		}
	}
	return false;
}
//自分が視野角内に入っているかどうか
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
	////黒
	//TK_Lib::Draw::Sprite(SpriteIndex, { Pos.x,Pos.y }, VECTOR2{ HpSize       ,10 }, VECTOR4{ 0,(60 / 4) * 3,942 / 3,60 / 4 });
	////ゲージ
	//TK_Lib::Draw::Sprite(SpriteIndex, { Pos.x,Pos.y }, VECTOR2{ TargetHpRatio,10 }, VECTOR4{ 0,0,942 / 3,60 / 4 });
}

bool EnemyBase::AddDamage(int Damage, int MaxinvincibleTime)
{
	//体力が0以下なら
	if (GetHp() <= 0)return false;

	hp -= Damage;
	//もし生き残っていたなら
	if (hp >= 1)
	{
		//過去にダメージを受けた。
		oldDamageFlg = true;
		//ダメージフラグのオン
		SetDamageFlg(true);
	}
	else//死亡しているなら
	{
		//ダメージフラグのオン
		SetDeadFlg(true);
	}
	return true;
}
//攻撃目標にできようになる
void EnemyBase::TargetComplete()
{
	targetFlg= TargetFlg::Complete;
}
//攻撃目標にできないようになる
void EnemyBase::TargetFaild()
{
	targetFlg = TargetFlg::Failed;

	//ミニオンの帰還
	for (int i = 0; i < AttackMinions.size(); i++)
	{
		MinionPlayer* minion = AttackMinions.at(i);
		minion->ResetNode();
	}

	//子オブジェクトも攻撃目標から消す。
	for (int i = 0; i < children.size(); i++)
	{
		EnemyBase* enm = children.at(i);
		enm->TargetFaild();
	}
}