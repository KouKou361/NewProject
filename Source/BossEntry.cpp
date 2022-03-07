#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"
#include "EnemyDerived.h"

//開始処理
void BossEntry::Start()
{
	//アニメーションの再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), owner->anime->GetIndex(owner->anime->BossOpen), false);
	TK_Lib::Lib_Sound::SoundPlay("BossEntry", false);
}

//実行処理
ActionBase::State BossEntry::Run()
{
	//攻撃モーション中
	if (TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//サウンド
		float AnimetionRate = TK_Lib::Model::IsPlayAnimetionRate(owner->GetModel());

		if (AnimetionRate >= 0.42f)
		{
			if (AnimetionRate <= 0.43f)
			{
				TK_Lib::Lib_Sound::SoundPlay("BossTranceform", false);
			}
		}

		return ActionBase::State::Run;

	}
	return ActionBase::State::Complete;
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
