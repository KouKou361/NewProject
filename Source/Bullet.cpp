#include "Bullet.h"
//�������𓊂��鎞�̏c�̑傫��(�����x)
float Bullet::GetParabolaHieght(const float time)
{
	float f= (0.5f * Gravity)* time* time;
	return f;
}

//����_���炠��_�܂ł̒���
float Bullet::GetLength(const VECTOR3 posA, const VECTOR3 posB)
{
	XMVECTOR Start, End, V;
	float L;

	Start = XMLoadFloat3(&posA);
	End = XMLoadFloat3(&posB);
	V = XMVectorSubtract(End, Start);

	V = XMVector3Length(V);
	XMStoreFloat(&L, V);
	return L;
}
//����_���炠��_�܂łɂ�����
float Bullet::GetTime(const VECTOR3 posA, const VECTOR3 posB, const float speed)
{
	float L = GetLength(posA, posB);
	return L / speed;
}
//����_���炠��_�܂łɂ����x
float Bullet::GetSpeed(const VECTOR3 posA, const VECTOR3 posB, const float time)
{
	float L = GetLength(posA, posB);
	return L / time;
}
