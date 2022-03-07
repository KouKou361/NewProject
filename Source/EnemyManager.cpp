#pragma once
#include "EnemyManager.h"
#include "Collision.h"
#include "MinionPlayer.h"
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
	Target = scene->GetPlayer();
}
//更新処理
void EnemyManager::Update()
{
	for (shared_ptr<EnemyBase> enm: enemies)
	{
		if (enm)
		{
			enm->Update();

			ImGui::Begin("Attack");
			ImGui::Text("AttackMinion=%d", enm->AttackMinions.size());
			ImGui::End();
		}
	
	}
	//破棄処理
//更新処理が終わった後に破棄リストに積まれたオブジェクトを削除する。
	for (shared_ptr<EnemyBase> enm : remove)
	{
		//std::vectorから要素を破棄する場合はイレテーターで削除しなければならない
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
void EnemyManager::Destroy(EnemyBase* Enm)
{
	for (shared_ptr<EnemyBase> enm : enemies)
	{
		std::vector<shared_ptr<EnemyBase>>::iterator it = std::find(enemies.begin(), enemies.end(), enm);
		if (it->get() == Enm)
		{
			shared_ptr<EnemyBase> e = enm;
			remove.emplace_back(e);
		}
	}

	TK_Lib::Lib_Sound::SoundPlay("SummonEXP", false);
	for(int i=0;i<5;i++)
	{
		shared_ptr<EXP> m_exp = make_shared<EXP>();
		scene->GetExpManager()->Register(m_exp,Enm->GetPos());
	}

	scene->GetEffectManager()->GetEffectFromSerchKey("Destroy")->Play(Enm->GetPos(),20);

	//削除するので目標にしていたキャラクターたちの
	//目標リセット
	ResetTheTargetCharacter(Enm);

}
bool EnemyManager::CollisionEnemy(const VECTOR3 pos,const float weight,const float collisionRadius,VECTOR3& OutPos,EnemyBase*& SaveEnm)
{
	VECTOR3 OutPosB;
	bool hitFlg = false;

	for (int i = 0; i <GetEnemiesSize(); i++)
	{
		EnemyBase* enm = GetEnemiesIndex(i);
		if (Collision::Instance().SphereVsSphere(pos, weight, collisionRadius, enm->GetPos(), enm->GetWeight(), enm->GetCollisionRadius(), OutPos, OutPosB))
		{
			//enm->SetPos(OutPosB);
			//pos = OutPosB;
			hitFlg= true;
			SaveEnm = enm;
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
void EnemyManager::Register(shared_ptr<EnemyBase> enm)
{
	enm->Init();
	enm->SetTarget(Target);
	enemies.emplace_back(enm);
}
void EnemyManager::ResetTheTargetCharacter(EnemyBase* enm)
{
	MinionManager* minionManager = scene->GetPlayer()->GetMinionManager();
	//ミニオンの目標リセット
	for (int i = 0; i < minionManager->GetMinionsSize(); i++)
	{
		//ミニオンの取得
		MinionPlayer* minion= minionManager->GetMinionIndex(i);
		//もしミニオンの目標が指定された敵(引数)ならば
		if (minion->GetTarget() == enm)
		{
			//目標のリセット
			minion->SetTarget(nullptr);
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
EnemyBase* EnemyManager::SearchEnemyTag(const EnemyTag searchTag)
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