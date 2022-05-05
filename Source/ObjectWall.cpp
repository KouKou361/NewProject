#include "ObjectDerived.h"
#include "Collision.h"
//初期化処理
void ObjectWall::Init()
{
	//モデルの設定
	SetCollisionModel("CollisionWall");

	//ステータスデータの設定
	SetModel(TK_Lib::Load::GetModel("Wall"));

	//タグの設定
	SetTag(ObjectTag::TAG_OBJECT);
	objectType = ObjectType::WALL;

	//モデルの行列更新
	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
	
}
//更新処理
void ObjectWall::Update()
{

}