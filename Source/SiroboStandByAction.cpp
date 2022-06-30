#include "SiroboActionDerived.h"
#include "SiroboPlayer.h"
#include "Player.h"
#include "Collision.h"
#include "Animetion.h"

//待機行動


//開始処理
void SiroboStandByAction::Start()
{
	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex(siroboOwner->GetAnime()->Idle), true);
	siroboOwner->SetState(Sirobo::StateType::TYPE_STAND_BY);
	TK_Lib::Lib_Sound::SoundPlay("SiroboAttack", false);
	speed = 0.0f;
	AppropriateAnimesion(idei);
	//全回復
	siroboOwner->SetHp(siroboOwner->GetMaxHp());
}

//群衆処理
void SiroboStandByAction::Flock()
{
	//集合位置
	VECTOR3 TargetPos = (-siroboOwner->GetPlayer()->GetFront()) * 5 + siroboOwner->GetPlayer()->GetPos();


	SiroboManager* manager = siroboOwner->GetManager();

	const float RangeL = 10.0f;
	VECTOR3 AddPosition = { 0,0,0 };//RangeLの範囲内にいるミニオンたちの合計の位置
	VECTOR3 AddVelocity = { 0,0,0 };//RangeLの範囲内にいるミニオンたちの合計の速度
	int SiroboNum = 0;
	float MaxL = FLT_MAX;
	Sirobo* nearSirobo=nullptr;

	
	for (int i = 0; i < manager->GetSiroboSize(); i++)
	{
		//ミニオンの取得
		Sirobo* sirobo = manager->GetSiroboIndex(i);
		if (siroboOwner == sirobo)continue;
		//if (siroboOwner->GetState() != SiroboPlayer::StateType::TypeStandBy)continue;

		//距離の算出
		float L=sirobo->Length(siroboOwner->GetPos());
		//RangeLの範囲内にいるミニオンの算出
		if(RangeL>=L)
		{
			AddPosition += sirobo->GetPos();
			AddVelocity += sirobo->GetVelocity();
			SiroboNum++;
		}


		//一番近くのミニオンの取得
		if (MaxL >= L)
		{
			MaxL = L;
			nearSirobo = sirobo;
		}
	}


	

	//集合位置に進む
	VECTOR3 v2;
	{
		const float power = 0.05f;
		XMVECTOR V;
		v2 = TargetPos-siroboOwner->GetPos();
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
		if (nearSirobo == nullptr)
		{
			siroboOwner->SetMoveVec(v2);
			return;
		}

		const float power = 0.001f;
		XMVECTOR V;
		v = siroboOwner->GetPos() - nearSirobo->GetPos();
		V = XMLoadFloat3(&v);
		V = XMVector3Normalize(V);
		V = XMVectorScale(V, power);
		XMStoreFloat3(&v, V);
	}

	siroboOwner->SetMoveVec(v2+v);


	{
		float l;
		XMVECTOR L, V;
		VECTOR3 V2 = (v2 + v);
		V = XMLoadFloat3(&V2);
		L = XMVector3Length(V);
		XMStoreFloat(&l, L);
		speed = l;
	}

}

//実行処理
ActionBase::State SiroboStandByAction::Run()
{
	Flock();
	SiroboVsSirobo();
	VsPlayer();
	//縦方向の当たり判定（Y方向）
	siroboOwner->VerticalCollision();
	//適切なアニメーションに移行する。
	AllAppropriateAnimesion();

	return ActionBase::State::RUN;
}

ActionBase::State SiroboStandByAction::DeleteTarget()
{
	return Run();
}

void  SiroboStandByAction::SiroboVsSirobo()
{
	SiroboManager* manager = siroboOwner->GetManager();
	for (int i = 0; i < manager->GetSiroboSize(); i++)
	{
		Sirobo* sirobo = manager->GetSiroboIndex(i);
		if (sirobo == siroboOwner)continue;
		VECTOR3 OutPosA, OutPosB;
		if (Collision::Instance().SphereVsSphere(
			siroboOwner->GetPos(), siroboOwner->GetWeight(), siroboOwner->GetCollisionRadius(),
			sirobo->GetPos(), sirobo->GetWeight(), sirobo->GetCollisionRadius(), OutPosA, OutPosB))
		{
			sirobo->SetPos(OutPosB);
			siroboOwner->SetPos(OutPosA);
		}

	}
}
void SiroboStandByAction::VsPlayer()
{
	VECTOR3 OutPosA, OutPosB;
	if (Collision::Instance().SphereVsSphere(
		siroboOwner->GetPos(), siroboOwner->GetWeight(), siroboOwner->GetCollisionRadius(),
		siroboOwner->GetPlayer()->GetPos(), siroboOwner->GetPlayer()->GetWeight(), siroboOwner->GetPlayer()->GetCollisionRadius(), OutPosA, OutPosB))
	{
	//	siroboOwner->GetPlayer()->SetPos(OutPosB);
		siroboOwner->SetPos(OutPosA);
	}
}
//適切なアニメーションに移行する。
bool SiroboStandByAction::AppropriateAnimesion(BaseStandByAnimetion* anime)
{
	
	if (anime->Judge(speed))
	{
		if (current == anime)return true;
		current = anime;
		current->Init();//アニメーション切り替え
		if (current == anime)return true;
	}
	return false;
}

void SiroboStandByAction::AllAppropriateAnimesion()
{
	//走る
	if (AppropriateAnimesion(run))return;
	//待機
	if (AppropriateAnimesion(idei))return;
	//歩く
	if (AppropriateAnimesion(walk))return;

}

//終了処理
void SiroboStandByAction::End()
{

}

//Imguiデバッグ
void SiroboStandByAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("StandBy");
	ImGui::End();
}
