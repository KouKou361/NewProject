#include "CameraController.h"
#include "EnemyManager.h"
//初期化
void CameraManager::Init(Actor* owner)
{
	ChangeCamera(new CameraNormal(owner));
}
//更新処理
void CameraManager::Update()
{
	currentCamera->Update();
}
//カメラが切り替わった時の後始末処理
void CameraManager::End()
{
	currentCamera->End();
}
//デバッグ
void CameraManager::ChangeCamera(Camera* newScene, const VECTOR3 cameraPos)
{
	if (currentCamera != nullptr)
	{
		End();
	}
	//カメラ切り替え
	currentCamera.reset(newScene);
	
	
	{
		currentCamera->targetPos = cameraPos;
		currentCamera->startTargetPos = cameraPos;
		currentCamera->startEyePos = cameraPos;
	}
	//初期化
	currentCamera->angle = { 0,0,0 };
	currentCamera->manager = this;
	currentCamera->Init();
}
void CameraManager::ChangeCamera(Camera* newScene)
{
	//前のカメラステータスを引き継ぐため用
	VECTOR3 oldPos = { 0,0,0 };
	VECTOR3 oldTarget = { 0,0,0 };
	VECTOR3 oldAngle = { 0,0,0 };

	if (currentCamera != nullptr)
	{
		//保存
		oldPos = currentCamera->eye;
		oldTarget = currentCamera->targetPos;
		oldAngle = currentCamera->angle;

		//カメラが切り替わった時、切り替わる前のカメラ方向Xを取得しておく
		//そうでもしないとカメラの切り替わえ時に変な方向に向くため
		{
			VECTOR3 Vec= oldTarget-oldPos;
			oldAngle.x=atan2f(Vec.x, Vec.z);
		}
		End();//後始末処理
	}

	currentCamera.reset(newScene);

	//初期化
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

//振動
void CameraManager::SetVibration(const float volume, const float time)
{
	currentCamera->SetVibration(volume, time);
}
