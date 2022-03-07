#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"


class EnemyBase;

//�J�n����
void DeadAction::Start()
{
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->Die), false);
	owner->SetDeadFlg(false);
	owner->SetDeathTime(1.0f);
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
			owner->Destroy();
			return ActionBase::State::Failed;
		}
	}


	return ActionBase::State::Run;
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
