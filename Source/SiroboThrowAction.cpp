#include "SiroboActionDerived.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "Animetion.h"
#include "ObjectManager.h"

//待機行動

//開始処理
void SiroboThrowAction::Start()
{
	siroboOwner->SetState(Sirobo::StateType::TYPE_THROW);
	siroboOwner->SetAttackStandBy(false);

	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex("Jump"), false);

	//放物線
	SetFirstVelocity();

	TK_Lib::Lib_Sound::SoundPlay("SiroboAttack", false);


}

//実行処理
ActionBase::State SiroboThrowAction::Run()
{	


	
	//重力の適応
	AddGravity();

	//目標地点に進む
	TargetToMove();
	
	//当たり判定
	if (HitCollision())
	{
		return ActionBase::State::COMPLETE;
	}

	const float UnderGround = -0.5f;
	//もし下に行きそうなら帰還
	if (siroboOwner->GetPos().y <= UnderGround)
	{
		return ActionBase::State::FAILED;
	}
	return ActionBase::State::RUN;
}

//当たり判定処理
bool SiroboThrowAction::HitCollision()
{

	//当たり判定用のモデルに接触したかどうか
	if (HitCollisioinModel())return true;

	//敵との当たり判定
	if (HitEnemy())	return true;

	//オブジェクトの当たり判定
	if (HitObject())return true;

	
	return false;

}

//終了処理
void SiroboThrowAction::End()
{

}

//Imguiデバッグ
void SiroboThrowAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Throw");
	ImGui::End();
}

//もし目標物が消えてしまった場合
ActionBase::State SiroboThrowAction::DeleteTarget()
{
	//siroboOwner->ResetNode();
	return ActionBase::State::COMPLETE;
}


//放物線を描いて進む初速度設定
void SiroboThrowAction::SetFirstVelocity()
{
	const float FarL = 5.0f;
	VECTOR3 start, end;
	start = siroboOwner->GetPos();
	end = siroboOwner->GetTarget()->GetPos();
	end += siroboOwner->GetFront() * FarL;
	const float BulletL = 2.0f;

	//目標地点までにつく時間の算出
	float L = Bullet::GetLength(start, end);
	float g = Bullet::GetGravity();
	float v = BulletL * siroboOwner->GetSpeed();

	velocity = g * (L / v);
}

//重力の適応
void SiroboThrowAction::AddGravity()
{

	velocity -= Bullet::GetGravity();

	VECTOR3 SiroboOwnerPos = siroboOwner->GetPos();
	SiroboOwnerPos.y += velocity * TK_Lib::Window::GetElapsedTime();
	siroboOwner->SetPos(SiroboOwnerPos);

}

//目標地点に進む
void SiroboThrowAction::TargetToMove()
{
	VECTOR3 VTarget;
	XMVECTOR Vec;
	VTarget = siroboOwner->GetTarget()->GetPos() - siroboOwner->GetPos();
	//TK_Lib::Debug3D::Line(siroboOwner->GetTarget()->GetPos(), siroboOwner->GetPos());
	Vec = XMLoadFloat3(&VTarget);
	Vec = XMVector3Normalize(Vec);
	XMStoreFloat3(&VTarget, Vec);
	siroboOwner->SetMoveVec(VTarget);

}

//モデルの当たり判定
bool SiroboThrowAction::HitCollisioinModel()
{
	const float RayPickUp = 1.0f;
	//ステージと当たり判定
	VECTOR3 RayStart;
	RayStart.x = siroboOwner->GetPos().x;
	RayStart.y = siroboOwner->GetPos().y + RayPickUp;
	RayStart.z = siroboOwner->GetPos().z;

	VECTOR3 RayEnd;
	RayEnd.x = siroboOwner->GetPos().x + siroboOwner->GetFront().x;
	RayEnd.y = siroboOwner->GetPos().y + siroboOwner->GetFront().y + RayPickUp;
	RayEnd.z = siroboOwner->GetPos().z + siroboOwner->GetFront().z;

	//TK_Lib::Debug3D::Line(RayStart, RayEnd);

	RayOut ray;
	Actor* actor = nullptr;
	Collision::Instance().RayPick(RayStart, RayEnd, ray, actor);

	const float collisionR = 2.0f;
	if (actor != nullptr)
	{

		siroboOwner->SetPos(ray.Normal * collisionR + siroboOwner->GetPos());
		siroboOwner->SetTarget(actor);
		return true;
	}

	//もしヒットしていないなら
	if (ray.materialIndex >= 0)
	{
		return true;

	}
	return false;
}

//敵に当たり判定
bool SiroboThrowAction::HitEnemy()
{
	EnemyBase* OutEnm = nullptr;
	VECTOR3 OutPos;


	if (siroboOwner->GetManager()->GetEnemyManager()->CollisionEnemy(
		siroboOwner->GetPos(),
		siroboOwner->GetWeight(),
		siroboOwner->GetCollisionRadius(),
		OutPos, OutEnm)
		)
	{

		if (OutEnm->GetTargetFlg() == TargetFlg::COMPLETE)
		{
			if (OutEnm->GetDeadFlg() == false)
			{
				if (OutEnm != nullptr) {
					siroboOwner->SetTarget(OutEnm);
				}
				return true;
			}
		}
	}
	return false;
}

//オブジェクトの当たり判定
bool SiroboThrowAction::HitObject()
{
	ObjectBase* OutObj = nullptr;
	VECTOR3 OutPos;

	if (siroboOwner->GetManager()->GetObjectManager()->CollisionCircleObject(
		siroboOwner->GetPos(),
		siroboOwner->GetWeight(),
		siroboOwner->GetCollisionRadius(),
		OutPos, OutObj)
		)
	{
		if (OutObj != nullptr) {
			siroboOwner->SetTarget(OutObj);
		}
		return true;
	}
	return false;
}