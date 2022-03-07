#pragma once
#include "vector.h"
//���̂悤�ȃN���X���ɂ��Ă���̂��Ƃ�����
//���C�u�����[���g���Ă���\�[�X�ɓ������O�ɂȂ��Ă��܂��̂�h�����߂ł���

//�܂�����Ȗ��O�ɂ�����N���X�������Ԃ����肵�Ȃ����낤
class CameraLib
{
public:
	CameraLib() {}
	~CameraLib() {}
public:
	// �w�����������
	void SetLookAt(
		const VECTOR3& pos,
		const VECTOR3& Target,
		const VECTOR3& up);

	// �p�[�X�y�N�e�B�u�ݒ�
	void SetPerspectiveFov(float fovY, float aspect, float nearZ, float farZ);

	void SetOrthongraphic(float Width, float Height, float Near, float Far);


	const DirectX::XMFLOAT4X4& GetView() const { return view; }

	const DirectX::XMFLOAT4X4& GetProjection() const { return projection; }

	// ���_�擾
	const VECTOR3& GetPos() const { return pos; }

	// �����_�擾
	const VECTOR3& GetTarget() const { return target; }

	// ������擾
	const VECTOR3& GetUp() const { return up; }

	// �O�����擾
	const VECTOR3& GetFront() const { return front; }

	// �E�����擾
	const VECTOR3& GetRight() const { return right; }

	// �E�����擾
	const float& GetNear() const { return m_near; }

	// �E�����擾
	const float& GetFar() const { return m_far; }


	// �ŒZ����
	const float& GetFor() const { return fov; }

	// ������
	const float& GetAspext() const { return aspext; }
	//MEMO:SetView(XMMATRIX)�Ƃ��������炢������
	//SetProjection

private:

	DirectX::XMFLOAT4X4 view =     {0,0,0,0,  0,0,0,0, 0,0,0,0,  0,0,0,0};
	DirectX::XMFLOAT4X4 projection={0,0,0,0,  0,0,0,0, 0,0,0,0,  0,0,0,0 };

	VECTOR3 pos = {0,0,0};
	VECTOR3 target = { 0,0,0 };

	VECTOR3 up = { 0,0,0 };
	VECTOR3 front = { 0,0,0 };
	VECTOR3 right = { 0,0,0 };

	float m_near;
	float m_far;
	float fov;
	float aspext;
};
