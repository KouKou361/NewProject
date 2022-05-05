#include "CameraController.h"
#include "Charactor.h"
#include "Collision.h"


CameraNormal::CameraNormal(Actor* owner) {
	this->owner = owner;

}
//����������
void CameraNormal::Init()
{
	//�J�����̐؂�ւ�莞�̃J����Y�̊p�x
	constexpr float InitCameraYAngle = DirectX::XMConvertToRadians(10.0);
	angle.y = InitCameraYAngle;

	manager->cameraType = CameraManager::CameraType::TYPE_NORMAL;
	endTargetPos = owner->GetPos();

	//����⊮
	LerpEyeCamera(0.01f);

}
//���_�ʒu�����߂�X�V
void CameraNormal::UpdateEye()
{

	//�J������onwer�Ƃ̋���
	const float L = 100.0f;
	//�J�����̍ő�Y��
	const float MaxAngleY = 0.5f;
	//�J�����̊��x
	constexpr float CameraSensitivity = DirectX::XMConvertToRadians(2);
	
	
	float ax = TK_Lib::Gamepad::GetAxisRX()  * CameraSensitivity;
	float ay = TK_Lib::Gamepad::GetAxisRY()  * CameraSensitivity;
	float az = 0.0f;
	
	angle.x += ax;
	angle.y -= ay;//���͂Ƃ͋t�̕����ɂ��Ă���
	angle.z += az;
	
	if (angle.y >= MaxAngleY) angle.y = MaxAngleY;
	if (angle.y <= -MaxAngleY)angle.y = -MaxAngleY;
	
	//��]�s��ɕϊ�����
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);
	
	//�O���x�N�g���̎Z�o
	DirectX::XMVECTOR Front = Transform.r[2];
	//
	VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);

	////
	////
	////
	////endEyePos = { 0, 10, 0 };
	//
	////�v���C���[�̈ʒu�iXZ���ʁj
	//VECTOR3 plPos;
	//{
	//	plPos = owner->GetPos();
	//	plPos.y = 0;
	//}
	//
	////�J�����̈ʒu�iXZ���ʁj
	//VECTOR3 CameraPos;
	//{
	//	CameraPos = endEyePos;
	//	CameraPos.y = 0;
	//}
	//
	//XMVECTOR Vec=XMVectorSet(0,0,0,0);
	//{
	//VECTOR3 v = plPos - CameraPos;
	//v.y = 0;
	//XMVECTOR V = XMLoadFloat3(&v);
	//V = XMVector3Normalize(V);
	//Vec=XMVectorScale(V, L);
	//}
	//
	//XMVECTOR pos;
	//{
	//	VECTOR3 Pos = owner->GetPos();
	//	pos=XMLoadFloat3(&Pos);
	//}
	//
	//
	//pos =XMVectorAdd(-Vec,pos);
	//XMStoreFloat3(&endEyePos, pos);
	////
	//endEyePos.y = owner->GetPos().y - front.y * L;
	//

	//endEyePos�̎Z�o
	{
		endEyePos.x = owner->GetPos().x - front.x * L;
		endEyePos.y = owner->GetPos().y - front.y * L;
		endEyePos.z = owner->GetPos().z - front.z * L;
	}

	//����⊮
	LerpEyeCamera(0.2f);
}
//�����_�����߂�X�V
void CameraNormal::UpdateTarget()
{
	//�J�����̐���⊮�̎���
	const float LerpTimer = 0.2f;

	targetPos = owner->GetPos();
	endTargetPos = targetPos;
	LerpTargetCamera(LerpTimer);
	//SetTarget(owner->pos);
	//LerpTargetCamera(0.05f);
}

//�X�V����
void CameraNormal::Update()
{
	//���_�ʒu�����߂�X�V
	UpdateEye();
	//�����_�����߂�X�V
	UpdateTarget();

	//�n�ʂƃ��C�s�b�N
	//RayPick();

	//�J�����̐ݒ�
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });
}
//�I������
void CameraNormal::End()
{

}
//Imgui
void CameraNormal::Imgui()
{
	ImGui::Begin(u8"�Q�[��");
	ImGui::Text("CameraNormal");
	ImGui::Text("Angle.x.y.z=%f,%f,%f", angle.x, angle.y, angle.z);
	ImGui::Text("eye.x.y.z=%f,%f,%f", eye.x, eye.y, eye.z);
	ImGui::Text("Target.x.y.z=%f,%f,%f", targetPos.x, targetPos.y, targetPos.z);
	ImGui::End();
}

