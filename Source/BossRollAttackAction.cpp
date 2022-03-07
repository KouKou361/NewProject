#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"


//開始処理
void BossRollAttackAction::Start()
{
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->BossClose_RollLoop), true);
	RollTimer = 0;
	owner->TargetFaild();

	TK_Lib::Lib_Sound::SoundPlay("BossRoll", true);
}

//実行処理
ActionBase::State BossRollAttackAction::Run()
{

	owner->TargetFaild();

	Advance(4.0f);
	RollTimer++;
	owner->AttackCircle(owner->GetPos(),10.0f);
	
	//レイピックして壁にぶつかったなら終了

	VECTOR3 Start, End,Pos, Front;
	Pos = owner->GetPos();

	const float Scale = 20.0f;
	const float Up = 5.0f;
	//前方向ベクトルの取得
	Front = owner->GetFront();
	Front *= Scale;

	Start = { Pos.x,         Pos.y + Up,Pos.z };
	End   = { Pos.x+ Front.x,Pos.y + Up,Pos.z + Front.z };
	RayOut ray;
	Collision::Instance().RayPick(Start, End, ray);

	TK_Lib::Debug3D::Line(Start,End);
	//もし当たっているなら
	if (ray.materialIndex >= 0)
	{
		TK_Lib::Lib_Sound::SoundStop("BossRoll");
		return ActionBase::State::Complete;
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
	return ActionBase::State::Run;
	
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

//前進
void BossRollAttackAction::Advance(const float AdvanceSpeed)
{
	VECTOR3 Front, MoveVec;
	//前方向ベクトルの取得
	Front=owner->GetFront();
	MoveVec = AdvanceSpeed*Front;

	owner->SetMoveVec(MoveVec);
	
}
