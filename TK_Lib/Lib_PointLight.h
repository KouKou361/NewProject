#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include "Lib_ShaderResource.h"

#include "Vector.h"

using namespace DirectX;
using namespace std;
using namespace Microsoft::WRL;
struct Lib_pointLight
{
	float index = -1;//�ԍ�
	float range;//���̓͂��͈�
	float dummy;
	float dummy2;
	VECTOR4 pos;
	VECTOR4 color;
};

class Lib_PointLight
{
	float index=-1;//�ԍ�
	float range = 0.0f;//���̓͂��͈�
	float dummy=0.0f;
	float dummy2 = 0.0f;
	VECTOR4 pos = { 0,0,0,0 };
	VECTOR4 color = { 0,0,0,0 };
public:
	void SetIndex(const int index);
	int GetIndex();
	//�f�[�^�����ɖ߂�
	void Clear();
	//�ʒu�̎擾
	VECTOR4 GetPos();
	//�f�[�^�̐ݒ�
	void Set(VECTOR4 pos, VECTOR4 color,float range);
};

