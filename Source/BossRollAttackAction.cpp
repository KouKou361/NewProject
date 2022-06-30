#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "Scene.h"


//回転攻撃開始処理
void BossRollAttackAction::Start()
{
	//ボスの回転モーションの取得
	const int BossRollAttackAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->BossClose_RollLoop);
	//回転攻撃アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossRollAttackAnimetion, true);
	//プレイヤーは攻撃目標にできない！（回転中はミニオンたちの攻撃は受けない！）
	owner->TargetFaild();

	//回転攻撃サウンド
	TK_Lib::Lib_Sound::SoundPlay("BossRoll", true);
}

//実行処理
ActionBase::State BossRollAttackAction::Run()
{
	const float Speed = 6.0f;
	//ボスの前進
	Advance(Speed);

	//プレイヤーがぶつかるとダメージを与える処理
	{
		const float AttackCircleRadius = 10.0f;
		owner->AttackCircle(owner->GetPos(), AttackCircleRadius);
	}

	//モデルのレイピック（壁にぶつかったら攻撃終了、状態変位）
	if(ContactWall())
	{
		TK_Lib::Lib_Sound::SoundStop("BossRoll");
		//攻撃終了！別の行動へ移行
		return ActionBase::State::COMPLETE;
	}	
	//if (ray.materialIndex < -1);
	//{
	//	return ActionBase::State::Complete;
	//}
	//if (RollTimerMax >= RollTimer)
	//{
	//	return ActionBase::State::Run;
	//}
	////攻撃モーション中
	//if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	//{
	//	return ActionBase::State::Run;
	//
	//}

	//行動を続行！
	return ActionBase::State::RUN;
	
}

//終了処理
void BossRollAttackAction::End()
{

}

//壁にぶつかったかどうか
bool BossRollAttackAction::ContactWall()
{
	//正面レイピックの長さ
	constexpr float RayRickFrontLength = 20.0f;
	//ちょっと上からレイピック
	constexpr float RayRickUp = 5.0f;



	VECTOR3 Start, End, Pos, Front;
	Pos = owner->GetPos();
	//前方向ベクトルの取得
	Front = owner->GetFront();
	Front *= RayRickFrontLength;
	//レイピック開始位置
	Start = { Pos.x,        Pos.y + RayRickUp,Pos.z };
	//レイピック終了位置
	End = { Pos.x + Front.x,Pos.y + RayRickUp,Pos.z + Front.z };
	RayOut ray;
	Collision::Instance().RayPick(Start, End, ray);
	//TK_Lib::Debug3D::Line(Start, End);

	//もし当たっているなら
	if (ray.materialIndex >= 0)
	{
		return true;
	}
	//当っていない
	return false;
	
}

//デバッグ用
void BossRollAttackAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossRollAttackAction");
	ImGui::End();
}

//前進する
void BossRollAttackAction::Advance(const float AdvanceSpeed)
{
	const float Vibrationtime = 0.1f;
	const float VibrationVolume = 0.25f;
	//振動
	owner->GetSceneGame()->GetCameraManager()->SetVibration(VibrationVolume, Vibrationtime);

	VECTOR3 Front, MoveVec;
	//前方向ベクトルの取得
	Front=owner->GetFront();
	MoveVec = AdvanceSpeed*Front;

	owner->SetMoveVec(MoveVec);
	
}
