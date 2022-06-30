#include "CameraController.h"
#include "Lib.h"
//カメラの注視点移動(補完)
bool Camera::LerpTargetCamera(const float time)
{
	
	//minLよりも小さい場合線上補完しない
	const float minL = 1.0f;

	VECTOR3 outpos;
	//線上補完の算出
	if (LerpCamera(outpos, startTargetPos, endTargetPos, minL, time))
	{
		SetTarget(outpos);
		startTargetPos = targetPos;
		return false;
	}

	return true;
}
//カメラの視点移動(補完)
bool Camera::LerpEyeCamera(const float time)
{

	//minLよりも小さい場合線上補完しない
	const float minL = 1.0f;

	VECTOR3 outpos;
	//線上補完の算出
	if (LerpCamera(outpos, startEyePos, endEyePos, minL, time))
	{
		eye = outpos;
		startEyePos = eye;
		return false;
	}
	return true;


}
//長さを取得
float Camera::GetLength(VECTOR3 startPos, VECTOR3 endPos)
{
	//endTargetPosまでの長さ
	float l;
	VECTOR3 v = startPos - endPos;
	XMVECTOR Vec = XMLoadFloat3(&v);
	Vec = XMVector3Length(Vec);
	XMStoreFloat(&l, Vec);
	return l;
}
bool Camera::LerpCamera(VECTOR3& outpos, const VECTOR3 startPos, const VECTOR3& endPos, const float& minL, const float& time)
{
	//minよりも小さい場合線上補完しない
	float l = GetLength(startPos, endPos);
	if (minL >= l)	return false;

	//線上補完
	outpos.x = Mathf::Lerp(startPos.x, endPos.x, time);
	outpos.y = Mathf::Lerp(startPos.y, endPos.y, time);
	outpos.z = Mathf::Lerp(startPos.z, endPos.z, time);
	
	return true;
}

//振動
void Camera::SetVibration(const float volume, const float time)
{
	vibrationTime = time;
	vibrationVolume = volume;
}
//振動更新処理
void Camera::VibrationUpdate()
{
	if (vibrationTime <= 0)return;

	vibrationTime -= TK_Lib::Window::GetElapsedTime();
	targetPos.x += Mathf::RandomRange(-vibrationVolume,vibrationVolume);
	targetPos.y += Mathf::RandomRange(-vibrationVolume, vibrationVolume);
	targetPos.z += Mathf::RandomRange(-vibrationVolume, vibrationVolume);

}