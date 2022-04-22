#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"
#include "Collision.h"


//�J�n����
void BossIdeiAction::Start()
{
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->Idle), true);
	ideiTimer = 0;
}

//���s����
ActionBase::State BossIdeiAction::Run()
{
	//�ҋ@�I������
	constexpr float TimeMax = 5;
	//�ҋ@���Ԃ̍X�V����
	ideiTimer += TK_Lib::Window::GetElapsedTime();


	if (ideiTimer >= TimeMax)
	{
		//�ҋ@�I���I���̃X�e�[�g�Ɉڍs
		return ActionBase::State::FAILED;
	}
	return ActionBase::State::RUN;

}

//�I������
void BossIdeiAction::End()
{

}

//�f�o�b�O�p
void BossIdeiAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossIdeiAction");
	ImGui::End();
}