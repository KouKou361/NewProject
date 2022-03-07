#include "ObjectDerived.h"
#include "Collision.h"
//初期化処理
void ObjectWall::Init()
{
	SetQuaternion({ 0, 0, 0, 1 });
	//SetPos({ 0,0,0 });
	SetScale({ 0.1f,0.1f,0.1f });

	SetCollisionModel("CollisionWall");
	SetModel(TK_Lib::Load::GetModel("Wall"));

	SetHp(10);
	SetMaxHp(GetHp());

	SetTag(ObjectTag::TagObject);

	collisionRadius = 5;
	objectType = ObjectType::Wall;


	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
	
}
//更新処理
void ObjectWall::Update()
{

}