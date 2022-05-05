#include "ObjectDerived.h"
#include "Collision.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"
#include "UIDerived.h"

//初期化処理
void ObjectTower::Init()
{
	//モデルの設定
	SetModel(TK_Lib::Load::GetModel("Tower"));

	//ステータスデータの設定
	SetStatus("Tower");

	//タグの設定
	SetTag(ObjectTag::TAG_OBJECT);
	objectType = ObjectType::TOWER;

	//スポットライトの作成
	spotLightHandle=TK_Lib::SpotLight::Create(GetPos(), { 1,0,1,1 }, 20.0f);

	//モデルの行列更新
	TK_Lib::Model::Tranceform(GetModel(), GetPos(), GetQuaternion(), GetScale());

	//ライトの明るさ
	spotLightRadius = 10.0f;

	timer = 0.0f;
}
//更新処理
void ObjectTower::Update()
{
	//時間の更新処理
	timer += TK_Lib::Window::GetElapsedTime();
	
	//スポットライトの更新処理
	TK_Lib::SpotLight::Set(spotLightHandle, GetPos(), { 1,0,1,1 }, sinf(timer)* spotLightRadius+20.0f);
	
}
//オブジェクトの死亡処理
void ObjectTower::Dead()
{
	//タワーの数を知らせる点滅タイマー
	const float blinkingTimer = 10.0f;
	scene->GetStageManager()->GetNowStage()->GetNumTower()->SetBlinkingTimer(blinkingTimer);

	//エフェクトの数（タワーの破棄エフェクトをだす）
	const int EffectNum = 30;
	scene->GetEffectManager()->GetEffectFromSerchKey("TowerBreak")->Play(GetPos(), EffectNum);

	//タワーのサウンド
	TK_Lib::Lib_Sound::SoundPlay("TowerBreak",false);
	TK_Lib::Lib_Sound::SoundPlay("TowerBreak2", false);

	//スポットライトの破棄
	TK_Lib::SpotLight::Delete(spotLightHandle);

	Destroy();
}
