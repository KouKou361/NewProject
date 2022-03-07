#include "ObjectFunctionDerive.h"
#include "Player.h"
#include "ObjectFunctionManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "EffectDerived.h"
#include "EffectManager.h"
//����������
void FunctionEnd::Init()
{
	isFunction = IsFunction::IS_FALSE;
	radius = 20.0f;
	SetState(ObjectFunctionState::State_None);
	SpotLightHandle=TK_Lib::SpotLight::Create(GetPos(), { 1,1,0,1 }, 0.0f);
	
}

//�X�V����
void FunctionEnd::Update()
{
	if (sceneGame->GetStageManager()->GetClearJudge())
	{
		TK_Lib::SpotLight::Set(SpotLightHandle,GetPos(), { 1,1,0,1 },80);
		sceneGame->GetEffectManager()->GetEffectFromSerchKey("StageClear")->Play(GetPos(), 2);
	}

}

//����
void FunctionEnd::Judge()
{
	//�͈͓��ɂ���Ȃ�
	if (IsCircle(sceneGame->GetPlayer()->GetPos()))
	{
		isFunction = IsFunction::IS_TRUE;
	}
	else isFunction = IsFunction::IS_FALSE;
}

//�J�n����
void FunctionEnd::Start()
{

//	if (sceneGame->GetStageManager()->GetClearJudge())
	{
		TK_Lib::Lib_Fade::FadeInBegin(0.02f);
	}

}

//�X�V����
void FunctionEnd::Run()
{
	if (TK_Lib::Lib_Fade::GetFadeVolume()>=1.0f)
	{
		//���̃X�e�[�W�ֈڍs
		sceneGame->GetObjectFunctionManager()->GetSceneGama()->GetStageManager()->GoNextStage();
	}
}

//�I������
void FunctionEnd::End()
{
	TK_Lib::Lib_Fade::FadeOutBegin(0.02f);
}