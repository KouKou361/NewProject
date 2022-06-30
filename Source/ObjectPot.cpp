#include "ObjectDerived.h"
#include "Collision.h"
#include "Scene.h"
#include "SiroboPlayer.h"

//初期化処理
void ObjectPot::Init()
{
	//モデルの設定
	SetModel(TK_Lib::Load::GetModel("Pat"));
	//ステータスデータの設定
	SetStatus("Pot");
	//タグの設定
	SetTag(ObjectTag::TAG_OBJECT);
	objectType = ObjectType::POT;

	//モデルの行列更新
	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());

}
//更新処理
void ObjectPot::Update()
{
	TK_Lib::Model::UpdateMask(GetModel());

	if (GetMaskVolume() >= 1.0f)
	{
		Destroy();
	}
}

bool ObjectPot::AddDamage(const int& damage, const float& maxInvincibleTime)
{
	//体力が0以下なら
	if (GetHp() <= 0)return false;

	SetHp(GetHp() - damage);
	//もし生き残っていたなら
	if (GetHp() >= 1)
	{	//オブジェクトのダメージ処理
		this->Damage();
	}
	else//死亡しているなら
	{
		//ミニオンの召喚
		SummonSirobo();
	
		//ダメージフラグのオン
		Dead();
	}
	return true;
}

//シロボの召喚
void ObjectPot::SummonSirobo()
{
	shared_ptr<Sirobo> sirobo;
	sirobo = make_shared<Sirobo>();
	sirobo->Init(scene->GetPlayer());
	sirobo->SetPos(this->GetPos());
	//	sirobo->pos = { 5,0,static_cast<float>(140) };
	scene->GetPlayer()->GetSiroboManager()->Register(sirobo);

}
