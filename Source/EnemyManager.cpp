#pragma once
#include "EnemyManager.h"
#include "Collision.h"
#include "SiroboPlayer.h"
#include "Player.h"
#include "CameraController.h"
#include "EffectManager.h"
#include "EffectBase.h"
#include "Scene.h"
#include "EXPManager.h"
#include "EXP.h"

//初期化処理
void EnemyManager::Init()
{
	target = scene->GetPlayer();
}
//更新処理
void EnemyManager::Update()
{
	for (shared_ptr<EnemyBase> enm: enemies)
	{
		if (enm)
		{
			//更新処理
			enm->Update();
		}
	
	}
	//破棄処理
//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する。
	for (shared_ptr<EnemyBase> enm : remove)
	{
		std::vector<shared_ptr<EnemyBase>>::iterator it = std::find(enemies.begin(), enemies.end(), enm);
		if (it != enemies.end())
		{
			enemies.erase(it);
		}
	}
	remove.clear();

}
//描画処理
void EnemyManager::Render()
{
	for (shared_ptr<EnemyBase> enm : enemies)
	{
		if (enm)
		{
			enm->Render();

			//Imgui
			//enm->ImguiDebug();
		}
	}
}
//モデル描画処理
void EnemyManager::ModelRender()
{
	for (shared_ptr<EnemyBase> enm : enemies)
	{
		if (enm)
		{
			enm->ModelRender();
		}
	}
}
//破棄処理
void EnemyManager::Destroy(EnemyBase* enm)
{
	//破棄リストに追加
	for (shared_ptr<EnemyBase> Enm : enemies)
	{
		std::vector<shared_ptr<EnemyBase>>::iterator it = std::find(enemies.begin(), enemies.end(), Enm);
		if (it->get() == enm)
		{
			shared_ptr<EnemyBase> e = Enm;
			remove.emplace_back(e);
		}
	}

	//経験値のだす
	SummonEXP(enm);

	//破壊エフェクト
	SummonDestoryEffect(enm);
	
	//削除するので目標にしていたキャラクターたちの目標をリセット
	ResetTheTargetCharacter(enm);

}
bool EnemyManager::CollisionEnemy(const VECTOR3& pos,const float& weight,const float& collisionRadius,VECTOR3& outPos,EnemyBase*& saveEnm)
{
	VECTOR3 OutPosB;
	bool hitFlg = false;

	for (int i = 0; i <GetEnemiesSize(); i++)
	{
		EnemyBase* enm = GetEnemiesIndex(i);
		if (Collision::Instance().SphereVsSphere(pos, weight, collisionRadius, enm->GetPos(), enm->GetWeight(), enm->GetCollisionRadius(), outPos, OutPosB))
		{
			//enm->SetPos(OutPosB);
			//pos = OutPosB;
			hitFlg= true;
			saveEnm = enm;
		}

	}
	return hitFlg;

}
void EnemyManager::CollisionDebug()
{
	for (shared_ptr<EnemyBase> enm : enemies)
	{
		if (enm)
		{
			enm->CollisionDebug();
		}
	}
}

//全削除
void EnemyManager::Clear()
{
	for (int i = 0; i < GetEnemiesSize(); i++)
	{
		EnemyBase* enm = GetEnemiesIndex(i);
		ResetTheTargetCharacter(enm);
	}

	enemies.clear();
	remove.clear();
}
//敵の行動をするかどうか
void EnemyManager::SetEnemyActive(bool flg)
{
	for (int i = 0; i < GetEnemiesSize(); i++)
	{
		EnemyBase* enm = GetEnemiesIndex(i);
		enm->SetActionFlg(flg);
	}
}
//登録
void EnemyManager::Register(const shared_ptr<EnemyBase>& enm)
{
	enm->Init();
	enm->SetTarget(target);
	enemies.emplace_back(enm);
}
void EnemyManager::ResetTheTargetCharacter(const EnemyBase* enm)
{
	SiroboManager* siroboManager = scene->GetPlayer()->GetSiroboManager();
	//ミニオンの目標リセット
	for (int i = 0; i < siroboManager->GetSiroboSize(); i++)
	{
		//ミニオンの取得
		Sirobo* sirobo= siroboManager->GetSiroboIndex(i);
		//もしミニオンの目標が指定された敵(引数)ならば
		if (sirobo->GetTarget() == enm)
		{
			//目標のリセット
			sirobo->SetTarget(nullptr);
		}
	}

	//プレイヤーの目標のリセット
	if (scene->GetPlayer()->GetTarget() == enm)
	{//目標のリセット
		scene->GetPlayer()->SetTarget(nullptr);
	}

	//カメラのリセット
	if (scene->GetCameraManager()->GetTargetChractor() == enm)
	{//目標のリセット
		scene->GetCameraManager()->ChangeCamera(new CameraNormal(scene->GetPlayer()));
	}
}
//タグから検索していき、最初に検索に当たったEnemyを返す
EnemyBase* EnemyManager::SearchEnemyTag(const EnemyTag& searchTag)
{
	for (int i = 0; i < GetEnemiesSize(); i++)
	{
		EnemyBase* enm = GetEnemiesIndex(i);
		if (enm->GetEnemyTag() == searchTag)
		{
			return enm;
		}
	}
	return nullptr;
}
//経験値のだす
void EnemyManager::SummonEXP(EnemyBase* enm)
{
	//サウンド（ピロン）
	TK_Lib::Lib_Sound::SoundPlay("SummonEXP", false);

	//経験値の出現
	for (int i = 0; i < enm->GetExpNum(); i++)
	{
		shared_ptr<EXP> m_exp = make_shared<EXP>();
		scene->GetExpManager()->Register(m_exp, enm->GetPos());
	}
}

//破壊エフェクトをだす
void EnemyManager::SummonDestoryEffect(EnemyBase* enm)
{
	//破壊エフェクト
	{
		//エフェクトの数
		const int EffectNum = 20;
		scene->GetEffectManager()->GetEffectFromSerchKey("Destroy")->Play(enm->GetPos(), EffectNum);
	}
}