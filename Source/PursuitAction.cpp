#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

//�J�n����
void PursuitAction::Start()
{
	searchFlg = true;
	targetPos = { 0,0,0 };
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->Run), true);
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
		return ActionBase::State::Failed;
	}
	//���G�͈͂ɂ���Ȃ�
	if (owner->SearchTarget(owner->GetSearchL()))
	{
		VECTOR3 Pos;
		owner->RouteSearch(Pos);
		owner->MoveOnPosition(Pos);
		return ActionBase::State::Run;
	}
	return ActionBase::State::Failed;


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