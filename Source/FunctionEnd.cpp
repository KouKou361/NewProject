#include "ObjectFunctionDerive.h"
#include "Player.h"
#include "ObjectFunctionManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "EffectDerived.h"
#include "EffectManager.h"
//初期化処理
void FunctionEnd::Init()
{
	//現在の状態：関数オブジェクトに入っていない
	isFunction = IsFunction::IS_FALSE;

	//当たり判定の大きさ
	radius = 20.0f;

	//現在の状態：なし
	SetState(ObjectFunctionState::STATE_NONE);

	//スポットライトの生成
	spotLightHandle=TK_Lib::SpotLight::Create(GetPos(), { 1,1,0,1 }, 0.0f);
	
}

//更新処理
void FunctionEnd::Update()
{
	//ゲームのクリア条件を達しているかどうか？
	if (sceneGame->GetStageManager()->GetClearJudge())
	{
		//スポットライトの色
		const VECTOR4 SpotLightRedColor = { 1,1,0,1 };
		//スポットライトの大きさ
		const float SpotLightRange = 80;
		TK_Lib::SpotLight::Set(spotLightHandle,GetPos(), SpotLightRedColor, SpotLightRange);

		//ゲームクリアエフェクト
		const int EffectNum = 2;
		sceneGame->GetEffectManager()->GetEffectFromSerchKey("StageClear")->Play(GetPos(), EffectNum);
	}

}

//判定
void FunctionEnd::Judge()
{
	//範囲内にいるなら
	if (IsCircle(sceneGame->GetPlayer()->GetPos()))
	{
		//現在の状態：現在入っている
		isFunction = IsFunction::IS_TRUE;
	}
	//現在の状態：なし
	else isFunction = IsFunction::IS_FALSE;
}

//開始処理
void FunctionEnd::Start()
{

	//if (sceneGame->GetStageManager()->GetClearJudge())
	{
		//フェードインの強さ
		const float FadeInVolume = 0.02f;
		TK_Lib::Lib_Fade::FadeInBegin(FadeInVolume);
	}

}

//更新処理
void FunctionEnd::Run()
{
	//フェードイン完了したかどうか？
	if (TK_Lib::Lib_Fade::GetFadeVolume()>=1.0f)
	{
		//次のステージへ移行
		sceneGame->GetObjectFunctionManager()->GetSceneGama()->GetStageManager()->GoNextStage();
	}
}

//終了処理
void FunctionEnd::End()
{
	//フェードインの強さ
	const float FadeOutVolume = 0.02f;
	TK_Lib::Lib_Fade::FadeOutBegin(FadeOutVolume);
}