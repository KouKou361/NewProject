#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"


//�J�n����
void BossWalkAction::Start()
{
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->BossWalk), true);
	timer = 0;


	//�ړ��ڕW�n�_�̐ݒ�
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

//���s����
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

//�I������
void BossWalkAction::End()
{
	TK_Lib::Lib_Sound::SoundStop("BossRun");
}

//�f�o�b�O�p
void BossWalkAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossWalkAction");
	ImGui::End();
}


//�O�i
void BossWalkAction::Advance(const float AdvanceSpeed)
{
	VECTOR3 Front, MoveVec;
	//�O�����x�N�g���̎擾
	Front = owner->GetFront();
	MoveVec = AdvanceSpeed * Front;

	owner->SetMoveVec(MoveVec);

}
