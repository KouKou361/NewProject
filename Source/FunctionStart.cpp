#include "ObjectFunctionDerive.h"
#include "Player.h"
#include "Scene.h"
//����������
void FunctionStart::Init()
{
	//���݂̏�ԁF�֐��I�u�W�F�N�g�ɓ����Ă��Ȃ�
	isFunction = IsFunction::IS_FALSE;

	SetState(ObjectFunctionState::STATE_NONE);

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

}

//�X�V����
void FunctionStart::Run()
{

}

//�I������
void FunctionStart::End()
{
	
}