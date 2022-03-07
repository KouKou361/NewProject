#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//開始処理
void BossRollAttackStartAction::Start()
{
	owner->TargetFaild();
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->BossOpenGoToRoll), false);
}

//実行処理
ActionBase::State BossRollAttackStartAction::Run()
{

	owner->TargetFaild();
	PlayerToTurn();
	//攻撃モーション中
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
	

		//サウンド
		float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());

		if (AnimetionRate >= 0.7f)
		{
			if (AnimetionRate <= 0.72f)
			{
				TK_Lib::Lib_Sound::SoundPlay("BossAttackStart", false);
			}
		}

		return ActionBase::State::Run;

	}

	return ActionBase::State::Complete;
}

//終了処理
void BossRollAttackStartAction::PlayerToTurn()
{
	//攻撃目標に向く
	VECTOR3 TargetPos=owner->GetTarget()->GetPos();
	VECTOR3 OwnerPos = owner->GetPos();
	owner->Turn(TargetPos- OwnerPos);
}

//終了処理
void BossRollAttackStartAction::End()
{

}

//デバッグ用
void BossRollAttackStartAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossRollAttackStartAction");
	ImGui::End();
}
