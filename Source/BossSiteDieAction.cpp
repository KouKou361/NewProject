#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "Scene.h"
#include"EffectManager.h"
#include "EffectBase.h"



class EnemyBase;

//�J�n����
void BossSiteDieAction::Start()
{
	//�A�j���[�V�����̍Đ�
	//TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->Die), false);
	//owner->SetDeadFlg(false);
	//owner->SetDeathTime(1.0f);

}

//���s����
ActionBase::State BossSiteDieAction::Run()
{
	//�G�t�F�N�g�̐�
	const int EffectNum = 1;
	//���G�t�F�N�g�̏o��
	owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossSiteBreak")->Play(owner->GetPos(), EffectNum);
	//�s�����s
	return ActionBase::State::RUN;
}

//�I������
void BossSiteDieAction::End()
{

}

//�f�o�b�O�p
void BossSiteDieAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossSiteDieAction");
	ImGui::End();
}
