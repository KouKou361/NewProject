#include "ObjectDerived.h"
#include "Collision.h"
#include "Scene.h"
#include "MinionPlayer.h"

//初期化処理
void ObjectPot::Init()
{
	SetQuaternion({ 0, 0, 0, 1 });
	//SetPos({ 0,0,0 });
	SetScale({ 0.1f,0.1f,0.1f });

	//SetCollisionModel("Pat");
	SetModel(TK_Lib::Load::GetModel("Pat"));

	SetHp(10);
	SetMaxHp(GetHp());


	SetTag(ObjectTag::TAG_OBJECT);
	collisionRadius = 5;
	objectType = ObjectType::Pot;


	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());

}
//更新処理
void ObjectPot::Update()
{

}

bool ObjectPot::AddDamage(int Damage, int MaxinvincibleTime)
{
	//体力が0以下なら
	if (GetHp() <= 0)return false;

	SetHp(GetHp() - Damage);
	//もし生き残っていたなら
	if (GetHp() >= 1)
	{	//オブジェクトのダメージ処理
		this->Damage();
	}
	else//死亡しているなら
	{

		{
			//ミニオンの召喚
			shared_ptr<MinionPlayer> minion;
			minion = make_shared<MinionPlayer>();
			minion->Init(scene->GetPlayer());
			minion->SetPos(this->GetPos());
			//	minion->pos = { 5,0,static_cast<float>(140) };
			scene->GetPlayer()->GetMinionManager()->Register(minion);
		}

		
		//ダメージフラグのオン
		Dead();
	}
	return true;
}
