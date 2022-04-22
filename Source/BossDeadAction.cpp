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
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->Idle), false);
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
		return ActionBase::State::FAILED;
		break;
	}


	return ActionBase::State::RUN;
}
//�~�܂���
void BossDeadAction::StateStop()
{
	//���S���Ԃ̍X�V
	if (owner->UpdateDeathTime())
	{
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
	owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossFire")->Play(owner->GetPos(), 3);
	//���S���Ԃ̍X�V
	if (owner->UpdateDeathTime())
	{
		//�̗͂��O�ɂȂ��Ă�������Ă��܂��܂ł̎���
		constexpr float DeathTime = 3.0f;
		//���S�^�C���̐ݒ�
		owner->SetDeathTime(DeathTime);
		// ���̏�Ԃ�
		state = EventDeleteState::EXPLOSION;
	}
}
//�������
void BossDeadAction::StateExplosion()
{
	owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossExplosion")->Play(owner->GetPos(), 5);

	//���S���Ԃ̍X�V
	if (owner->UpdateDeathTime())
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

//�I������
void BossDeadAction::End()
{
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
