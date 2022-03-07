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
	isFunction = IsFunction::IS_FALSE;
	radius = 20.0f;
	SetState(ObjectFunctionState::State_None);
	SpotLightHandle=TK_Lib::SpotLight::Create(GetPos(), { 1,1,0,1 }, 0.0f);
	
}

//更新処理
void FunctionEnd::Update()
{
	if (sceneGame->GetStageManager()->GetClearJudge())
	{
		TK_Lib::SpotLight::Set(SpotLightHandle,GetPos(), { 1,1,0,1 },80);
		sceneGame->GetEffectManager()->GetEffectFromSerchKey("StageClear")->Play(GetPos(), 2);
	}

}

//判定
void FunctionEnd::Judge()
{
	//範囲内にいるなら
	if (IsCircle(sceneGame->GetPlayer()->GetPos()))
	{
		isFunction = IsFunction::IS_TRUE;
	}
	else isFunction = IsFunction::IS_FALSE;
}

//開始処理
void FunctionEnd::Start()
{

//	if (sceneGame->GetStageManager()->GetClearJudge())
	{
		TK_Lib::Lib_Fade::FadeInBegin(0.02f);
	}

}

//更新処理
void FunctionEnd::Run()
{
	if (TK_Lib::Lib_Fade::GetFadeVolume()>=1.0f)
	{
		//次のステージへ移行
		sceneGame->GetObjectFunctionManager()->GetSceneGama()->GetStageManager()->GoNextStage();
	}
}

//終了処理
void FunctionEnd::End()
{
	TK_Lib::Lib_Fade::FadeOutBegin(0.02f);
}