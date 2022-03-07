#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"


//�J�n����
void BossRollAttackAction::Start()
{
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->BossClose_RollLoop), true);
	RollTimer = 0;
	owner->TargetFaild();

	TK_Lib::Lib_Sound::SoundPlay("BossRoll", true);
}

//���s����
ActionBase::State BossRollAttackAction::Run()
{

	owner->TargetFaild();

	Advance(4.0f);
	RollTimer++;
	owner->AttackCircle(owner->GetPos(),10.0f);
	
	//���C�s�b�N���ĕǂɂԂ������Ȃ�I��

	VECTOR3 Start, End,Pos, Front;
	Pos = owner->GetPos();

	const float Scale = 20.0f;
	const float Up = 5.0f;
	//�O�����x�N�g���̎擾
	Front = owner->GetFront();
	Front *= Scale;

	Start = { Pos.x,         Pos.y + Up,Pos.z };
	End   = { Pos.x+ Front.x,Pos.y + Up,Pos.z + Front.z };
	RayOut ray;
	Collision::Instance().RayPick(Start, End, ray);

	TK_Lib::Debug3D::Line(Start,End);
	//�����������Ă���Ȃ�
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
	////�U�����[�V������
	//if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	//{
	//	return ActionBase::State::Run;
	//
	//}
	return ActionBase::State::Run;
	
}

//�I������
void BossRollAttackAction::End()
{

}

//�f�o�b�O�p
void BossRollAttackAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossRollAttackAction");
	ImGui::End();
}

//�O�i
void BossRollAttackAction::Advance(const float AdvanceSpeed)
{
	VECTOR3 Front, MoveVec;
	//�O�����x�N�g���̎擾
	Front=owner->GetFront();
	MoveVec = AdvanceSpeed*Front;

	owner->SetMoveVec(MoveVec);
	
}
