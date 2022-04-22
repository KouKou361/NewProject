#include "MinionActionDerived.h"
#include "Player.h"
#include "MinionPlayer.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "Animetion.h"
#include "ObjectManager.h"

//待機行動

//開始処理
void MinionThrowAction::Start()
{
	minionOwner->SetState(MinionPlayer::StateType::TYPE_THROW);
	minionOwner->SetAttackStandBy(false);

	//アニメーションの開始
	TK_Lib::Model::PlayAnimation(minionOwner->GetModel(), minionOwner->GetAnime()->GetIndex("Jump"), false);

	//放物線
	{
		VECTOR3 start, end;
		start = minionOwner->GetPos();
		end = minionOwner->GetTarget()->GetPos();
		end += minionOwner->GetFront() * 5;
	
		//目標地点までにつく時間の算出
		float L =Bullet::GetLength(start, end);
		float g = Bullet::GetGravity();
		float v = 2 * minionOwner->GetSpeed();

		velocity = g * (L / v);
	}

	TK_Lib::Lib_Sound::SoundPlay("MinionAttack", false);


}

//実行処理
ActionBase::State MinionThrowAction::Run()
{	

	velocity -= Bullet::GetGravity() ;

	VECTOR3 MinionOwnerPos = minionOwner->GetPos();
	MinionOwnerPos.y += velocity * TK_Lib::Window::GetElapsedTime();
	minionOwner->SetPos(MinionOwnerPos);

	VECTOR3 VTarget;
	XMVECTOR Vec;
	//ImGui::Begin("H");
	//ImGui::Text("%f", hieght);
	//ImGui::End();

	
	VTarget = minionOwner->GetTarget()->GetPos() - minionOwner->GetPos();
	TK_Lib::Debug3D::Line(minionOwner->GetTarget()->GetPos(), minionOwner->GetPos());
	Vec=XMLoadFloat3(&VTarget);
	Vec=XMVector3Normalize( Vec);
	XMStoreFloat3(&VTarget,Vec);
	minionOwner->SetMoveVec(VTarget);

	//当たり判定
	if (HitCollision())
	{
		return ActionBase::State::COMPLETE;
	}
	//もし何かの出来事で下に行きそうなら帰還
	if (minionOwner->GetPos().y <= -0.5)
	{
		return ActionBase::State::FAILED;
	}
	return ActionBase::State::RUN;
}

//当たり判定処理
bool MinionThrowAction::HitCollision()
{
	//ステージと当たり判定
	VECTOR3 RayStart;
	RayStart.x = minionOwner->GetPos().x;
	RayStart.y = minionOwner->GetPos().y + 1.0f;
	RayStart.z = minionOwner->GetPos().z;

	VECTOR3 RayEnd;
	RayEnd.x = minionOwner->GetPos().x + minionOwner->GetFront().x;
	RayEnd.y = minionOwner->GetPos().y + minionOwner->GetFront().y+1;
	RayEnd.z = minionOwner->GetPos().z + minionOwner->GetFront().z;

	TK_Lib::Debug3D::Line(RayStart, RayEnd);

	RayOut ray;
	Actor* actor=nullptr;
	Collision::Instance().RayPick(RayStart, RayEnd, ray, actor);

	const float collisionR = 2.0f;
	if (actor != nullptr)
	{

		minionOwner->SetPos(ray.Normal *collisionR+minionOwner->GetPos());
		minionOwner->SetTarget(actor);
		return true;
	}
	
	//もしヒットしていないなら
	if (ray.materialIndex >= 0)
	{
			return true;
		
	}

	
	VECTOR3 OutPos;


	//敵との当たり判定
	{
	EnemyBase* OutEnm=nullptr;
	

		if (minionOwner->GetManager()->GetEnemyManager()->CollisionEnemy(
			minionOwner->GetPos(),
			minionOwner->GetWeight(),
			minionOwner->GetCollisionRadius(),
			OutPos, OutEnm)
			)
		{

			if (OutEnm->GetTargetFlg() == TargetFlg::COMPLETE)
			{
				if (OutEnm->GetDeadFlg() == false)
				{
					if (OutEnm != nullptr) {
						minionOwner->SetTarget(OutEnm);
					}
					return true;
				}
			}
	
	

	
		}
	}


	//オブジェクトとの当たり判定
	{

	}

	ObjectBase* OutObj = nullptr;

	if (minionOwner->GetManager()->GetObjectManager()->CollisionObject(
		minionOwner->GetPos(),
		minionOwner->GetWeight(),
		minionOwner->GetCollisionRadius(),
		OutPos, OutObj)
		)
	{
		if (OutObj != nullptr) {
			minionOwner->SetTarget(OutObj);
		}
		return true;
	}
	return false;

}

//終了処理
void MinionThrowAction::End()
{

}

//Imguiデバッグ
void MinionThrowAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Throw");
	ImGui::End();
}

//もし目標物が消えてしまった場合
ActionBase::State MinionThrowAction::DeleteTarget()
{
	//minionOwner->ResetNode();
	return ActionBase::State::COMPLETE;
}