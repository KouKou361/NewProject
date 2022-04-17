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
	minionOwner->ResuscitationTime = 0;
}

//実行処理
ActionBase::State MinionResuscitationAction::Run()
{
	if (!minionOwner->IsResuscitation())
	{
		minionOwner->SetState(MinionPlayer::StateType::TYPE_DEAD);
		//蘇生されていないなら
		return ActionBase::State::Failed;
	}

	//蘇生更新処理
	UpdateResuscitation();
	if (minionOwner->GetState() == MinionPlayer::StateType::TYPE_STAND_BY)
	{
		return ActionBase::State::Failed;
	}

	minionOwner->ResuscitationFlg = false;
	return ActionBase::State::Run;

	
}

//蘇生処理
void MinionResuscitationAction::Resuscitation()
{
	minionOwner->ResuscitationTime = 0;
	minionOwner->SetHp(minionOwner->GetMaxHp());
	minionOwner->SetState(MinionPlayer::StateType::TYPE_STAND_BY);
}

//蘇生更新処理
void MinionResuscitationAction::UpdateResuscitation()
{
	minionOwner->ResuscitationTime++;
	const int MaxResuscitationTime = 60;

	if (minionOwner->ResuscitationTime >= MaxResuscitationTime)
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
	minionOwner->ResuscitationTime = 0;
}

//Imguiデバッグ
void MinionResuscitationAction::DebugImgui()
{
	ImGui::Begin("Minion");
	ImGui::Text("Resuscitation");
	ImGui::Text("ResuscitationTime=%d", minionOwner->ResuscitationTime);
	ImGui::End();
}