#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//開始処理
void DeadAction::Start()
{

	//ボスの回転攻撃終了モーションの取得
	const int BossDamageAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->Die);

	//アニメーションの死亡モーション再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), BossDamageAnimetion, false);

	owner->SetDeadFlg(false);


	//目標にされなくする。
	owner->TargetFaild();
	//死亡時間の設定
	const float DeathTime = 1.0f;
	owner->SetDeathTime(DeathTime);
}

//実行処理
ActionBase::State DeadAction::Run()
{

	//もし死亡アニメーションが終了したなら
	if (!TK_Lib::Model::IsPlayAnimetion(owner->GetModel()))
	{
		//死亡時間の更新
		if (owner->UpdateDeathTime())
		{
			const float MaskSpeed = 1.5f;
			owner->MaskStart(MaskSpeed);
		
		}
	}

	if (owner->GetMaskVolume() >= 1.0f)
	{
		//死亡時間になったら
		owner->Destroy();
		return ActionBase::State::FAILED;
	}

	//次の行動に移行
	return ActionBase::State::RUN;
}

//終了処理
void DeadAction::End()
{

}

//デバッグ用
void DeadAction::DebugImgui()
{
	ImGui::Begin("Action");
	ImGui::Text("Dead");
	ImGui::End();
}
