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
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->Idle), true);
	timer = 0;
}

//���s����
ActionBase::State BossIdeiAction::Run()
{
	timer++;
	constexpr float TimeMax = 300;
	if (timer >= TimeMax)
	{
		return ActionBase::State::Failed;
	}
	return ActionBase::State::Run;

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