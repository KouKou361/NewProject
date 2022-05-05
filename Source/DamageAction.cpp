#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//開始処理
void DamageAction::Start()
{
	//ボスの回転攻撃終了モーションの取得
	const int BossDamageAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->Damage);
	//ダメージを受けるアニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossDamageAnimetion, false);

	//ダメージ通知
	owner->SetDamageFlg(false);
}

//実行処理
ActionBase::State DamageAction::Run()
{
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//行動続行
		return ActionBase::State::RUN;
	}

	//行動に移行
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
