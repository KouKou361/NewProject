#include "SiroboActionDerived.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "Animetion.h"
#include "ObjectManager.h"

//�ҋ@�s��

//�J�n����
void SiroboThrowAction::Start()
{
	siroboOwner->SetState(Sirobo::StateType::TYPE_THROW);
	siroboOwner->SetAttackStandBy(false);

	//�A�j���[�V�����̊J�n
	TK_Lib::Model::PlayAnimation(siroboOwner->GetModel(), siroboOwner->GetAnime()->GetIndex("Jump"), false);

	//������
	SetFirstVelocity();

	TK_Lib::Lib_Sound::SoundPlay("SiroboAttack", false);


}

//���s����
ActionBase::State SiroboThrowAction::Run()
{	


	
	//�d�͂̓K��
	AddGravity();

	//�ڕW�n�_�ɐi��
	TargetToMove();
	
	//�����蔻��
	if (HitCollision())
	{
		return ActionBase::State::COMPLETE;
	}

	const float UnderGround = -0.5f;
	//�������ɍs�������Ȃ�A��
	if (siroboOwner->GetPos().y <= UnderGround)
	{
		return ActionBase::State::FAILED;
	}
	return ActionBase::State::RUN;
}

//�����蔻�菈��
bool SiroboThrowAction::HitCollision()
{

	//�����蔻��p�̃��f���ɐڐG�������ǂ���
	if (HitCollisioinModel())return true;

	//�G�Ƃ̓����蔻��
	if (HitEnemy())	return true;

	//�I�u�W�F�N�g�̓����蔻��
	if (HitObject())return true;

	
	return false;

}

//�I������
void SiroboThrowAction::End()
{

}

//Imgui�f�o�b�O
void SiroboThrowAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Throw");
	ImGui::End();
}

//�����ڕW���������Ă��܂����ꍇ
ActionBase::State SiroboThrowAction::DeleteTarget()
{
	//siroboOwner->ResetNode();
	return ActionBase::State::COMPLETE;
}


//��������`���Đi�ޏ����x�ݒ�
void SiroboThrowAction::SetFirstVelocity()
{
	const float FarL = 5.0f;
	VECTOR3 start, end;
	start = siroboOwner->GetPos();
	end = siroboOwner->GetTarget()->GetPos();
	end += siroboOwner->GetFront() * FarL;
	const float BulletL = 2.0f;

	//�ڕW�n�_�܂łɂ����Ԃ̎Z�o
	float L = Bullet::GetLength(start, end);
	float g = Bullet::GetGravity();
	float v = BulletL * siroboOwner->GetSpeed();

	velocity = g * (L / v);
}

//�d�͂̓K��
void SiroboThrowAction::AddGravity()
{

	velocity -= Bullet::GetGravity();

	VECTOR3 SiroboOwnerPos = siroboOwner->GetPos();
	SiroboOwnerPos.y += velocity * TK_Lib::Window::GetElapsedTime();
	siroboOwner->SetPos(SiroboOwnerPos);

}

//�ڕW�n�_�ɐi��
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

//���f���̓����蔻��
bool SiroboThrowAction::HitCollisioinModel()
{
	const float RayPickUp = 1.0f;
	//�X�e�[�W�Ɠ����蔻��
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

	//�����q�b�g���Ă��Ȃ��Ȃ�
	if (ray.materialIndex >= 0)
	{
		return true;

	}
	return false;
}

//�G�ɓ����蔻��
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

//�I�u�W�F�N�g�̓����蔻��
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