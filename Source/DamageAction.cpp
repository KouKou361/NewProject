#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//開始処理
void DamageAction::Start()
{
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->GetAnime()->GetIndex(owner->GetAnime()->Damage), false);
	owner->SetDamageFlg(false);
}

//実行処理
ActionBase::State DamageAction::Run()
{
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		return ActionBase::State::RUN;
	}
	return ActionBase::State::FAILED;
}

//終了処理
void DamageAction::End()
{

}

//デバッグ用
void DamageAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("Damage");
	ImGui::End();
}
