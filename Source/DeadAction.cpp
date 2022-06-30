#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//�J�n����
void DeadAction::Start()
{

	//�{�X�̉�]�U���I�����[�V�����̎擾
	const int BossDamageAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->Die);

	//�A�j���[�V�����̎��S���[�V�����Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossDamageAnimetion, false);

	owner->SetDeadFlg(false);


	//�ڕW�ɂ���Ȃ�����B
	owner->TargetFaild();
	//���S���Ԃ̐ݒ�
	const float DeathTime = 1.0f;
	owner->SetDeathTime(DeathTime);
}

//���s����
ActionBase::State DeadAction::Run()
{

	//�������S�A�j���[�V�������I�������Ȃ�
	if (!TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//���S���Ԃ̍X�V
		if (owner->UpdateDeathTime())
		{
			const float MaskSpeed = 1.5f;
			owner->MaskStart(MaskSpeed);
		
		}
	}

	if (owner->GetMaskVolume() >= 1.0f)
	{
		//���S���ԂɂȂ�����
		owner->Destroy();
		return ActionBase::State::FAILED;
	}

	//���̍s���Ɉڍs
	return ActionBase::State::RUN;
}

//�I������
void DeadAction::End()
{

}

//�f�o�b�O�p
void DeadAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("Dead");
	ImGui::End();
}
