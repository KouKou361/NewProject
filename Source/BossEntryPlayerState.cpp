#include "PlayerState.h"
#include "Player.h"
#include "Collision.h"
#include "Animetion.h"
#include "MinionPlayer.h"
#include "Stage.h"

//=============================
//プレイヤーのボス専登場演出クラス
//=============================

//初期化
void BossEntryPlayerState::Start(Player* pl)
{
	pl->state = Player::State::BOSS_ENTRY;
	TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Run), true);
	pl->moveVec = { 0,0,-0.1f };
}
//更新
void BossEntryPlayerState::Run(Player* pl)
{
	if (stage->GetEventState() == EventState::TURN_CAMERA_LOOK_FRONT)
	{
		TK_Lib::Model::PlayAnimation(pl->GetModel(), pl->anime->GetIndex(pl->anime->Idle), true);
		pl->moveVec = { 0,0,0 };
	}

	pl->Move();

	////プレイヤーの入力処理
	//pl->Input();
	////プレイヤーの回転
	//pl->Turn(pl->moveVec);
	////敵との当たり判定
	//pl->VsEnemy();
	////レイピックによる位置補正
	//pl->UpdateCollision();
	////Navメッシュに現在地を更新する
	//Collision::Instance().SetTarget(pl->GetPos());
	////過去の地点の保存
	//pl->SetOldPos(pl->GetPos());
	////無敵時間の更新
	//pl->InvincibleTimeUpdate();

	//if (fabsf(pl->moveVec.x) + fabsf(pl->moveVec.y) + fabsf(pl->moveVec.z) == 0)
	//{
	//	pl->ChangeState(pl->stateWait.get());
	//}
}
//終了
void BossEntryPlayerState::End(Player* pl)
{

}



