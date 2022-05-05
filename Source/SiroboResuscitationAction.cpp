#include "SiroboActionDerived.h"
#include "Player.h"
#include "SiroboPlayer.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "Bullet.h"
#include "Animetion.h"

//待機行動

//開始処理
void SiroboResuscitationAction::Start()
{
	siroboOwner->SetMoveVec({ 0,0,0 });
	siroboOwner->resuscitationTime = 0;
}

//実行処理
ActionBase::State SiroboResuscitationAction::Run()
{
	if (!siroboOwner->IsResuscitation())
	{
		siroboOwner->SetState(Sirobo::StateType::TYPE_DEAD);
		//蘇生されていないなら
		return ActionBase::State::FAILED;
	}

	//蘇生更新処理
	UpdateResuscitation();
	if (siroboOwner->GetState() == Sirobo::StateType::TYPE_STAND_BY)
	{
		return ActionBase::State::FAILED;
	}

	siroboOwner->resuscitationFlg = false;
	return ActionBase::State::RUN;

	
}

//蘇生処理
void SiroboResuscitationAction::Resuscitation()
{
	siroboOwner->resuscitationTime = 0;
	siroboOwner->SetHp(siroboOwner->GetMaxHp());
	siroboOwner->SetState(Sirobo::StateType::TYPE_STAND_BY);
}

//蘇生更新処理
void SiroboResuscitationAction::UpdateResuscitation()
{
	siroboOwner->resuscitationTime+=TK_Lib::Window::GetElapsedTime();

	//プレイヤーが蘇生する時間
	const float MaxResuscitationTime = 1;

	if (siroboOwner->resuscitationTime >= MaxResuscitationTime)
	{
		Resuscitation();
	}

}

//もし目標物が消えてしまった場合
ActionBase::State SiroboResuscitationAction::DeleteTarget()
{
	return Run();
}
//終了処理
void SiroboResuscitationAction::End()
{
	siroboOwner->resuscitationTime = 0;
}

//Imguiデバッグ
void SiroboResuscitationAction::DebugImgui()
{
	ImGui::Begin("Sirobo");
	ImGui::Text("Resuscitation");
	ImGui::Text("ResuscitationTime=%f", siroboOwner->resuscitationTime);
	ImGui::End();
}