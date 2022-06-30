#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "Scene.h"
#include "EffectManager.h"
#include "EffectDerived.h"
#include "ObjectFunctionManager.h"
#include "ObjectFunctionDerive.h"


class EnemyBase;

//�J�n����
void BossDeadAction::Start()
{
	//�T�E���h�I��
	TK_Lib::Lib_Sound::SoundStop("BossRun");

	//�ҋ@���[�V�����ԍ��̎擾
	const int BossDeadIdeiIndex = owner->GetAnime()->GetIndex(owner->GetAnime()->Idle);
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossDeadIdeiIndex, false);
	state = EventDeleteState::STOP;
}

//���s����
ActionBase::State BossDeadAction::Run()
{
	//���S���o�ɂ���āA��ԕψ�
	switch (state)
	{
	case EventDeleteState::STOP://�~�܂�
		StateStop();
		break;
	case EventDeleteState::FIRE://�R����
		StateFire();
		break;
	case EventDeleteState::EXPLOSION://����
		StateExplosion();
		break;
	case EventDeleteState::END://�I��
		StateEnd();
		//���̍s���Ɉڍs
		return ActionBase::State::FAILED;
		break;
	}


	return ActionBase::State::RUN;
}

//�I������
void BossDeadAction::End()
{
	const float Vibrationtime = 6.0f;
	const float VibrationVolume = 0.15f;
	//�U��
	owner->GetSceneGame()->GetCameraManager()->SetVibration(VibrationVolume, Vibrationtime);
	//�Q�[���N���A�I�u�W�F�N�g�̐���
	{
		std::shared_ptr<FunctionEnd> objFunction = make_shared<FunctionEnd>(owner->GetSceneGame());
		owner->GetSceneGame()->GetObjectFunctionManager()->Register(objFunction);
		objFunction->SetPos(owner->GetPos());
	}

}

//�f�o�b�O�p
void BossDeadAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossDeadAction");
	ImGui::End();
}


//�~�܂���
void BossDeadAction::StateStop()
{
	//���S���Ԃ̍X�V
	if (owner->UpdateDeathTime())
	{
		TK_Lib::Lib_Sound::SoundPlay("BossRoll", false);
		//�̗͂��O�ɂȂ��Ă�������Ă��܂��܂ł̎���
		constexpr float DeathTime = 2.0f;
		//���S�^�C���̐ݒ�
		owner->SetDeathTime(DeathTime);
		//���̏�Ԃ�
		state = EventDeleteState::FIRE;
	}
}
//�R������
void BossDeadAction::StateFire()
{
	//���G�t�F�N�g
	{
		//�G�t�F�N�g�̏o����
		const int EffectPlayNum = 3;
		//���G�t�F�N�g�̏o��
		owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossFire")->Play(owner->GetPos(), EffectPlayNum);
	}

	//���S���Ԃ̍X�V
	if (owner->UpdateDeathTime())
	{
		TK_Lib::Lib_Sound::SoundPlay("BossExplosion", false);

		const float MaskSpeed = 0.2f;
		owner->MaskStart(MaskSpeed);

		////�̗͂��O�ɂȂ��Ă�������Ă��܂��܂ł̎���
		//constexpr float DeathTime = 3.0f;
		////���S�^�C���̐ݒ�
		//owner->SetDeathTime(DeathTime);
		// ���̏�Ԃ�
		state = EventDeleteState::EXPLOSION;
	}
}
//�������
void BossDeadAction::StateExplosion()
{
	const float Vibrationtime = 0.1f;
	const float VibrationVolume = 0.5f;
	//�U��
	owner->GetSceneGame()->GetCameraManager()->SetVibration(VibrationVolume, Vibrationtime);
	//�����G�t�F�N�g
	{
		//�G�t�F�N�g�̏o����
		const int EffectPlayNum = 3;
		//���G�t�F�N�g�̏o��
		owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossExplosion")->Play(owner->GetPos(), EffectPlayNum);
	}

	if (owner->GetMaskVolume() >= 1.0f)
	{
		// ���̏�Ԃ�
		state = EventDeleteState::END;
	}
}
//�I�����
void BossDeadAction::StateEnd()
{
	//���ŏ���
	owner->Destroy();
}

