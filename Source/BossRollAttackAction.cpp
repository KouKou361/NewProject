#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"


//��]�U���J�n����
void BossRollAttackAction::Start()
{
	//��]�U���A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->BossClose_RollLoop), true);
	//�v���C���[�͍U���ڕW�ɂł��Ȃ��I�i��]���̓~�j�I�������̍U���͎󂯂Ȃ��I�j
	owner->TargetFaild();

	//��]�U���T�E���h
	TK_Lib::Lib_Sound::SoundPlay("BossRoll", true);
}

//���s����
ActionBase::State BossRollAttackAction::Run()
{
	//�U��
	//owner->TargetFaild();

	//�{�X�̑O�i
	Advance(4.0f);
	//��]�U���̏���
	owner->AttackCircle(owner->GetPos(),10.0f);
	




	//���f���̃��C�s�b�N�i�ǂɂԂ�������U���I���A��ԕψʁj
	{
		//���ʃ��C�s�b�N�̒���
		constexpr float RayRickFrontLength = 20.0f;
		//������Əォ�烌�C�s�b�N
		constexpr float RayRickUp = 5.0f;

		VECTOR3 Start, End, Pos, Front;
		Pos = owner->GetPos();
		//�O�����x�N�g���̎擾
		Front = owner->GetFront();
		Front *= RayRickFrontLength;
		//���C�s�b�N�J�n�ʒu
		Start = { Pos.x,         Pos.y + RayRickUp,Pos.z };
		//���C�s�b�N�I���ʒu
		End = { Pos.x + Front.x,Pos.y + RayRickUp,Pos.z + Front.z };
		RayOut ray;
		Collision::Instance().RayPick(Start, End, ray);
		//TK_Lib::Debug3D::Line(Start, End);
		
		//�����������Ă���Ȃ�
		if (ray.materialIndex >= 0)
		{
			//�U���I���I�ʂ̍s���ֈڍs
			TK_Lib::Lib_Sound::SoundStop("BossRoll");
			return ActionBase::State::COMPLETE;
		}
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
	return ActionBase::State::RUN;
	
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

//�O�i����
void BossRollAttackAction::Advance(const float AdvanceSpeed)
{
	VECTOR3 Front, MoveVec;
	//�O�����x�N�g���̎擾
	Front=owner->GetFront();
	MoveVec = AdvanceSpeed*Front;

	owner->SetMoveVec(MoveVec);
	
}
