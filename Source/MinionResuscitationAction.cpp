#include "MinionActionDerived.h"
#include "Player.h"
#include "MinionPlayer.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "Animetion.h"

//待機行動

//開始処理
void MinionResuscitationAction::Start()
{
	minionOwner->SetMoveVec({ 0,0,0 });
	minionOwner->resuscitationTime = 0;
}

//実行処理
ActionBase::State MinionResuscitationAction::Run()
{
	if (!minionOwner->IsResuscitation())
	{
		minionOwner->SetState(MinionPlayer::StateType::TYPE_DEAD);
		//蘇生されていないなら
		return ActionBase::State::FAILED;
	}

	//蘇生更新処理
	UpdateResuscitation();
	if (minionOwner->GetState() == MinionPlayer::StateType::TYPE_STAND_BY)
	{
		return ActionBase::State::FAILED;
	}

	minionOwner->resuscitationFlg = false;
	return ActionBase::State::RUN;

	
}

//蘇生処理
void MinionResuscitationAction::Resuscitation()
{
	minionOwner->resuscitationTime = 0;
	minionOwner->SetHp(minionOwner->GetMaxHp());
	minionOwner->SetState(MinionPlayer::StateType::TYPE_STAND_BY);
}

//蘇生更新処理
void MinionResuscitationAction::UpdateResuscitation()
{
	minionOwner->resuscitationTime++;
	const int MaxResuscitationTime = 60;

	if (minionOwner->resuscitationTime >= MaxResuscitationTime)
	{
		Resuscitation();
	}

}

//もし目標物が消えてしまった場合
ActionBase::State MinionResuscitationAction::DeleteTarget()
{
	return Run();
}
//終了処理
void MinionResuscitationAction::End()
{
	minionOwner->resuscitationTime = 0;
}

//Imguiデバッグ
void MinionResuscitationAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Resuscitation");
	ImGui::Text("ResuscitationTime=%d", minionOwner->resuscitationTime);
	ImGui::End();
}