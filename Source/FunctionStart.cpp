#include "ObjectFunctionDerive.h"
#include "Player.h"
#include "Scene.h"
//����������
void FunctionStart::Init()
{
	isFunction = IsFunction::IS_FALSE;
	SetState(ObjectFunctionState::State_None);
	sceneGame->GetPlayer()->SetPos(GetPos());
}

//�X�V����
void FunctionStart::Update()
{

}

//����
void FunctionStart::Judge()
{
	//�͈͓��ɂ���Ȃ�
	if (IsCircle(sceneGame->GetPlayer()->GetPos()))
	{
		isFunction = IsFunction::IS_TRUE;
	}
	else isFunction = IsFunction::IS_FALSE;
}

//�J�n����
void FunctionStart::Start()
{
	int test=0;

}

//�X�V����
void FunctionStart::Run()
{
	int test = 0;
}

//�I������
void FunctionStart::End()
{
	int test = 0;
}