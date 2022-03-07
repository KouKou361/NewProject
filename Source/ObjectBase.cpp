#include "ObjectBase.h"
#include "ObjectManager.h"
#include "Collision.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"
//当たり判定用のモデル
void ObjectBase::SetCollisionModel(string CollisionModelKey)
{
	collisionModel=TK_Lib::Load::GetModel(CollisionModelKey);
	TK_Lib::Model::Tranceform(collisionModel, GetPos(), GetQuaternion(), GetScale());
	TK_Lib::Model::PlayAnimation(collisionModel,0,false);
	Collision::Instance().RegisterModel(collisionModel, ModelCollisionType::CollisionModel, this);
}
//初期化処理
void ObjectBase::Init()
{
	SetTag(ObjectTag::TagObject);
}
//更新処理
void ObjectBase::Update()
{
	//モデルの行列更新
	if (GetModel() >= 0)
	{
		TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
		TK_Lib::Model::AnimetionUpdate(GetModel());
	}
}
//描画処理
void ObjectBase::ModelRender()
{
	if (GetModel() >= 0)
	{

		if (TK_Lib::Camera::IsCamera(GetPos(), 35.0f))
		{
			TK_Lib::Draw::Model(GetModel(), ShaderType::Shader_MakeShadow);
		}

	}
}
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

void ObjectBase::HPRender(const int SpriteIndex, const VECTOR2 Pos)
{

}
void ObjectBase::Destroy()
{
	
	objectManager->Destroy(this);
	Collision::Instance().DeleteCollisionModel(collisionModel);
}
bool ObjectBase::AddDamage(int Damage, int MaxinvincibleTime)
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
		//ダメージフラグのオン
		Dead();
	}
	return true;
}

//オブジェクトの死亡処理
void ObjectBase::Dead()
{
	scene->GetEffectManager()->GetEffectFromSerchKey("Destroy")->Play(GetPos(), 20);
	Destroy();
}
//オブジェクトのダメージ処理
void ObjectBase::Damage()
{

}