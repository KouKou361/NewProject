#include "CameraController.h"
#include "Charactor.h"
#include "Collision.h"


CameraNormal::CameraNormal(Actor* owner) {
	this->owner = owner;

}
//初期化処理
void CameraNormal::Init()
{
	manager->cameraType = CameraManager::CameraType::TypeNormal;
	//	Angle.x = DirectX::XMConvertToRadians(10);
	angle.y = DirectX::XMConvertToRadians(10);
	//angle.z = DirectX::XMConvertToRadians(10);

	endTargetPos = owner->GetPos();

	LerpEyeCamera(0.001f);
}
//視点位置を決める更新
void CameraNormal::UpdateEye()
{

	//カメラとonwerとの距離
	constexpr float L = 100.0f;
	//カメラの最大Y軸
	constexpr float MaxAngleY = 0.5f;
	
	
	float ax = TK_Lib::Gamepad::GetAxisRX()  * DirectX::XMConvertToRadians(2);
	float ay = TK_Lib::Gamepad::GetAxisRY()  * DirectX::XMConvertToRadians(2);
	float az = 0.0f;
	
	angle.x += ax;
	angle.y -= ay;//入力とは逆の方向にしている
	angle.z += az;
	
	if (angle.y >= MaxAngleY) angle.y = MaxAngleY;
	if (angle.y <= -MaxAngleY)angle.y = -MaxAngleY;
	
	
	
	
	//回転行列に変換する
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);
	
	//前方ベクトルの算出
	DirectX::XMVECTOR Front = Transform.r[2];
	//
	VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);

	////
	////
	////
	////endEyePos = { 0, 10, 0 };
	//
	////プレイヤーの位置（XZ平面）
	//VECTOR3 plPos;
	//{
	//	plPos = owner->GetPos();
	//	plPos.y = 0;
	//}
	//
	////カメラの位置（XZ平面）
	//VECTOR3 CameraPos;
	//{
	//	CameraPos = endEyePos;
	//	CameraPos.y = 0;
	//}
	//
	//XMVECTOR Vec=XMVectorSet(0,0,0,0);
	//{
	//VECTOR3 v = plPos - CameraPos;
	//v.y = 0;
	//XMVECTOR V = XMLoadFloat3(&v);
	//V = XMVector3Normalize(V);
	//Vec=XMVectorScale(V, L);
	//}
	//
	//XMVECTOR pos;
	//{
	//	VECTOR3 Pos = owner->GetPos();
	//	pos=XMLoadFloat3(&Pos);
	//}
	//
	//
	//pos =XMVectorAdd(-Vec,pos);
	//XMStoreFloat3(&endEyePos, pos);
	////
	//endEyePos.y = owner->GetPos().y - front.y * L;
	//

	endEyePos.x = owner->GetPos().x - front.x * L;
	endEyePos.y = owner->GetPos().y - front.y * L;
	endEyePos.z = owner->GetPos().z - front.z * L;

	LerpEyeCamera(0.2f);
}
//注視点を決める更新
void CameraNormal::UpdateTarget()
{
	targetPos = owner->GetPos();
	endTargetPos = targetPos;
	LerpTargetCamera(0.2f);
	//SetTarget(owner->pos);
	//LerpTargetCamera(0.05f);
}

//更新処理
void CameraNormal::Update()
{
	//視点位置を決める更新
	UpdateEye();
	//注視点を決める更新
	UpdateTarget();

	//地面とレイピック
	//RayPick();

	//カメラの設定
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });
}
//終了処理
void CameraNormal::End()
{

}
//Imgui
void CameraNormal::Imgui()
{
	ImGui::Begin(u8"ゲーム");
	ImGui::Text("CameraNormal");
	ImGui::Text("Angle.x.y.z=%f,%f,%f", angle.x, angle.y, angle.z);
	ImGui::Text("eye.x.y.z=%f,%f,%f", eye.x, eye.y, eye.z);
	ImGui::Text("Target.x.y.z=%f,%f,%f", targetPos.x, targetPos.y, targetPos.z);
	ImGui::End();
}

