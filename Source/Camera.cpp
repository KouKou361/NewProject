#include "CameraController.h"
#include "Lib.h"
//�J�����̒����_�ړ�(�⊮)
bool Camera::LerpTargetCamera(const float time)
{
	
	//minL�����������ꍇ����⊮���Ȃ�
	const float minL = 1.0f;

	VECTOR3 outpos;
	//����⊮�̎Z�o
	if (LerpCamera(outpos, startTargetPos, endTargetPos, minL, time))
	{
		SetTarget(outpos);
		startTargetPos = targetPos;
		return false;
	}

	return true;
}
//�J�����̎��_�ړ�(�⊮)
bool Camera::LerpEyeCamera(const float time)
{

	//minL�����������ꍇ����⊮���Ȃ�
	const float minL = 1.0f;

	VECTOR3 outpos;
	//����⊮�̎Z�o
	if (LerpCamera(outpos, startEyePos, endEyePos, minL, time))
	{
		eye = outpos;
		startEyePos = eye;
		return false;
	}
	return true;


}
//�������擾
float Camera::GetLength(VECTOR3 startPos, VECTOR3 endPos)
{
	//endTargetPos�܂ł̒���
	float l;
	VECTOR3 v = startPos - endPos;
	XMVECTOR Vec = XMLoadFloat3(&v);
	Vec = XMVector3Length(Vec);
	XMStoreFloat(&l, Vec);
	return l;
}
bool Camera::LerpCamera(VECTOR3& outpos, const VECTOR3 startPos, const VECTOR3& endPos, const float& minL, const float& time)
{
	//min�����������ꍇ����⊮���Ȃ�
	float l = GetLength(startPos, endPos);
	if (minL >= l)	return false;

	//����⊮
	outpos.x = Mathf::Lerp(startPos.x, endPos.x, time);
	outpos.y = Mathf::Lerp(startPos.y, endPos.y, time);
	outpos.z = Mathf::Lerp(startPos.z, endPos.z, time);
	
	return true;
}

//�U��
void Camera::SetVibration(const float volume, const float time)
{
	vibrationTime = time;
	vibrationVolume = volume;
}
//�U���X�V����
void Camera::VibrationUpdate()
{
	if (vibrationTime <= 0)return;

	vibrationTime -= TK_Lib::Window::GetElapsedTime();
	targetPos.x += Mathf::RandomRange(-vibrationVolume,vibrationVolume);
	targetPos.y += Mathf::RandomRange(-vibrationVolume, vibrationVolume);
	targetPos.z += Mathf::RandomRange(-vibrationVolume, vibrationVolume);

}