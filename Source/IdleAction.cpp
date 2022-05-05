#include "ActionDerived.h"
#include "EnemyBase.h"
#include "Lib.h"
#include "Animetion.h"

class EnemyBase;

//開始処理
void IdleAction::Start()
{
	//待機モーションの取得
	const int IdeiAnimetion = owner->GetAnime()->GetIndex(owner->GetAnime()->Idle);
	//アニメーションの待機モーション再生
	TK_Lib::Model::PlayAnimation(owner->GetModel(), IdeiAnimetion, true);
}

//実行処理
ActionBase::State IdleAction::Run()
{

	//索敵内にいればtrueを返す
	if (owner->SearchTarget(owner->GetSearchL()))
	{
		//行動終了！次の行動に移行
		return ActionBase::State::FAILED;
	}
	//行動の続行
	return ActionBase::State::RUN;
}

//終了処理
void IdleAction::End()
{

}

//Imguiデバッグ
void IdleAction::DebugImgui()
{
	//TK_Lib::Debug3D::Circle(owner->pos, owner->GetSearchL(), { 0,1,0,1 });

	ImGui::Begin("Action");
	ImGui::Text("Idle");
	ImGui::End();
}