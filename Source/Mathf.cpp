#include "Mathf.h"
#include <stdlib.h>
#include	<time.h>
//線形補完
float Mathf::Lerp(float a, float b, float t)
{
	return a * (1.0f - t) + (b * t);
}

float Mathf::RandomRange(float min, float max)
{
	//もし同じ数字ならリターン
	if (min - max == 0)return min;

	const float num = 1000;//割り切らせる数字

	float Max = max * num;
	float Min = min * num;
	int dis = static_cast<int>(abs(Max)) + static_cast<int>(abs(Min));
	float Rnd = static_cast<float>(rand() % static_cast<int>(dis));
	Rnd /= num;//整数/整数して

	return Rnd + min;

}
//正規化 Vec3
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