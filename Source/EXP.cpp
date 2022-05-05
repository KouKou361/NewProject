#include "EXP.h"
#include "EXPManager.h"
#include "Scene.h"
#include "UIDerived.h"
//����������
void EXP::Init(const VECTOR3 &pos)
{
	//�e�N�X�`���̓ǂݍ���
	spriteIndex = TK_Lib::Load::LoadTexture("./Data/Sprite/EXP.png");

	//�ڕW�n�_�̎Z�o
	SetTargetPos();

	//�ʒu�̎Z�o
	SetPos(pos);

	//�����̎Z�o�i�R�U�O�x�j
	angle = XMConvertToRadians(static_cast<float>(rand() % 360));

	//�i�ޕ����̎Z�o
	this->velocity = { sinf(angle),cosf(angle)};

	//�����̎Z�o
	speed = -10;

	timer = 0;
}
//�X�V����
void EXP::Update()
{
	//����K�x���Ԃ��߂���������鏈��
	DeleteToTimer();

	//����K�x�ڕW�ɏ������ꍇ�����鏈��
	const float DeleteLength = 40.0f;
	DeleteMinLength(DeleteLength);

	//�ڕW�n�_�ɐi��
	ModeToTarget();

}

//�X�V����
void EXP::Render()
{
	const VECTOR4 cut = { 0,0,1024,1024 };
	//EXP�̕`��
	TK_Lib::Draw::Sprite(spriteIndex, pos, size, cut, angle);
}

//�j������
void EXP::Delete()
{
	//�T�E���h�i�`�������j
	TK_Lib::Lib_Sound::SoundPlay("GetCoin",false);

	//�Q�[���I�[�o�[�^�C�}�[�̉�
	const int AddGameOverTimerNum = 5;
	scene->GetStageManager()->GetNowStage()->GetUiTimer()->AddGameOverTimer(AddGameOverTimerNum);

	//�������g�̔j��
	scene->GetExpManager()->Destroy(this);
}

//���[���h����X�N���[�����W�ɕϊ�
VECTOR2 EXP::WorldToScreen(const VECTOR3& pos)
{
	XMVECTOR WorldPosition;
	WorldPosition = XMLoadFloat3(&pos);

	//���W�ϊ�
	XMMATRIX View = XMLoadFloat4x4(&TK_Lib::Camera::GetView());
	XMMATRIX Projection = XMLoadFloat4x4(&TK_Lib::Camera::GetProjection());
	XMMATRIX World = XMMatrixIdentity();

	VECTOR2 viewport = TK_Lib::Window::GetWindowSize();

	VECTOR3 screenPos;
	//���[���h���W����X�N���[�����W�ɕϊ�����
	XMVECTOR ScreenPosition;
	ScreenPosition = XMVector3Project(WorldPosition, 0, 0, viewport.x, viewport.y, 0.0f, 1.0, Projection, View, World);
	XMStoreFloat3(&screenPos, ScreenPosition);

	return VECTOR2{ screenPos.x,screenPos.y };
}

//�ڕW�n�_�̎Z�o
void EXP::SetTargetPos()
{
	//�ڕW�̍���
	const float targetPosY = 20.0f;
	//�ڕW�̉��̔���
	const float targetPosX = TK_Lib::Window::GetWindowSize().x/2;

	targetPos.x = targetPosX;
	targetPos.y = targetPosY;
	
}

//�ʒu�̎Z�o
void EXP::SetPos(const VECTOR3& pos)
{

	//�ʒu�̎Z�o
	const float PosYScreenDown = 10.0f;//�X�N���[�����W�ɕϊ�������������Ə�ɏグ��B
	this->pos = WorldToScreen(pos);//���[���h���W����X�N���[�����W
	this->pos.y -= PosYScreenDown;
	
}

//�ڕW�n�_�ɐi��
void EXP::ModeToTarget()
{
	//�����x
	const float AcceleSpeed = 0.2f;
	speed += AcceleSpeed;//��������

	if (speed >= 0)
	{
		//�p�x�̎Z�o
		angle = atan2f(targetPos.y - pos.y, targetPos.x - pos.x);
	}

	//�i�ރx�N�g���̎Z�o
	const VECTOR2 V = { cosf(angle), sinf(angle) };
	velocity = speed * V;

	pos.x += velocity.x;	//�ʒu�̍X�V����
	pos.y += velocity.y;	//�ʒu�̍X�V����
}
//����K�x���Ԃ��߂���������鏈��
void EXP::DeleteToTimer()
{
	//�O�̂���
	timer += TK_Lib::Window::GetElapsedTime();

	//���Ŏ���
	const float DeleteTime = 4;
	if (timer >= DeleteTime)
	{
		Delete();
	}

}

//����K�x�ڕW�ɏ������ꍇ�����鏈��
void EXP::DeleteMinLength(const float& DeleteLength)
{
	float l=0;
	{
		VECTOR2 Vec;
		Vec.x = targetPos.x - pos.x;
		Vec.y = targetPos.y - pos.y;
		XMVECTOR V;
		V = XMLoadFloat2(&Vec);
		V = XMVector3Length(V);
		XMStoreFloat(&l, V);
	}
	if (l <= DeleteLength)
	{
		Delete();
	}

}