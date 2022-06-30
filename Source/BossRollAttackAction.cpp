#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"
#include "Scene.h"


//��]�U���J�n����
void BossRollAttackAction::Start()
{
	//�{�X�̉�]���[�V�����̎擾
	const int BossRollAttackAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->BossClose_RollLoop);
	//��]�U���A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossRollAttackAnimetion, true);
	//�v���C���[�͍U���ڕW�ɂł��Ȃ��I�i��]���̓~�j�I�������̍U���͎󂯂Ȃ��I�j
	owner->TargetFaild();

	//��]�U���T�E���h
	TK_Lib::Lib_Sound::SoundPlay("BossRoll", true);
}

//���s����
ActionBase::State BossRollAttackAction::Run()
{
	const float Speed = 6.0f;
	//�{�X�̑O�i
	Advance(Speed);

	//�v���C���[���Ԃ���ƃ_���[�W��^���鏈��
	{
		const float AttackCircleRadius = 10.0f;
		owner->AttackCircle(owner->GetPos(), AttackCircleRadius);
	}

	//���f���̃��C�s�b�N�i�ǂɂԂ�������U���I���A��ԕψʁj
	if(ContactWall())
	{
		TK_Lib::Lib_Sound::SoundStop("BossRoll");
		//�U���I���I�ʂ̍s���ֈڍs
		return ActionBase::State::COMPLETE;
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

	//�s���𑱍s�I
	return ActionBase::State::RUN;
	
}

//�I������
void BossRollAttackAction::End()
{

}

//�ǂɂԂ��������ǂ���
bool BossRollAttackAction::ContactWall()
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
	Start = { Pos.x,        Pos.y + RayRickUp,Pos.z };
	//���C�s�b�N�I���ʒu
	End = { Pos.x + Front.x,Pos.y + RayRickUp,Pos.z + Front.z };
	RayOut ray;
	Collision::Instance().RayPick(Start, End, ray);
	//TK_Lib::Debug3D::Line(Start, End);

	//�����������Ă���Ȃ�
	if (ray.materialIndex >= 0)
	{
		return true;
	}
	//�����Ă��Ȃ�
	return false;
	
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
	const float Vibrationtime = 0.1f;
	const float VibrationVolume = 0.25f;
	//�U��
	owner->GetSceneGame()->GetCameraManager()->SetVibration(VibrationVolume, Vibrationtime);

	VECTOR3 Front, MoveVec;
	//�O�����x�N�g���̎擾
	Front=owner->GetFront();
	MoveVec = AdvanceSpeed*Front;

	owner->SetMoveVec(MoveVec);
	
}
