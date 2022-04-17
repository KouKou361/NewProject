#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//�J�n����
void AttackAction::Start()
{
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->Attack1), false);
}

//���s����
ActionBase::State AttackAction::Run()
{

	VECTOR3 Vec =owner->GetTarget()->GetPos()- owner->GetPos();
	owner->Turn(Vec);

	//�U�����[�V������
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		owner->AttackCircleNode(owner->GetAttackNode(), owner->GetAttackRadius(), 0.0f, 0.5f);
		return ActionBase::State::Run;

	}

	return ActionBase::State::Failed;
}
void AttackAction::DebugRender()
{
	TK_Lib::Debug3D::Circle(owner->GetPos(), owner->GetAttackRadius());
}

//�I������
void AttackAction::End()
{

}

//�f�o�b�O�p
void AttackAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("Attack");
	ImGui::End();
}
