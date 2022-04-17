#include "CameraController.h"
#include "Charactor.h"
#include "EnemyManager.h"

CameraAim::CameraAim(Actor* owner, Actor* targetChara, EnemyManager* enemyManager) {
this->targetChara = targetChara;
this->owner = owner;
this->enemyManager = enemyManager;

};
//初期化処理
void CameraAim::Init()
{
	keyTimer = 0;
	angle.y = DirectX::XMConvertToRadians(10);
	manager->cameraType = CameraManager::CameraType::TYPE_AIM;

	endTargetPos = targetChara->GetPos();
}
//視点位置を決める更新
void CameraAim::UpdateEye()
{


	//カメラとonwerとの距離
	constexpr float L = 45.0f;

	VECTOR3 vec = targetChara->GetPos() - owner->GetPos();
	vec.y = 0;
	XMVECTOR V = XMLoadFloat3(&vec);
	XMVECTOR NV = XMVector3Normalize(V);
	VECTOR3 OwnerPos = owner->GetPos();
	XMVECTOR P = XMLoadFloat3(&OwnerPos);
	V = XMVectorScale(NV, -L);
	V = XMVectorAdd(V, P);
	XMStoreFloat3(&endEyePos, V);
	endEyePos.y = targetChara->GetPos().y+10.0f;

	LerpEyeCamera(0.05f);
}
//注視点を決める更新
void CameraAim::UpdateTarget()
{
	endTargetPos = targetChara->GetPos();
	LerpTargetCamera(0.05f);
}
//更新処理
void CameraAim::Update()
{
	//視点位置を決める更新
	UpdateEye();
	//注視点を決める更新
	UpdateTarget();

	//地面とレイピック
	RayPick();

	//カメラの設定
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });




	//float ax = TK_Lib::Gamepad::GetAxisRX();
	//if (fabsf(ax)>=0.3f)
	//{
	//	ChangeTargetChara();
	//}
	//もしR2が押されていない時
	//if (TK_Lib::Gamepad::GetButtonDown(BTN::X) <= 0)
	if (TK_Lib::Gamepad::GetButtonDown(BTN::LT) <= 0)
	{
		manager->ChangeCamera(new CameraNormal(owner));
	}

	if (targetChara == nullptr)
	{
		manager->ChangeCamera(new CameraNormal());
	}

	
	
}
//目標の切り替え
void CameraAim::ChangeTargetChara()
{
	if (keyTimer > 0)return;
	float ax = TK_Lib::Gamepad::GetAxisRX();

	float nearDot = FLT_MAX;

	VECTOR3  vec1 = TK_Lib::Camera::GetFront();
	vec1.y = 0;
	XMVECTOR Vec1 = XMLoadFloat3(&vec1);
	XMVECTOR NVec1 = XMVector3Normalize(Vec1);

	constexpr float ViewAngle = 30;
	for (int i = 0; i < enemyManager->GetEnemiesSize(); i++)
	{
		EnemyBase* enm = enemyManager->GetEnemiesIndex(i);
		//最短距離までの長さ
				//視野角内かどうか
		float dot = 0;
		{
			VECTOR3  vec2 = enm->GetPos() - TK_Lib::Camera::GetPos();
			vec2.y = 0;
			XMVECTOR Vec2 = XMLoadFloat3(&vec2);
			XMVECTOR Nvec2 = XMVector3Normalize(Vec2);
			XMVECTOR Dot = XMVector3Dot(NVec1, Nvec2);
			XMStoreFloat(&dot, Dot);
			dot = acosf(dot);
		}
		if (enm == targetChara)continue;
		//ターゲット視野角に入ってないならcontinue
		//if (XMConvertToDegrees(dot) >= ViewAngle)
		//{
		//	continue;
		//}
		if (dot >= nearDot)
		{
			continue;
		}


		VECTOR3 cross;
		{
			VECTOR3 vec2 = enm->GetPos() - owner->GetPos();
			XMVECTOR Vec2 = XMLoadFloat3(&vec2);
			XMVECTOR Cross = XMVector3Cross(Vec1, Vec2);

			XMStoreFloat3(&cross, Cross);
		}
		//右なら
		if (cross.y >= 0 && ax >= 0.3f)
		{
			targetChara = enm;
			nearDot = dot;
		}
		//左なら
		if (cross.y <= 0 && ax <= -0.3f)
		{
			targetChara = enm;
			nearDot = dot;
		}

	}


}
//終了処理
void CameraAim::End()
{

}
//Imgui
void CameraAim::Imgui()
{
	ImGui::Begin(u8"ゲーム");
	ImGui::Text("CameraAim");
	ImGui::Text("Angle.x.y.z=%f", angle.x, angle.y, angle.z);
	ImGui::Text("eye.x.y.z=%f", eye.x, eye.y, eye.z);
	ImGui::Text("Target.x.y.z=%f", targetPos.x, targetPos.y, targetPos.z);
	ImGui::End();
}

