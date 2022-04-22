#include "Mathf.h"
#include <stdlib.h>
#include	<time.h>
//üŒ`•âŠ®
float Mathf::Lerp(float a, float b, float t)
{
	return a * (1.0f - t) + (b * t);
}

float Mathf::RandomRange(float min, float max)
{
	const float num = 100;//Š„‚èØ‚ç‚¹‚é”š

	float Max = max * num;
	float Min = min * num;
	float dis = abs(Max) + abs(Min);
	float Rnd = rand() % static_cast<int>(dis);
	Rnd /= num;//®”/®”‚µ‚Ä

	return Rnd + min;

}
//³‹K‰» Vec3
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