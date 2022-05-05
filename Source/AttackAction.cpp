#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//�J�n����
void AttackAction::Start()
{
	//�U���A�j���[�V�����ԍ��̎擾
	const int AttackAnimetionIndex = owner->GetAnime()->GetIndex(owner->GetAnime()->Attack1);
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), AttackAnimetionIndex, false);
}

//���s����
ActionBase::State AttackAction::Run()
{
	//�G�̕����Ɍ���
	VECTOR3 Vec =owner->GetTarget()->GetPos()- owner->GetPos();
	owner->Turn(Vec);


	//�U�����[�V�������ɍU������B
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//�U���J�n���[�g
		constexpr float AttackStartTime = 0.0f;
		//�U���I�����[�g
		constexpr float AttackEndTime   = 0.5f;

		//�U������
		owner->AttackCircleNode(owner->GetAttackNode(), owner->GetAttackRadius(), AttackStartTime, AttackEndTime);
		return ActionBase::State::RUN;

	}

	return ActionBase::State::FAILED;
}
void AttackAction::DebugRender()
{
	//TK_Lib::Debug3D::Circle(owner->GetPos(), owner->GetAttackRadius());
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
