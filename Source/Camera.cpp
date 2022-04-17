#include "CameraController.h"
#include "Lib.h"
#include "Collision.h"
//視点移動更新処理
bool Camera::LerpCameraUpdate()
{
	return LerpTargetCamera(lerpSpeed);
}
//視点移動
bool Camera::LerpTargetCamera(const float time)
{
	VECTOR3 v = endTargetPos - startTargetPos;
	XMVECTOR Vec=XMLoadFloat3(&v);
	Vec = XMVector3Length(Vec);
	float L;
	XMStoreFloat(&L, Vec);
	if (1>=L)
	{
		return true;
	}
	VECTOR3 Pos;
	Pos.x = Mathf::Lerp(startTargetPos.x, endTargetPos.x, time);
	Pos.y = Mathf::Lerp(startTargetPos.y, endTargetPos.y, time);
	Pos.z = Mathf::Lerp(startTargetPos.z, endTargetPos.z, time);
	SetTarget(Pos);

	startTargetPos = targetPos;
	return false;
}
//レイピック
void Camera::RayPick()
{
	VECTOR3 Start,End;
	Start = targetPos;
	End = eye;

	VECTOR3 v;
	v = { End - Start };
	XMVECTOR V= XMLoadFloat3(&v);
	XMVector3Normalize(V);
	XMStoreFloat3(&v,V);


	//RayOut ray;
	//Collision::Instance().RayPick(Start,Start+v,ray);
	////もし当たっているなら
	//if (ray.materialIndex >= 0)
	//{
	//	eye.x = ray.Pos.x;
	//	eye.z = ray.Pos.z;
	//}

}
//カメラの視点移動(補完)
bool Camera::LerpEyeCamera(const float time)
{
	VECTOR3 v = endEyePos - startEyePos;
	XMVECTOR Vec = XMLoadFloat3(&v);
	Vec = XMVector3Length(Vec);
	float L;
	XMStoreFloat(&L, Vec);
	if (1 >= L)
	{
		return true;
	}
	VECTOR3 Pos;
	Pos.x = Mathf::Lerp(startEyePos.x, endEyePos.x, time);
	Pos.y = Mathf::Lerp(startEyePos.y, endEyePos.y, time);
	Pos.z = Mathf::Lerp(startEyePos.z, endEyePos.z, time);
	eye = Pos;

	startEyePos = eye;
	return false;
}