#pragma once
#include "Lib.h"
class Mathf
{
public:
	//���`�⊮
	static float Lerp(float a, float b, float t);
	//�w��͈͂̃����_���l���v�Z����
	static float RandomRange(float min, float max);
	//���K�� Vec3
	static VECTOR3 Vec3Normalize(const VECTOR3 &Vec);
};
