#include "CameraController.h"
#include "EnemyManager.h"
//������
void CameraManager::Init(Actor* owner)
{
	ChangeCamera(new CameraNormal(owner));
}
//�X�V����
void CameraManager::Update()
{
	currentCamera->Update();
}
//�J�������؂�ւ�������̌�n������
void CameraManager::End()
{
	currentCamera->End();
}
//�f�o�b�O
void CameraManager::ChangeCamera(Camera* newScene, const VECTOR3 cameraPos)
{
	if (currentCamera != nullptr)
	{
		End();
	}
	//�J�����؂�ւ�
	currentCamera.reset(newScene);
	
	
	{
		currentCamera->targetPos = cameraPos;
		currentCamera->startTargetPos = cameraPos;
		currentCamera->startEyePos = cameraPos;
	}
	//������
	currentCamera->angle = { 0,0,0 };
	currentCamera->manager = this;
	currentCamera->Init();
}
void CameraManager::ChangeCamera(Camera* newScene)
{
	//�O�̃J�����X�e�[�^�X�������p�����ߗp
	VECTOR3 oldPos = { 0,0,0 };
	VECTOR3 oldTarget = { 0,0,0 };
	VECTOR3 oldAngle = { 0,0,0 };

	if (currentCamera != nullptr)
	{
		//�ۑ�
		oldPos = currentCamera->eye;
		oldTarget = currentCamera->targetPos;
		oldAngle = currentCamera->angle;

		//�J�������؂�ւ�������A�؂�ւ��O�̃J��������X���擾���Ă���
		//�����ł����Ȃ��ƃJ�����̐؂�ւ킦���ɕςȕ����Ɍ�������
		{
			VECTOR3 Vec= oldTarget-oldPos;
			oldAngle.x=atan2f(Vec.x, Vec.z);
		}
		End();//��n������
	}

	currentCamera.reset(newScene);

	//������
	currentCamera->startTargetPos = oldTarget;
	currentCamera->angle = oldAngle;
	currentCamera->startEyePos = oldPos;

	currentCamera->manager = this;
	currentCamera->Init();
}
void CameraManager::Imgui()
{
	currentCamera->Imgui();
}

//�U��
void CameraManager::SetVibration(const float volume, const float time)
{
	currentCamera->SetVibration(volume, time);
}
