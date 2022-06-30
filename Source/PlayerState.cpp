#include "PlayerState.h"
#include "Player.h"
#include "Collision.h"
#include "Animetion.h"
#include "SiroboPlayer.h"
#include "Scene.h"
#include "EnemyManager.h"
//=============================
//プレイヤーの攻撃クラス
//=============================

//初期化
void AttackState::Start(Player* pl)
{
	//攻撃アニメーション
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Attack1),false);
	pl->state = Player::State::ATTACK;

	//攻撃出来る状態
	attackFlg = true;
}
//更新
void AttackState::Run(Player* pl)
{

	//プレイヤーの入力処理
	pl->Input();
	//減速
	DownSpeed(pl);
	//敵との当たり判定
	pl->VsEnemy();
	//レイピックによる位置補正
	pl->UpdateCollision();

	//もし敵がいないなら
	if (pl->GetTarget() == nullptr)
	{
		pl->ChangeState(pl->stateWalk.get());
		return;
	}
	//もしスタンバイ状態のシロボがいない場合
	if (pl->GetSiroboManager()->GetTypeSiroboSize(Sirobo::StateType::TYPE_STAND_BY) == 0)
	{
		pl->ChangeState(pl->stateWalk.get());
		return;
	}

	//敵の方向に向かせる
	VECTOR3 Vec;
	Vec = pl->GetTarget()->GetPos() - pl->GetPos();
	pl->Turn(Vec);

	//もしアニメーション中ではないなら
	if (TK_Lib::Model::IsPlayAnimetion(pl->GetModel()) == false)
	{
		pl->ChangeState(pl->stateWalk.get());
		return;
	}



	float RateTime = TK_Lib::Model::IsPlayAnimetionRate(pl->GetModel());
	//ミニオンの攻撃開始
	if (RateTime>=AttackTimeRate)
	{
		if (attackFlg == true)
		{
			pl->siroboManager->OneAttack(nullptr);
		}

		//攻撃出来る状態をfalseにする
		attackFlg = false;

	}

}
//終了
void AttackState::End(Player* pl)
{

}

void AttackState::DownSpeed(Player* pl)
{
	pl->moveVec.x *= pl->AttackSpeedDown;
	pl->moveVec.y *= pl->AttackSpeedDown;
	pl->moveVec.z *= pl->AttackSpeedDown;
}

//=============================
//プレイヤーのダメージクラス
//=============================

//初期化
void DamageState::Start(Player* pl)
{
	pl->moveVec = { 0,0,0 };
	pl->state = Player::State::DAMAGE;
	pl->SetDamageFlg(false);
	//ダメージアニメーション
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Damage), false);
}
//更新
void DamageState::Run(Player* pl)
{
	//もしアニメーション中ではないなら
	if (TK_Lib::Model::IsPlayAnimetion(pl->GetModel())==false)
	{
		pl->ChangeState(pl->stateWalk.get());
	}
}
//終了
void DamageState::End(Player* pl)
{

}

//=============================
//プレイヤーの死亡クラス
//=============================

//初期化
void DeadState::Start(Player* pl)
{
	pl->moveVec = { 0,0,0 };
	pl->state = Player::State::DEAD;
	pl->SetDeadFlg(false);
	//死亡アニメーション
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Die), false);
	pl->sceneGame->GetEnemyManager()->SetEnemyActive(false);
}
//更新
void DeadState::Run(Player* pl)
{
//	//もしアニメーション中ではないなら
//	if (TK_Lib::Model::IsPlayAnimetion(pl->GetModel()) == false)
//	{
//		pl->ChangeState(pl->stateWalk.get());
//	}
}
//終了
void DeadState::End(Player* pl)
{
	pl->sceneGame->GetEnemyManager()->SetEnemyActive(true);
}

//=============================
//プレイヤーの待機クラス
//=============================

//初期化
void WaitState::Start(Player* pl)
{
	pl->state = Player::State::WAIT;
	//待機アニメーション
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Idle), true);
}
//更新
void WaitState::Run(Player* pl)
{
	//プレイヤーの入力処理
	pl->Input();
	//プレイヤーの回転
	pl->Turn(pl->moveVec);
	
	//もし移動したなら
	if (fabsf(pl->moveVec.x) + fabsf(pl->moveVec.y) + fabsf(pl->moveVec.z) > 0)
	{
		pl->ChangeState(pl->stateWalk.get());
	}
}
//終了
void WaitState::End(Player* pl)
{

}

//=============================
//プレイヤーの移動クラス
//=============================

//初期化
void WalkState::Start(Player* pl)
{
	pl->state = Player::State::WALK;
	//走るアニメーション
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Run), true);
}
//更新
void WalkState::Run(Player* pl)
{
	//プレイヤーの入力処理
	pl->Input();
	//プレイヤーの回転
	pl->Turn(pl->moveVec);
	//敵との当たり判定
	pl->VsEnemy();
	//レイピックによる位置補正
	pl->UpdateCollision();
	//Navメッシュに現在地を更新する
	Collision::Instance().SetTarget(pl->GetPos());
	//過去の地点の保存
	pl->SetOldPos(pl->GetPos());
	//無敵時間の更新
	pl->InvincibleTimeUpdate();

	if (fabsf(pl->moveVec.x) + fabsf(pl->moveVec.y) + fabsf(pl->moveVec.z) == 0)
	{
		pl->ChangeState(pl->stateWait.get());
	}
}
//終了
void WalkState::End(Player* pl)
{

}


//=============================
//プレイヤーのボス専登場演出クラス
//=============================

//初期化
void BossEntryPlayerState::Start(Player* pl)
{
	pl->state = Player::State::BOSS_ENTRY;
	//歩くアニメーション
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Run), true);
	//ボス登場ムーブ中、ちょっと前進しておく。
	pl->moveVec = { 0,0,-0.1f };
}
//更新
void BossEntryPlayerState::Run(Player* pl)
{
	//ボスの方向に向くイベントに移行した時
	if (stage->GetEventState() == EventState::TURN_CAMERA_LOOK_FRONT)
	{
		//前に進むことをやめる。
		TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Idle), true);
		pl->moveVec = { 0,0,0 };
	}

	pl->Move();
}
//終了
void BossEntryPlayerState::End(Player* pl)
{

}






