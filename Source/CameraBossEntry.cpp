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

	manager->cameraType = CameraManager::CameraType::TYPE_BOSS;

	const float AngleY = 15;
	const float AngleX = 45;
	angle.y = DirectX::XMConvertToRadians(AngleY);
	angle.x = DirectX::XMConvertToRadians(AngleX);

	endTargetPos = owner->GetPos();
	startEyePos = { 0,100,100 };
	eye = startEyePos;
	targetPos = { 0,0,0 };

	lookAtOwnerTimer = 0.0f;
}

//���_�ʒu�����߂�X�V
void CameraBossEntry::UpdateEye()
{
	//BossEntryAction���󋵂ɉ����đ��삵�Ă����̂�
	//�L���Ȃ�
}
//�����_�����߂�X�V
void CameraBossEntry::UpdateTarget()
{
	//BossEntryAction���󋵂ɉ����đ��삵�Ă����̂�
    //�L���Ȃ�
}
//�X�V����
void CameraBossEntry::Update()
{
	//BossEntryAction���󋵂ɉ����đ��삵�Ă����̂�
    //�L���Ȃ�
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
	//���̏�ԂɈڍs����܂ł̎���
	{
		const float NextTimer = 3.0f;

		lookAtOwnerTimer += TK_Lib::Window::GetElapsedTime();
		if (lookAtOwnerTimer >= NextTimer)
		{
			lookAtOwnerTimer = 0.0f;
			return true;
		}
	}
	
	//�J�����̒����_
	{
		targetPos = owner->GetPos();
	}

	//�J�����̈ʒu�̎Z�o
	{
		//�J������onwer�Ƃ̋���
		static float L = 60.0f;

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
	}

	
	
	VECTOR3 Vup = { 0,1,0 };
	//�J�����̐ݒ�
	TK_Lib::Camera::SetLookAt(eye, targetPos, Vup);

	return false;
}
//�G�̕����Ɍ���
bool CameraBossEntry::LookatOwnerFront()
{
	//�G�̕����Ɍ����J�����̈ړ��X�s�[�h
	constexpr float CameraXSpeed = XMConvertToRadians(0.4f);
	//���̃J������ԂɑJ�ڂ���p�x
	constexpr float NextCameraMax = XMConvertToRadians(170);
	//����⊮�̎���
	const float LerpSpeed = 0.004f;

	//�J�����̈ʒu�Z�o
	{
		angle.x += CameraXSpeed;
		if (angle.x >= NextCameraMax)
		{
			angle.x = NextCameraMax;
			return true;
		}

		//��]�s��ɕϊ�����
		DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

		//�O���x�N�g���̎Z�o
		DirectX::XMVECTOR Front = Transform.r[2];
		VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);

		//�J������onwer�Ƃ̋���
		static float L = 60.0f;
		eye.x = owner->GetPos().x - front.x * L;
		eye.y = owner->GetPos().y - front.y * L;
		eye.z = owner->GetPos().z - front.z * L;
	}

	//�J�����̒����_�̎Z�o
	LerpTargetCamera(LerpSpeed);

	//�J�����̐ݒ�
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });
	return false;
}
//�{�X������
bool CameraBossEntry::LookatBoss()
{
	//�J������onwer�Ƃ̋���
	static float L = 60.0f;
	//�G�̕����Ɍ����J�����̈ړ��X�s�[�h
	constexpr float CameraX = XMConvertToRadians(180);
	//���̃J������ԂɑJ�ڂ���p�x
	constexpr float CameraY = XMConvertToRadians(15);
	//�����_��Y
	const float TargetPosY = 13.0f;


	
	
	angle.x = CameraX;
	angle.y = CameraY;
	
	//�J�����̈ʒu�Z�o
	{
		//��]�s��ɕϊ�����
		DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

		//�O���x�N�g���̎Z�o
		DirectX::XMVECTOR Front = Transform.r[2];
		VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);


		eye.x = enm->GetPos().x - front.x * L;
		eye.y = enm->GetPos().y - front.y * L;
		eye.z = enm->GetPos().z - front.z * L;
		startEyePos = eye;
	}

	//�J�����̒����_�̎Z�o
	{
		targetPos = enm->GetPos();
		targetPos.y = TargetPosY;
	}

	//�J�����̐ݒ�
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });

	return true;
}
//�{�X����J�����������
bool CameraBossEntry::BackCamera()
{
	//�G��������������
	const float enmActionTimer = 1.0f;
	//�J�����̌Œ�p�x
	const float AngleY = 10.0f;
	const float AngleZ = 10.0f;
	//����⊮�̎���
	const float LerpTimer = 0.026f;
	//�J������onwer�Ƃ̋���
	const float L = 100.0f;



	lookAtOwnerTimer += TK_Lib::Window::GetElapsedTime();
	//���Ԃ������Ȃ�
	if (lookAtOwnerTimer >= enmActionTimer)
	{
		enm->SetActionFlg(true);//�G�s���\�̒ʒm
		angle.y = DirectX::XMConvertToRadians(AngleY);
		angle.z = DirectX::XMConvertToRadians(AngleZ);
	
	}

	//endEyePos�̎Z�o
	{
		//��]�s��ɕϊ�����
		DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.y, angle.x, angle.z);

		//�O���x�N�g���̎Z�o
		DirectX::XMVECTOR Front = Transform.r[2];
		VECTOR3 front; DirectX::XMStoreFloat3(&front, Front);


		endEyePos.x = owner->GetPos().x - front.x * L;
		endEyePos.y = owner->GetPos().y - front.y * L;
		endEyePos.z = owner->GetPos().z - front.z * L;
	}
	//�J�����̒����_�̎Z�o
	{
		targetPos = enm->GetPos();
	}

	//����⊮
	if (LerpEyeCamera(LerpTimer))
	{
		//����⊮�I��
		return true;
	}
	TK_Lib::Camera::SetLookAt(eye, targetPos, { 0,1,0 });
	return false;
}

