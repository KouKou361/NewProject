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

////初期化処理
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

//CSVからデータを取り出して、ステータスの設定する。
void EnemyBase::SetStatus(const string& searchName)
{
	//データの取得
	EnemyStatusData* data = sceneGame->GetexportSCV()->GetEnemyStatusDataSearchName(searchName);

	//ステータスの設定
	SetQuaternion({ 0,0,0,1 });
	SetScale({ data->GetScale(),data->GetScale(),data->GetScale() });
	SetHp(data->GetHp());
	SetMaxHp(GetHp());
	SetMaxBeAttacked(data->GetSiroboMaxBeAttacked());	//ミニオンが攻撃してくる最大数
	attackNode = data->GetAttackNode();
	speed = data->GetSpeed();
	collisionRadius = data->GetCollisionRadius();
}
//更新処理
void EnemyBase::Update()
{

	//死亡フラグやダメージフラグが来ていないか確認
	FlgCheak();
	//進む方向の初期化
	SetMoveVec({ 0,0,0 });

	//ビヘイビアツリーの行動処理
	ActionBehaviorTree();
	//地面の補正
	//VerticalCollision();
	
	//敵の進む方向に回転
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
		//行動をリセット
		ResetNode();
	}
	if (GetDeadFlg() == true)
	{
		//行動をリセット
		ResetNode();
	}

}


//敵のボーンを取得して攻撃（当たり判定）
void EnemyBase::AttackCircleNode(const string& nodeName, const float& circleL, const float& startTime,const float& endTime)
{
	
	//アニメーション中かどうかを確かめる。（もしアニメーション外ならreturn）
	{
		const float endAnimetionTime = TK_Lib::Model::GetEndAnimetionTime(GetModel());
		float AnimetionTime = TK_Lib::Model::GetAnimetionTime(GetModel());

		if (endAnimetionTime == 0)assert(L"0で割り算しようとしました");
		//アニメーションタイムの0～1までの比率に直す
		AnimetionTime /= endAnimetionTime;

		if (AnimetionTime <= startTime)return;
		if (AnimetionTime >= endTime)return;
	}



	//ボーンのノード取得
	ModelResource::NodeTest* node = nullptr;
	node = TK_Lib::Model::FindNode(GetModel(), nodeName.c_str());
	if (node == nullptr)assert(!L"nodeがnullptrです");

	VECTOR3 Pos;
	Pos.x = node->worldTransform._41;
	Pos.y = node->worldTransform._42;
	Pos.z = node->worldTransform._43;

	//攻撃する
	AttackCircle(Pos, circleL);
}

//攻撃目標に対して攻撃！
void EnemyBase::AttackCircle(const VECTOR3 &pos, const float& circleL)
{
	//攻撃力（まあこのゲームに攻撃力なんて存在しないが、とりあえず用意しておく。）
	const int AttackVolume = 1;

	//もし攻撃が目標に当たった場合
	if (VsTargetAttackCircle(pos, circleL))
	{
		GetTarget()->AddDamage(AttackVolume, GetTarget()->GetMaxinvincibleTime());
	}
	//TK_Lib::Debug3D::Circle(pos, circleL, VECTOR4{ 0,1,0,1 });
}

//別の行動へ移行させる。
void EnemyBase::ResetNode()
{
	actionNode = nullptr;
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
	if (actionNode != nullptr)
	{
		actionNode->ImguiDebug();
	}
}

bool EnemyBase::VsTargetAttackCircle(const VECTOR3& pos, const float& radius)
{
	//目標までの距離を算出
	float TargetL;
	{
		VECTOR3 vec = GetTarget()->GetPos() - pos;
		XMVECTOR Vec = XMLoadFloat3(&vec);
		Vec = XMVector3Length(Vec);
		XMStoreFloat(&TargetL, Vec);
	}
	//目標までの距離と比べる
	return TargetL <= radius;
}


//索敵範囲にTargetがいればTRUEを返す
bool EnemyBase::SearchTarget(const float &l)
{
	Actor* Target = GetTarget();
	//もし目標がいなかったらエラー
	if (Target == nullptr)
	{
		assert(!L"No Target!");
		return false;
	}
	//索敵範囲にいるかどうかを判断
	return SearchPosition(l,Target->GetPos());

}
//ビヘイビアツリーの行動処理
void EnemyBase::ActionBehaviorTree()
{

	if (actionFlg == false)return;

	//もし行動決まっていないなら新しく思考する。
	if (actionNode == nullptr)
	{

		actionNode = behaviorTree->ActiveNodeInference(this, behaviordata.get());
		//if(ActionNode)ActionNode->ImguiDebug();
	}
	//行動を開始
	if (actionNode != nullptr)
	{
		actionNode = behaviorTree->Run(this, actionNode, behaviordata.get());
	}


}

//消滅処理
void  EnemyBase::Destroy()
{
	//子オブジェクトも削除
	for (int i = 0; i < children.size(); i++)
	{
		GetSceneGame()->GetEnemyManager()->Destroy(children.at(i));
	}

     GetSceneGame()->GetEnemyManager()->Destroy(this);
}
//死亡する時間の更新処理
bool EnemyBase::UpdateDeathTime()
{
	const float DeltaTimer = TK_Lib::Window::GetElapsedTime();
	//死亡時間が経ったら
	if (deathTime <= 0)
	{
		return true;
	}

	deathTime -= DeltaTimer;	
	return false;
}
//自分が視野角内に入っているかどうか
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
	////黒
	//TK_Lib::Draw::Sprite(SpriteIndex, { Pos.x,Pos.y }, VECTOR2{ HpSize       ,10 }, VECTOR4{ 0,(60 / 4) * 3,942 / 3,60 / 4 });
	////ゲージ
	//TK_Lib::Draw::Sprite(SpriteIndex, { Pos.x,Pos.y }, VECTOR2{ TargetHpRatio,10 }, VECTOR4{ 0,0,942 / 3,60 / 4 });
}

bool EnemyBase::AddDamage(const int &damage,const float& maxInvincibleTime)
{
	//体力が0以下なら
	if (GetHp() <= 0)return false;

	hp -= damage;
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
	targetFlg= TargetFlg::COMPLETE;
}
//攻撃目標にできないようになる
void EnemyBase::TargetFaild()
{
	targetFlg = TargetFlg::FAILED;

	//ミニオンの帰還
	for (int i = 0; i < attackSirobo.size(); i++)
	{
		Sirobo* sirobo = attackSirobo.at(i);
		sirobo->ResetNode();
	}

	//子オブジェクトも攻撃目標から消す。
	for (int i = 0; i < children.size(); i++)
	{
		EnemyBase* enm = children.at(i);
		enm->TargetFaild();
	}
}