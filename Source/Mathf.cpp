#include "Mathf.h"
#include <stdlib.h>
#include	<time.h>
//���`�⊮
float Mathf::Lerp(float a, float b, float t)
{
	return a * (1.0f - t) + (b * t);
}

float Mathf::RandomRange(float min, float max)
{
	//�������������Ȃ烊�^�[��
	if (min - max == 0)return min;

	const float num = 1000;//����؂点�鐔��

	float Max = max * num;
	float Min = min * num;
	int dis = static_cast<int>(abs(Max)) + static_cast<int>(abs(Min));
	float Rnd = static_cast<float>(rand() % static_cast<int>(dis));
	Rnd /= num;//����/��������

	return Rnd + min;

}
//���K�� Vec3
VECTOR3 Mathf::Vec3Normalize(const VECTOR3& Vec)
{
	//return{ 0,0,0 };
	XMVECTOR VEC;
	VEC=DirectX::XMLoadFloat3(&Vec);
	VEC = DirectX::XMVector3Normalize(VEC);
	VECTOR3 vec;
	DirectX::XMStoreFloat3(&vec,VEC);
	return vec;
}