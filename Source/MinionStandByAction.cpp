#include "MinionActionDerived.h"
#include "MinionPlayer.h"
#include "Player.h"
#include "Collision.h"
#include "Animetion.h"
//待機行動


//開始処理
void MinionStandByAction::Start()
{
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(), minionOwner->GetAnime()->GetIndex(minionOwner->GetAnime()->Idle), true);
	minionOwner->SetState(MinionPlayer::StateType::TYPE_STAND_BY);
	TK_Lib::Lib_Sound::SoundPlay("MinionAttack", false);
	
	//全回復
	minionOwner->SetHp(minionOwner->GetMaxHp());
}

//群衆処理
void MinionStandByAction::Flock()
{
	//集合位置
	VECTOR3 TargetPos = (-minionOwner->GetPlayer()->GetFront()) * 5 + minionOwner->GetPlayer()->GetPos();


	MinionManager* manager = minionOwner->GetManager();

	const float RangeL = 10.0f;
	VECTOR3 AddPosition = { 0,0,0 };//RangeLの範囲内にいるミニオンたちの合計の位置
	VECTOR3 AddVelocity = { 0,0,0 };//RangeLの範囲内にいるミニオンたちの合計の速度
	int MinionNum = 0;
	float MaxL = FLT_MAX;
	MinionPlayer* nearMinion=nullptr;

	
	for (int i = 0; i < manager->GetMinionsSize(); i++)
	{
		//ミニオンの取得
		MinionPlayer* minion = manager->GetMinionIndex(i);
		if (minionOwner == minion)continue;
		//if (minionOwner->GetState() != MinionPlayer::StateType::TypeStandBy)continue;

		//距離の算出
		float L=minion->Length(minionOwner->GetPos());
		//RangeLの範囲内にいるミニオンの算出
		if(RangeL>=L)
		{
			AddPosition += minion->GetPos();
			AddVelocity += minion->GetVelocity();
			MinionNum++;
		}


		//一番近くのミニオンの取得
		if (MaxL >= L)
		{
			MaxL = L;
			nearMinion = minion;
		}
	}


	

	//集合位置に進む
	VECTOR3 v2;
	{
		const float power = 0.05f;
		XMVECTOR V;
		v2 = TargetPos-minionOwner->GetPos();
		V = XMLoadFloat3(&v2);

		float l;
		XMVECTOR L;
		L = XMVector3Length(V);
		XMStoreFloat(&l,L);
		l *= power;


		V = XMVector3Normalize(V);
		V = XMVectorScale(V, l);
		XMStoreFloat3(&v2, V);
	}

	

	//近くにいるミニオンに離れる
	VECTOR3 v;
	{
		//もし近くにミニオンがいないなら
		if (nearMinion == nullptr)
		{
			minionOwner->SetMoveVec(v2);
			return;
		}

		const float power = 0.001f;
		XMVECTOR V;
		v = minionOwner->GetPos() - nearMinion->GetPos();
		V = XMLoadFloat3(&v);
		V = XMVector3Normalize(V);
		V = XMVectorScale(V, power);
		XMStoreFloat3(&v, V);
	}

	minionOwner->SetMoveVec(v2+v);
}

//実行処理
ActionBase::State MinionStandByAction::Run()
{
	Flock();
	MinionVsMinion();
	VsPlayer();
	//縦方向の当たり判定（Y方向）
	minionOwner->VerticalCollision();

	return ActionBase::State::Run;
}

ActionBase::State MinionStandByAction::DeleteTarget()
{
	return Run();
}

void  MinionStandByAction::MinionVsMinion()
{
	MinionManager* manager = minionOwner->GetManager();
	for (int i = 0; i < manager->GetMinionsSize(); i++)
	{
		MinionPlayer* minion = manager->GetMinionIndex(i);
		if (minion == minionOwner)continue;
		VECTOR3 OutPosA, OutPosB;
		if (Collision::Instance().SphereVsSphere(
			minionOwner->GetPos(), minionOwner->GetWeight(), minionOwner->GetCollisionRadius(),
			minion->GetPos(), minion->GetWeight(), minion->GetCollisionRadius(), OutPosA, OutPosB))
		{
			minion->SetPos(OutPosB);
			minionOwner->SetPos(OutPosA);
		}

	}
}
void MinionStandByAction::VsPlayer()
{
	VECTOR3 OutPosA, OutPosB;
	if (Collision::Instance().SphereVsSphere(
		minionOwner->GetPos(), minionOwner->GetWeight(), minionOwner->GetCollisionRadius(),
		minionOwner->GetPlayer()->GetPos(), minionOwner->GetPlayer()->GetWeight(), minionOwner->GetPlayer()->GetCollisionRadius(), OutPosA, OutPosB))
	{


	//	minionOwner->GetPlayer()->SetPos(OutPosB);
		minionOwner->SetPos(OutPosA);
	}
}

//終了処理
void MinionStandByAction::End()
{

}

//Imguiデバッグ
void MinionStandByAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("StandBy");
	ImGui::End();
}
