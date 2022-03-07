#pragma once
#include "Lib.h"
//������p�̃N���X
class Bullet
{
private:
	static constexpr float gravity = 0.2f;
public:
	//�������𓊂��鎞�̏c�̑傫��
	static float GetParabolaHieght(const float time);
	//����_���炠��_�܂ł̒���
	static float GetLength(const VECTOR3 posA, const VECTOR3 posB);
	//����_���炠��_�܂łɂ�����
	static float GetTime(const VECTOR3 posA, const VECTOR3 posB,const float speed);
	//����_���炠��_�܂łɂ����x
	static float GetSpeed(const VECTOR3 posA, const VECTOR3 posB, const float time);
	//�d�͂��󂯂�
	static float GetGravity(){ return gravity; }

};
