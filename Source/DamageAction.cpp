#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//�J�n����
void DamageAction::Start()
{
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->Damage), false);
	owner->SetDamageFlg(false);
}

//���s����
ActionBase::State DamageAction::Run()
{
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		return ActionBase::State::Run;
	}
	return ActionBase::State::Failed;
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