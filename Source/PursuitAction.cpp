#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

//�J�n����
void PursuitAction::Start()
{
	searchFlg = true;
	targetPos = { 0,0,0 };

	//�ǔ��i����j���[�V�����̎擾
	const int RunAnimetionIndex = owner->GetAnime()->GetIndex(owner->GetAnime()->Run);
	//����A�j���[�V�����Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), RunAnimetionIndex, true);

}

//���s����
ActionBase::State PursuitAction::Run()
{
	////�����U������Ă�����������Ȃ�
	//if (owner->GetOldDamageFlg())
	//{
	//	VECTOR3 Pos;
	//	owner->RouteSearch(Pos);
	//	owner->MoveOnPosition(Pos);
	//	return ActionBase::State::Run;
	//}

		//�����U���͈͓��ɂ���Ȃ�
	if (owner->SearchTarget(owner->GetAttackL()))
	{
		return ActionBase::State::FAILED;
	}

	//�ړI�n�Ɉړ��I�i�o�H�T���j
	if (PursuitTarget())
	{
		//���G�͈͂ɂ���Ȃ�
		return ActionBase::State::RUN;
	}


	
	return ActionBase::State::FAILED;


}

//�^�[�Q�b�g�Ɍ������Đi�ށB
bool PursuitAction::PursuitTarget()
{
	//���G�͈͂ɂ���Ȃ�i�o�H�T���j
	if (owner->SearchTarget(owner->GetSearchL()))
	{
		//�i��
		VECTOR3 Pos;
		owner->RouteSearch(Pos);
		owner->MoveOnPosition(Pos);
		return true;

	}
	return false;
}

//�I������
void PursuitAction::End()
{

}


//�f�o�b�O�p
void PursuitAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("Pursuit");
	ImGui::End();
}