#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//�J�n����
void IdleAction::Start()
{
	//�ҋ@���[�V�����̎擾
	const int IdeiAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->Idle);
	//�A�j���[�V�����̑ҋ@���[�V�����Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), IdeiAnimetion, true);
}

//���s����
ActionBase::State IdleAction::Run()
{

	//���G���ɂ����true��Ԃ�
	if (owner->SearchTarget(owner->GetSearchL()))
	{
		//�s���I���I���̍s���Ɉڍs
		return ActionBase::State::FAILED;
	}
	//�s���̑��s
	return ActionBase::State::RUN;
}

//�I������
void IdleAction::End()
{

}

//Imgui�f�o�b�O
void IdleAction::DebugImgui()
{
	//TK_Lib::Debug3D::Circle(owner->pos, owner->GetSearchL(), { 0,1,0,1 });

	ImGui::Begin("Action");
	ImGui::Text("Idle");
	ImGui::End();
}