#include "ObjectFunctionDerive.h"
#include "Player.h"
#include "Scene.h"
//初期化処理
void FunctionStart::Init()
{
	isFunction = IsFunction::IS_FALSE;
	SetState(ObjectFunctionState::State_None);
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
	int test=0;

}

//更新処理
void FunctionStart::Run()
{
	int test = 0;
}

//終了処理
void FunctionStart::End()
{
	int test = 0;
}