#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//開始処理
void BossEntry::Start()
{
	//ボスの登場モーションの取得
	const int BossEntryAnimetion=owner->GetAnime()->GetIndex(owner->GetAnime()->BossOpen);
	//ボスの登場アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossEntryAnimetion, false);
	//サウンド
	TK_Lib::Lib_Sound::SoundPlay("BossEntry", false);
}

//実行処理
ActionBase::State BossEntry::Run()
{
	//攻撃モーション中なら
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//アニメーション
		const float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());
		//ボスの登場サウンド開始
		const float BossTranceformStart = 0.42f;
		//ボスの登場サウンド終了
		const float BossTranceformEnd = 0.43f;

		//ボスの登場サウンド（球体からロボットに変身する）
		if (AnimetionRate >= BossTranceformStart && AnimetionRate <= BossTranceformEnd)
		{
			//ボスサウンドの再生
			TK_Lib::Lib_Sound::SoundPlay("BossTranceform", false);	
		}
		return ActionBase::State::RUN;
	}
	return ActionBase::State::COMPLETE;
}

//終了処理
void BossEntry::End()
{

}

//デバッグ用
void BossEntry::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("BossEntry");
	ImGui::End();
}
