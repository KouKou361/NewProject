#pragma once
#include "Lib.h"
class Mathf
{
public:
	//線形補完
	static float Lerp(float a, float b, float t);
	//指定範囲のランダム値を計算する
	static float RandomRange(float min, float max);
	//正規化 Vec3
	static VECTOR3 Vec3Normalize(const VECTOR3 &Vec);
};
