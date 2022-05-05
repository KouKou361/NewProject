#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"


//開始処理
void BossWalkAction::Start()
{

	//ボスの回転攻撃終了モーションの取得
	const int BossWalkAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->BossWalk);
	//アニメーションの歩く再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossWalkAnimetion, true);
	

	//目的地を算出する関数
	SetTargetPos();

	//ボスの歩くサウンド
	TK_Lib::Lib_Sound::SoundPlay("BossRun", true);
	
	targetPos.y = 0;
	timer = 0;
}

//実行処理
ActionBase::State BossWalkAction::Run()
{
	const float Speed = 2.0f;
	const float CollisionRadius = 10.0f;

	//前進
	Advance(Speed);

	//目標地点に向く
	owner->Turn(targetPos-owner->GetPos());

	//目標地点に移動したかどうか
	if (owner->Length(targetPos) <= CollisionRadius)
	{
		//目的地についたので別の行動へ
		return ActionBase::State::COMPLETE;
	}
	//目的地につくまで行動続行
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

void BossWalkAction::SetTargetPos()
{
	//移動目標地点の設定
	targetPos = { 0,0,0 };
	XMVECTOR Target, Pos, OriginPos, V, NV;
	const float Scale = 50;
	const float RandMin = -25;
	const float RandMax = 25;

	//目的地方向の設定
	{
		VECTOR3 pos = owner->GetPos();
		pos.z += Mathf::RandomRange(RandMin, RandMax);
		pos.x += Mathf::RandomRange(RandMin, RandMax);
		Pos = XMLoadFloat3(&pos);
	}

	//原点の設定
	{
		VECTOR3 originPos = { 0,0,0 };
		OriginPos = XMLoadFloat3(&originPos);
	}

	//目的地の方向を元に目的地の算出
	{
		V = XMVectorSubtract(Pos, OriginPos);
		NV = XMVector3Normalize(V);
		Target = XMVectorScale(NV,Scale);
	}

	XMStoreFloat3(&targetPos,Target);
}
