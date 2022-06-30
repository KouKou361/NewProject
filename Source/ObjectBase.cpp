#include "ObjectBase.h"
#include "ObjectManager.h"
#include "Collision.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"
#include "ExportScript.h"

//当たり判定用のモデル
void ObjectBase::SetCollisionModel(const string &CollisionModelKey)
{
	collisionModel=TK_Lib::Load::GetModel(CollisionModelKey);
	TK_Lib::Model::Tranceform(collisionModel, GetPos(), GetQuaternion(), GetScale());
	TK_Lib::Model::PlayAnimation(collisionModel,0,false);

	//当たり判定モデルリストに追加
	Collision::Instance().RegisterModel(collisionModel, ModelCollisionType::COLLISION_MODEL, this);
}

//初期化処理
void ObjectBase::Init()
{
	SetTag(ObjectTag::TAG_OBJECT);
}

//更新処理
void ObjectBase::Update()
{
//	//モデルの行列更新
//	if (GetModel() >= 0)
//	{
//		TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
//		TK_Lib::Model::AnimetionUpdate(GetModel());
//	}

	if (GetMaskVolume()>=1.0f)
	{
		Destroy();
	}
}

//モデルの描画処理
void ObjectBase::ModelRender()
{
	//モデルの描画
	if (GetModel() >= 0)
	{
		if (TK_Lib::Camera::IsCamera(GetPos()))
		{
			TK_Lib::Draw::Model(GetModel(), ShaderType::Shader_MakeShadow);
		}

	}
}

//当たり判定用の描画
void ObjectBase::CollisionRender()
{
	if (GetModel() >= 0)
	{
		TK_Lib::Draw::Model(collisionModel, ShaderType::Shader_NoLight);
	}
}

//ImGuiのデバッグ
void ObjectBase::ImguiDebug()
{

}

void ObjectBase::HPRender(const int &SpriteIndex, const VECTOR2 &Pos)
{

}

//破棄処理
void ObjectBase::Destroy()
{
	
	objectManager->Destroy(this);
	//当たり判定用のモデルも破棄
	Collision::Instance().DeleteCollisionModel(collisionModel);
}

bool ObjectBase::AddDamage(const int &damage,const float &maxInvincibleTime)
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
		//ダメージフラグのオン
		Dead();
	}
	return true;
}

//マスクスタート
void ObjectBase::MaskStart(const float speed)
{
	TK_Lib::Model::MaskStart(GetModel(), speed);
}
//マスク大きさ取得
float ObjectBase::GetMaskVolume()
{
	return TK_Lib::Model::GetMaskVolume(GetModel());
}


//オブジェクトの死亡処理
void ObjectBase::Dead()
{
	//破棄時のエフェクト
	const int EffectNum = 20;
	scene->GetEffectManager()->GetEffectFromSerchKey("Destroy")->Play(GetPos(), EffectNum);

	const float MaskSpeed = 0.5f;
	MaskStart(MaskSpeed);

}

//オブジェクトのダメージ処理
void ObjectBase::Damage()
{

}

//ステータスの設定
void ObjectBase::SetStatus(const string &SearchName)
{
	ObjectStatusData* data = scene->GetexportSCV()->GetObjectStatusDataSearchName(SearchName);
	SetQuaternion({ 0,0,0,1 });
	SetScale({ data->GetScale(),data->GetScale(),data->GetScale() });
	SetHp(data->GetHp());
	SetMaxHp(GetHp());
	collisionRadius = data->GetCollisionRadius();

}