#pragma once
#include "Lib.h"
//物理専用のクラス
class Bullet
{
private:
	static constexpr float gravity = 0.2f;
public:
	//放物線を投げる時の縦の大きさ
	static float GetParabolaHieght(const float time);
	//ある点からある点までの長さ
	static float GetLength(const VECTOR3 posA, const VECTOR3 posB);
	//ある点からある点までにつく時間
	static float GetTime(const VECTOR3 posA, const VECTOR3 posB,const float speed);
	//ある点からある点までにつく速度
	static float GetSpeed(const VECTOR3 posA, const VECTOR3 posB, const float time);
	//重力を受ける
	static float GetGravity(){ return gravity; }

};
