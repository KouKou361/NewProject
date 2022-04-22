#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"


//回転攻撃開始処理
void BossRollAttackAction::Start()
{
	//回転攻撃アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->BossClose_RollLoop), true);
	//プレイヤーは攻撃目標にできない！（回転中はミニオンたちの攻撃は受けない！）
	owner->TargetFaild();

	//回転攻撃サウンド
	TK_Lib::Lib_Sound::SoundPlay("BossRoll", true);
}

//実行処理
ActionBase::State BossRollAttackAction::Run()
{
	//攻撃
	//owner->TargetFaild();

	//ボスの前進
	Advance(4.0f);
	//回転攻撃の処理
	owner->AttackCircle(owner->GetPos(),10.0f);
	




	//モデルのレイピック（壁にぶつかったら攻撃終了、状態変位）
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
		Start = { Pos.x,         Pos.y + RayRickUp,Pos.z };
		//レイピック終了位置
		End = { Pos.x + Front.x,Pos.y + RayRickUp,Pos.z + Front.z };
		RayOut ray;
		Collision::Instance().RayPick(Start, End, ray);
		//TK_Lib::Debug3D::Line(Start, End);
		
		//もし当たっているなら
		if (ray.materialIndex >= 0)
		{
			//攻撃終了！別の行動へ移行
			TK_Lib::Lib_Sound::SoundStop("BossRoll");
			return ActionBase::State::COMPLETE;
		}
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
	return ActionBase::State::RUN;
	
}

//終了処理
void BossRollAttackAction::End()
{

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
	VECTOR3 Front, MoveVec;
	//前方向ベクトルの取得
	Front=owner->GetFront();
	MoveVec = AdvanceSpeed*Front;

	owner->SetMoveVec(MoveVec);
	
}
