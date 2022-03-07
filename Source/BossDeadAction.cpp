#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "Scene.h"
#include "EffectManager.h"
#include "EffectDerived.h"
#include "ObjectFunctionManager.h"
#include "ObjectFunctionDerive.h"


class EnemyBase;

//�J�n����
void BossDeadAction::Start()
{
	//�A�j���[�V�����̍Đ�
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->Idle), false);
	owner->SetDeathTime(2);
	state = EventDeleteState::Stop;
}

//���s����
ActionBase::State BossDeadAction::Run()
{
	//�������S�A�j���[�V�������I�������Ȃ�
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))return ActionBase::State::Run;


	switch (state)
	{
	case EventDeleteState::Stop://�~�܂�
		StateStop();
		break;
	case EventDeleteState::Fire://�R����
		StateFire();
		break;
	case EventDeleteState::Explosion://����
		StateExplosion();
		break;
	case EventDeleteState::End://�I��
		StateEnd();
		return ActionBase::State::Failed;
		break;
	}


	return ActionBase::State::Run;
}
//�~�܂�
void BossDeadAction::StateStop()
{
	//���S���Ԃ̍X�V
	if (owner->UpdateDeathTime())
	{
		owner->SetDeathTime(3);
		state = EventDeleteState::Fire;
	}
}
//�R����
void BossDeadAction::StateFire()
{
	owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossFire")->Play(owner->GetPos(), 3);
	//���S���Ԃ̍X�V
	if (owner->UpdateDeathTime())
	{
		owner->SetDeathTime(3);
		state = EventDeleteState::Explosion;
	}
}
//����
void BossDeadAction::StateExplosion()
{
	owner->GetSceneGame()->GetEffectManager()->GetEffectFromSerchKey("BossExplosion")->Play(owner->GetPos(), 5);
	//���S���Ԃ̍X�V
	if (owner->UpdateDeathTime())
	{
		state = EventDeleteState::End;
	}
}
//�I��
void BossDeadAction::StateEnd()
{
	owner->Destroy();
}

//�I������
void BossDeadAction::End()
{
	std::shared_ptr<FunctionEnd> objFunction = make_shared<FunctionEnd>(owner->GetSceneGame());
	owner->GetSceneGame()->GetObjectFunctionManager()->Register(objFunction);
	objFunction->SetPos(owner->GetPos());

}

//�f�o�b�O�p
void BossDeadAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossDeadAction");
	ImGui::End();
}
