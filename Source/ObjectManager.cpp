#pragma once
#include "ObjectManager.h"
#include "Collision.h"
#include "SiroboPlayer.h"
#include "Player.h"
#include "CameraController.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"

//初期化処理
void ObjectManager::Init()
{

}
//更新処理
void ObjectManager::Update()
{
	for (shared_ptr<ObjectBase> obj : objes)
	{
		if (obj)
		{
			obj->Update();
		}

	}
	//破棄処理
//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する。
	for (shared_ptr<ObjectBase> obj : remove)
	{
		//std::vectorから要素を破棄する場合はイレテーターで削除しなければならない
		std::vector<shared_ptr<ObjectBase>>::iterator it = std::find(objes.begin(), objes.end(), obj);
		if (it != objes.end())
		{
			objes.erase(it);
		}
	}
	remove.clear();

}
//描画処理
void ObjectManager::Render()
{
	//for (shared_ptr<ObjectBase> obj : objes)
	//{
	//	if (obj)
	//	{
	//		obj->Render();
	//
	//		//Imgui
	//		//obj->ImguiDebug();
	//	}
	//}
}
//モデル描画処理
void ObjectManager::ModelRender()
{
	for (shared_ptr<ObjectBase> obj : objes)
	{
		if (obj)
		{
			obj->ModelRender();
		}
	}
}
//破棄処理
void ObjectManager::Destroy(ObjectBase* obj)
{
	for (shared_ptr<ObjectBase> m_obj : objes)
	{
		std::vector<shared_ptr<ObjectBase>>::iterator it = std::find(objes.begin(), objes.end(), m_obj);
		if (it->get() == obj)
		{
			shared_ptr<ObjectBase> e = m_obj;
			remove.emplace_back(e);
		}
	}


	//削除するので目標にしていたキャラクターたちの
	//目標リセット
	ResetTheTargetCharacter(obj);

}

//全てのオブジェクトの当たり判定（円と円）
bool ObjectManager::CollisionCircleObject(const VECTOR3 pos, const float weight, const float collisionRadius, VECTOR3& OutPos, ObjectBase*& Saveobj)
{
	VECTOR3 OutPosB;
	bool hitFlg = false;

	for (int i = 0; i < GetObjesSize(); i++)
	{
		ObjectBase* obj = GetObjesIndex(i);
		if (Collision::Instance().SphereVsSphere(pos, weight, collisionRadius, obj->GetPos(), obj->GetWeight(), obj->GetCollisionRadius(), OutPos, OutPosB))
		{
			//obj->SetPos(OutPosB);
			//pos = OutPosB;
			hitFlg = true; 
			Saveobj = obj;
		}

	}
	return hitFlg;

}
//現在のタワーの数
int ObjectManager::GetTowerNum()
{
	int PotNum = 0;

	for (int i = 0; i < GetObjesSize(); i++)
	{
		ObjectBase* obj = GetObjesIndex(i);
		if (obj->GetType() == ObjectType::TOWER)
		{
			PotNum++;
		}
	}
	return PotNum;

}

//当たり判定のモデル描画
void ObjectManager::CollisionDebug()
 {
	for (shared_ptr<ObjectBase> obj : objes)
	{
		if (obj)
		{
		//	obj->CollisionDebug();
		}
	}
}

//全削除
void ObjectManager::Clear()
{
	for (int i = 0; i < GetObjesSize(); i++)
	{
		ObjectBase* obj = GetObjesIndex(i);
		ResetTheTargetCharacter(obj);
	}

	objes.clear();
	remove.clear();
}
//登録
void ObjectManager::Register(shared_ptr<ObjectBase> obj)
{
	obj->Init();
	objes.emplace_back(obj);
}
//目標にしているシロボ達、攻撃中のシロボ達、カメラを全てのキャンセルする。
void ObjectManager::ResetTheTargetCharacter(ObjectBase* obj)
{
	//ミニオンの目標リセット
	for (int i = 0; i < sceneGame->GetPlayer()->GetSiroboManager()->GetSiroboSize(); i++)
	{
		//ミニオンの取得
		Sirobo* sirobo = sceneGame->GetPlayer()->GetSiroboManager()->GetSiroboIndex(i);
		//もしミニオンの目標が指定された敵(引数)ならば
		if (sirobo->GetTarget() == obj)
		{
			//目標のリセット
			sirobo->SetTarget(nullptr);
		}
	}

	//プレイヤーの目標のリセット
	if (sceneGame->GetPlayer()->GetTarget() == obj)
	{//目標のリセット
		sceneGame->GetPlayer()->SetTarget(nullptr);
	}

	//カメラのリセット
	if (sceneGame->GetCameraManager()->GetTargetChractor() == obj)
	{//目標のリセット
		sceneGame->GetCameraManager()->ChangeCamera(new CameraNormal(sceneGame->GetPlayer()));
	}
}