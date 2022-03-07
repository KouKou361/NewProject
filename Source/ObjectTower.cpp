#include "ObjectDerived.h"
#include "Collision.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"
#include "UIDerived.h"

//初期化処理
void ObjectTower::Init()
{
	SetQuaternion({ 0, 0, 0, 1 });
	//SetPos({ 0,0,0 });
	SetScale({ 0.1f,0.1f,0.1f });

	//SetCollisionModel("Pat");
	SetModel(TK_Lib::Load::GetModel("Tower"));

	SetHp(10);
	SetMaxHp(GetHp());


	SetTag(ObjectTag::TagObject);
	collisionRadius = 5;
	objectType = ObjectType::Tower;

	spotLightHandle=TK_Lib::SpotLight::Create(GetPos(), { 1,0,1,1 }, 20.0f);


	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());
	timer = 0.0f;
	spotLightRadius = 10.0f;
}
//更新処理
void ObjectTower::Update()
{
	timer += TK_Lib::Window::GetElapsedTime();
	
	TK_Lib::SpotLight::Set(spotLightHandle, GetPos(), { 1,0,1,1 }, sinf(timer)* spotLightRadius+20.0f);
	
}
//オブジェクトの死亡処理
void ObjectTower::Dead()
{
	scene->GetStageManager()->GetNowStage()->GetNumTower()->SetBlinkingTimer(10.0f);
	scene->GetEffectManager()->GetEffectFromSerchKey("TowerBreak")->Play(GetPos(), 30);
	TK_Lib::Lib_Sound::SoundPlay("TowerBreak",false);
	TK_Lib::Lib_Sound::SoundPlay("TowerBreak2", false);
	TK_Lib::SpotLight::Delete(spotLightHandle);
	Destroy();
}
