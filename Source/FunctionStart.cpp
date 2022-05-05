#include "ObjectFunctionDerive.h"
#include "Player.h"
#include "Scene.h"
//初期化処理
void FunctionStart::Init()
{
	//現在の状態：関数オブジェクトに入っていない
	isFunction = IsFunction::IS_FALSE;

	SetState(ObjectFunctionState::STATE_NONE);

	sceneGame->GetPlayer()->SetPos(GetPos());
}

//更新処理
void FunctionStart::Update()
{

}

//判定
void FunctionStart::Judge()
{
	//範囲内にいるなら
	if (IsCircle(sceneGame->GetPlayer()->GetPos()))
	{
		isFunction = IsFunction::IS_TRUE;
	}
	else isFunction = IsFunction::IS_FALSE;
}

//開始処理
void FunctionStart::Start()
{

}

//更新処理
void FunctionStart::Run()
{

}

//終了処理
void FunctionStart::End()
{
	
}