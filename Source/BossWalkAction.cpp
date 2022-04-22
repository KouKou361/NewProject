#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"


//開始処理
void BossWalkAction::Start()
{
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->BossWalk), true);
	timer = 0;


	//移動目標地点の設定
	targetPos = { 0,0,0 };
	XMVECTOR Target, Pos, OriginPos, V, NV;
	const float Scale = 100;

	{
		VECTOR3 pos = owner->GetPos();
		pos.z += ((rand() % 3) -1)*15;
		pos.x += ((rand() % 3) -1)*15;
		Pos = XMLoadFloat3(&pos);
	}
	{
		VECTOR3 originPos = { 0,0,0 };
		OriginPos = XMLoadFloat3(&originPos);
	}

	{
		V = XMVectorSubtract(OriginPos, Pos);
		NV = XMVector3Normalize(V);
		Target = XMVectorScale(NV,Scale);
	}

	XMStoreFloat3(&targetPos,Target);

	TK_Lib::Lib_Sound::SoundPlay("BossRun", true);
	
	targetPos.y = 0;
}

//実行処理
ActionBase::State BossWalkAction::Run()
{
	const float Speed = 2.0f;
	const float CollisionRadius = 10.0f;
	Advance(Speed);
	owner->Turn(targetPos-owner->GetPos());

	TK_Lib::Debug3D::Circle(targetPos, CollisionRadius);

	if (owner->Length(targetPos) <= CollisionRadius)
	{
		return ActionBase::State::COMPLETE;
	}

	return ActionBase::State::RUN;

	
}

//終了処理
void BossWalkAction::End()
{
	TK_Lib::Lib_Sound::SoundStop("BossRun");
}

//デバッグ用
void BossWalkAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossWalkAction");
	ImGui::End();
}


//前進
void BossWalkAction::Advance(const float AdvanceSpeed)
{
	VECTOR3 Front, MoveVec;
	//前方向ベクトルの取得
	Front = owner->GetFront();
	MoveVec = AdvanceSpeed * Front;

	owner->SetMoveVec(MoveVec);

}
