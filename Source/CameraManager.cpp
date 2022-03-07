#include "CameraController.h"
#include "EnemyManager.h"
void CameraManager::Init(Actor* owner)
{
	ChangeCamera(new CameraNormal(owner));
}
void CameraManager::Update()
{
	//if (!currentCamera->LerpCameraUpdate()) {
	//	return;
	//}
	currentCamera->Update();
}
void CameraManager::End()
{
	currentCamera->End();
}
void CameraManager::ChangeCamera(Camera* newScene, const VECTOR3 cameraPos)
{
	if (currentCamera != nullptr)
	{
		End();
	}
	currentCamera.reset(newScene);

	currentCamera->targetPos = cameraPos;
	currentCamera->startTargetPos = cameraPos;
	currentCamera->angle = {0,0,0};
	currentCamera->startEyePos = cameraPos;
	currentCamera->manager = this;
	currentCamera->Init();
}
void CameraManager::ChangeCamera(Camera* newScene)
{
	VECTOR3 oldPos = { 0,0,0 };
	VECTOR3 oldTarget = { 0,0,0 };
	VECTOR3 oldAngle = { 0,0,0 };
	if (currentCamera != nullptr)
	{
		oldPos = currentCamera->eye;
		oldTarget = currentCamera->targetPos;
		oldAngle = currentCamera->angle;
		//
		{
			VECTOR3 Vec= oldTarget-oldPos;
			oldAngle.x=atan2f(Vec.x, Vec.z);
		}
		End();
	}

	currentCamera.reset(newScene);

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
