#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//�J�n����
void DamageAction::Start()
{
	//�{�X�̉�]�U���I�����[�V�����̎擾
	const int BossDamageAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->Damage);
	//�_���[�W���󂯂�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossDamageAnimetion, false);

	//�_���[�W�ʒm
	owner->SetDamageFlg(false);
}

//���s����
ActionBase::State DamageAction::Run()
{
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//�s�����s
		return ActionBase::State::RUN;
	}

	//�s���Ɉڍs
	return ActionBase::State::FAILED;
}

//�I������
void DamageAction::End()
{

}

//�f�o�b�O�p
void DamageAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("Damage");
	ImGui::End();
}
