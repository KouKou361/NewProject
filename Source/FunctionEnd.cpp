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
	//���݂̏�ԁF�֐��I�u�W�F�N�g�ɓ����Ă��Ȃ�
	isFunction = IsFunction::IS_FALSE;

	//�����蔻��̑傫��
	radius = 20.0f;

	//���݂̏�ԁF�Ȃ�
	SetState(ObjectFunctionState::STATE_NONE);

	//�X�|�b�g���C�g�̐���
	spotLightHandle=TK_Lib::SpotLight::Create(GetPos(), { 1,1,0,1 }, 0.0f);
	
}

//�X�V����
void FunctionEnd::Update()
{
	//�Q�[���̃N���A������B���Ă��邩�ǂ����H
	if (sceneGame->GetStageManager()->GetClearJudge())
	{
		//�X�|�b�g���C�g�̐F
		const VECTOR4 SpotLightRedColor = { 1,1,0,1 };
		//�X�|�b�g���C�g�̑傫��
		const float SpotLightRange = 80;
		TK_Lib::SpotLight::Set(spotLightHandle,GetPos(), SpotLightRedColor, SpotLightRange);

		//�Q�[���N���A�G�t�F�N�g
		const int EffectNum = 2;
		sceneGame->GetEffectManager()->GetEffectFromSerchKey("StageClear")->Play(GetPos(), EffectNum);
	}

}

//����
void FunctionEnd::Judge()
{
	//�͈͓��ɂ���Ȃ�
	if (IsCircle(sceneGame->GetPlayer()->GetPos()))
	{
		//���݂̏�ԁF���ݓ����Ă���
		isFunction = IsFunction::IS_TRUE;
	}
	//���݂̏�ԁF�Ȃ�
	else isFunction = IsFunction::IS_FALSE;
}

//�J�n����
void FunctionEnd::Start()
{

	//if (sceneGame->GetStageManager()->GetClearJudge())
	{
		//�t�F�[�h�C���̋���
		const float FadeInVolume = 0.02f;
		TK_Lib::Lib_Fade::FadeInBegin(FadeInVolume);
	}

}

//�X�V����
void FunctionEnd::Run()
{
	//�t�F�[�h�C�������������ǂ����H
	if (TK_Lib::Lib_Fade::GetFadeVolume()>=1.0f)
	{
		//���̃X�e�[�W�ֈڍs
		sceneGame->GetObjectFunctionManager()->GetSceneGama()->GetStageManager()->GoNextStage();
	}
}

//�I������
void FunctionEnd::End()
{
	//�t�F�[�h�C���̋���
	const float FadeOutVolume = 0.02f;
	TK_Lib::Lib_Fade::FadeOutBegin(FadeOutVolume);
}