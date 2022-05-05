#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"


//�J�n����
void BossWalkAction::Start()
{

	//�{�X�̉�]�U���I�����[�V�����̎擾
	const int BossWalkAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->BossWalk);
	//�A�j���[�V�����̕����Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossWalkAnimetion, true);
	

	//�ړI�n���Z�o����֐�
	SetTargetPos();

	//�{�X�̕����T�E���h
	TK_Lib::Lib_Sound::SoundPlay("BossRun", true);
	
	targetPos.y = 0;
	timer = 0;
}

//���s����
ActionBase::State BossWalkAction::Run()
{
	const float Speed = 2.0f;
	const float CollisionRadius = 10.0f;

	//�O�i
	Advance(Speed);

	//�ڕW�n�_�Ɍ���
	owner->Turn(targetPos-owner->GetPos());

	//�ڕW�n�_�Ɉړ��������ǂ���
	if (owner->Length(targetPos) <= CollisionRadius)
	{
		//�ړI�n�ɂ����̂ŕʂ̍s����
		return ActionBase::State::COMPLETE;
	}
	//�ړI�n�ɂ��܂ōs�����s
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

void BossWalkAction::SetTargetPos()
{
	//�ړ��ڕW�n�_�̐ݒ�
	targetPos = { 0,0,0 };
	XMVECTOR Target, Pos, OriginPos, V, NV;
	const float Scale = 50;
	const float RandMin = -25;
	const float RandMax = 25;

	//�ړI�n�����̐ݒ�
	{
		VECTOR3 pos = owner->GetPos();
		pos.z += Mathf::RandomRange(RandMin, RandMax);
		pos.x += Mathf::RandomRange(RandMin, RandMax);
		Pos = XMLoadFloat3(&pos);
	}

	//���_�̐ݒ�
	{
		VECTOR3 originPos = { 0,0,0 };
		OriginPos = XMLoadFloat3(&originPos);
	}

	//�ړI�n�̕��������ɖړI�n�̎Z�o
	{
		V = XMVectorSubtract(Pos, OriginPos);
		NV = XMVector3Normalize(V);
		Target = XMVectorScale(NV,Scale);
	}

	XMStoreFloat3(&targetPos,Target);
}
