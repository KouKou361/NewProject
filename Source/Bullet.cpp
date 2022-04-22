#include "Bullet.h"
//放物線を投げる時の縦の大きさ(初速度)
float Bullet::GetParabolaHieght(const float time)
{
	float f= (0.5f * Gravity)* time* time;
	return f;
}

//ある点からある点までの長さ
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
//ある点からある点までにつく時間
float Bullet::GetTime(const VECTOR3 posA, const VECTOR3 posB, const float speed)
{
	float L = GetLength(posA, posB);
	return L / speed;
}
//ある点からある点までにつく速度
float Bullet::GetSpeed(const VECTOR3 posA, const VECTOR3 posB, const float time)
{
	float L = GetLength(posA, posB);
	return L / time;
}
