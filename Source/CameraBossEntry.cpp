#include "CameraController.h"
#include "Charactor.h"
#include "Collision.h"
#include "Player.h"
#include "Stage.h"
#include "EnemyBase.h"

CameraBossEntry::CameraBossEntry(Actor* owner, EnemyBase* enm, BossStage* stage) {
	this->owner = owner;
	this->state = stage;
	this->enm = enm;
}
//����������
void CameraBossEntry::Init()
{
	if (this->owner == nullptr)assert(!"owner��null");
	if (this->state == nullptr)assert(!"state��null");
	if (this->enm == nullptr)assert(!"enm��null");
	manager->cameraType = CameraManager::CameraType::TypeNormal;
	//	Angle.x = DirectX::XMConvertToRadians(10);
	angle.y = DirectX::XMConvertToRadians(15);
	angle.x = DirectX::XMConvertToRadians(45);

	endTargetPos = owner->GetPos();
	startEyePos = { 0,100,100 };
	eye = startEyePos;
	targetPos = { 0,0,0 };

	LookatOwnerTimer = 0.0f;
}

//���_�ʒu�����߂�X�V
void CameraBossEntry::UpdateEye()
{

	////�J������onwer�Ƃ̋���
	//constexpr float L = 100.0f;
	////�J�����̍ő�Y��
	//constexpr float MaxAngleY = 0.5f;


	//float ax = TK_Lib::Gamepad::GetAxisRX() * DirectX::XMConvertToRadians(2);
	//float ay = TK_Lib::Gamepad::GetAxisRY() * DirectX::XMConvertToRadians(2);
	//float az = 0.0f;

	//angle.x += ax;
	//angle.y -= ay;//���͂Ƃ͋t�̕����ɂ��Ă���
	//angle.z += az;

	//if (angle.y >= MaxAngleY) angle.y = MaxAngleY;
	//if (angle.y <= -MaxAngleY)angle.y = -MaxAngleY;




	////��]�s��ɕϊ�����
	//DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

	////�O���x�N�g���̎Z�o
	//DirectX::XMVECTOR Front = Transform.r[2];
	////
	//VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);


	//endEyePos.x = owner->GetPos().x - front.x * L;
	//endEyePos.y = owner->GetPos().y - front.y * L;
	//endEyePos.z = owner->GetPos().z - front.z * L;

	//LerpEyeCamera(0.2f);
}
//�����_�����߂�X�V
void CameraBossEntry::UpdateTarget()
{

	targetPos = owner->GetPos();
	//SetTarget(owner->pos);
	//LerpTargetCamera(0.05f);
}

//�X�V����
void CameraBossEntry::Update()
{
	////���_�ʒu�����߂�X�V
	//UpdateEye();
	////�����_�����߂�X�V
	//UpdateTarget();

	//�n�ʂƃ��C�s�b�N
	//RayPick();
}
//�I������
void CameraBossEntry::End()
{

}
//Imgui
void CameraBossEntry::Imgui()
{
	ImGui::Begin(u8"�Q�[��");
	ImGui::Text("CameraBossEntry");
	ImGui::Text("Angle.x.y.z=%f,%f,%f", angle.x, angle.y, angle.z);
	ImGui::Text("eye.x.y.z=%f,%f,%f", eye.x, eye.y, eye.z);
	ImGui::Text("Target.x.y.z=%f,%f,%f", targetPos.x, targetPos.y, targetPos.z);
	ImGui::End();
}


//Owner�̕��Ɍ����Ă���
bool CameraBossEntry::LookatOwner()
{
	LookatOwnerTimer += TK_Lib::Window::GetElapsedTime();
	if (LookatOwnerTimer >= 3.0f)
	{
		LookatOwnerTimer = 0.0f;
		return true;
	}
	//�J�����̒����_
	targetPos = owner->GetPos();

	//�J������onwer�Ƃ̋���
	static float L = 60.0f;

	ImGui::Begin("EvectBossCamera");
	ImGui::SliderAngle("angle_Y", &angle.y);
	ImGui::SliderAngle("angle_X", &angle.x);
	ImGui::SliderFloat("Length", &L,0.0f,500.0f);
	ImGui::End();




	//��]�s��ɕϊ�����
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

	//�O���x�N�g���̎Z�o
	DirectX::XMVECTOR Front = Transform.r[2];
	//
	VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);


	eye.x = owner->GetPos().x - front.x * L;
	eye.y = owner->GetPos().y - front.y * L;
	eye.z = owner->GetPos().z - front.z * L;

	startTargetPos = owner->GetPos();
	endTargetPos = enm->GetPos();

	//�J�����̐ݒ�
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });

	return false;
}
//�G�̕����Ɍ���
bool CameraBossEntry::LookatOwnerFront()
{

	angle.x += XMConvertToRadians(0.4f);
	if (angle.x >= XMConvertToRadians(170))
	{
		angle.x = XMConvertToRadians(170);
		return true;
	}

	//�J������onwer�Ƃ̋���
	static float L = 60.0f;

	//��]�s��ɕϊ�����
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

	//�O���x�N�g���̎Z�o
	DirectX::XMVECTOR Front = Transform.r[2];
	VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);


	eye.x = owner->GetPos().x - front.x * L;
	eye.y = owner->GetPos().y - front.y * L;
	eye.z = owner->GetPos().z - front.z * L;

	LerpTargetCamera(0.004f);

	//�J�����̐ݒ�
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });
	return false;
}
//�{�X������
bool CameraBossEntry::LookatBoss()
{
	//�J������onwer�Ƃ̋���
	static float L = 60.0f;

	angle.x = XMConvertToRadians(180);
	angle.y = XMConvertToRadians(15);

	//��]�s��ɕϊ�����
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

	//�O���x�N�g���̎Z�o
	DirectX::XMVECTOR Front = Transform.r[2];
	VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);


	eye.x = enm->GetPos().x - front.x * L;
	eye.y = enm->GetPos().y - front.y * L;
	eye.z = enm->GetPos().z - front.z * L;

	targetPos = enm->GetPos();
	targetPos.y = 13.0f;

	startEyePos=eye ;
	//LerpTargetCamera(0.004f);
	//Lear(0.004f);
	//�J�����̐ݒ�
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });

	return true;
}
//�{�X����J�����������
bool CameraBossEntry::BackCamera()
{
	LookatOwnerTimer += TK_Lib::Window::GetElapsedTime();
	if (LookatOwnerTimer >= 1.0f)
	{
		enm->SetActionFlg(true);
		angle.y = DirectX::XMConvertToRadians(10);
		angle.z = DirectX::XMConvertToRadians(10);
	
	}
	//�J������onwer�Ƃ̋���
	const float L = 100.0f;

	//��]�s��ɕϊ�����
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

	//�O���x�N�g���̎Z�o
	DirectX::XMVECTOR Front = Transform.r[2];
	VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);


	endEyePos.x = owner->GetPos().x - front.x * L;
	endEyePos.y = owner->GetPos().y - front.y * L;
	endEyePos.z = owner->GetPos().z - front.z * L;

	if (LerpEyeCamera(0.026f))
	{
		return true;
	}
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });
	return false;
}

