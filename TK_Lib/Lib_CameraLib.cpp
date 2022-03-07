#include "Lib_CameraLib.h"

void CameraLib::SetLookAt(
	const VECTOR3& pos,
	const VECTOR3& target,
	const VECTOR3& up)
{
	using namespace DirectX;

	XMVECTOR Eye = XMLoadFloat3(&pos);
	XMVECTOR Focus = XMLoadFloat3(&target);
	XMVECTOR Up = XMLoadFloat3(&up);
	XMMATRIX View = XMMatrixLookAtLH(Eye, Focus, Up);
	XMStoreFloat4x4(&view, View);

	// �r���[�s����t�s��(���[���h�s��ɕϊ�)
	XMFLOAT4X4 world;
	XMMATRIX World = XMMatrixInverse(nullptr, View);

	XMStoreFloat4x4(&world, World);

	// �J�����̕��������o��
	this->right = { world._11, world._12, world._13 };
	this->up = { world._21, world._22, world._23 };
	this->front = { world._31, world._32, world._33 };

	// ���_�A�����_��ۑ�
	this->pos = pos;
	this->target = target;



}

void CameraLib::SetPerspectiveFov(float fovY, float aspect, float nearZ, float farZ)
{
	fov= fovY;
	aspext = aspect;

	m_near = nearZ;
	m_far = farZ;

	DirectX::XMMATRIX Projection = DirectX::XMMatrixPerspectiveFovLH(fovY, aspect, nearZ, farZ);
	DirectX::XMStoreFloat4x4(&projection, Projection); // �v���W�F�N�V�����s��쐬
}
void CameraLib::SetOrthongraphic(float Width, float Height, float Near, float Far)
{
	m_near = Near;
	m_far = Far;
	DirectX::XMMATRIX Projection = DirectX::XMMatrixOrthographicLH(Width, Height, Near, Far);
	XMStoreFloat4x4(&projection, Projection);
}


