#include "Charactor.h"
#include "Collision.h"
#include "Lib_EffectManager.h"

//����������
void Charactor::Init()
{
	pos = { 0,0,0 };
	SetQuaternion({ 0,0,0,1 });
	scale = { 0.01f,0.01f,0.01f };
	SetOldPos(pos);
}
//�X�V����
void Charactor::Update()
{
	//���G���Ԃ̍X�V
	InvincibleTimeUpdate();
	//�U���N�[���^�C���X�V
	AttackCoolTimeUpdate();
	//���f���̍s��X�V
	if (modelIndex >= 0)
	{
		TK_Lib::Model::Tranceform(modelIndex, pos, GetQuaternion(), scale);
		TK_Lib::Model::AnimetionUpdate(modelIndex);
	}
	
}
//�`�揈��
void Charactor::ModelRender()
{
	if (modelIndex >= 0)
	{
		//�J�������O�ɂ���Ȃ�
		if (TK_Lib::Camera::IsCamera(GetPos()))
		{
			ShaderType shaderType= ShaderType::Shader_MakeShadow;
			//�����J�������牓���ꍇ�ADrawShadow�ɐ؂�ւ��B
			if (SearchPosition(200, TK_Lib::Camera::GetPos())==false)
			{
				shaderType = ShaderType::Shader_DrawShadow;
			}
			TK_Lib::Draw::Model(modelIndex, shaderType);
		}

	}
}
//���f���p�̕`�揈��
void Charactor::Render()
{

}
//�f�o�b�O
void Charactor::CollisionDebug()
{
	//�����蔻��
	TK_Lib::Debug3D::Circle(pos, collisionRadius);
	//���C�s�b�N�̕␳

	//���C�s�b�N�p�̓����蔻��
	VECTOR3 Start = { pos.x,pos.y + BesideRayPickUP,     pos.z };
	VECTOR3 End =   { pos.x,pos.y - VerticalRayPickUnder, pos.z };
	TK_Lib::Debug3D::Line(Start, End, { 0,1,0,1 });

	//���C�s�b�N�p�̓����蔻��
	Start = { pos.x - moveVec.x, pos.y - moveVec.y + BesideRayPickUP,     pos.z - moveVec.z };
	End =   { pos.x + moveVec.x ,pos.y + moveVec.y + BesideRayPickUP, pos.z + moveVec.z };

	TK_Lib::Debug3D::Line(Start, End, {0,1,0,1});
}
//�f�o�b�O
void Charactor::ParameterDebug()
{
	ImGui::DragFloat3("Pos",&pos.x,0.1f);
	ImGui::DragFloat3("Scale", &scale.x, 0.1f);
}

//Imgui�f�o�b�O
void Charactor::ImguiDebug()
{

	
}
//�o��邩�ǂ���
bool Charactor::TryInclined(const VECTOR3 Normal)
{
	XMVECTOR V_up = XMVectorSet(0, 1, 0, 0);
	XMVECTOR V_Normal = XMLoadFloat3(&Normal);
	V_Normal = XMVector3Normalize(V_Normal);

	float dot;
	XMVECTOR Dot;
	Dot=XMVector3Dot(V_up,V_Normal);
	XMStoreFloat(&dot, Dot);
	dot=acosf(dot);
	dot -= XMConvertToRadians(90);
	dot = fabsf(dot);

	ImGui::Begin("aaa");
	ImGui::Text("Radius=%f", dot/0.01754f);
	if (dot >= CanInclined)
	{
		ImGui::Text("OK");
	}
	ImGui::End();

	return (dot >= CanInclined);

	
	
	
}


//��]����
void Charactor::Turn(const VECTOR3& moveVec)
{
	VECTOR4 Q = GetQuaternion();
	XMVECTOR Qu = XMLoadFloat4(&Q);

	if (moveVec == VECTOR3{ 0,0,0 })return;
	XMVECTOR Vec;
	//�i�ޕ�����XZ���ʂɕϊ�����
	{
		VECTOR3 vec = moveVec;
		vec.y = 0.0f;
		Vec = DirectX::XMLoadFloat3(&vec);
		XMVECTOR L_moveVec;
		L_moveVec = XMVector3Length(Vec);
		float L;
		XMStoreFloat(&L, L_moveVec);
		if (L <= 0.0f)
		{
			return;
		}
		Vec = XMVector3Normalize(Vec);
	}

	XMVECTOR front;
	//���ʃx�N�g����
	//XZ���ʂɕϊ�����
	{
		VECTOR3 Front = GetFront();
		Front.y = 0.0f;
		front = DirectX::XMLoadFloat3(&Front);
		front = XMVector3Normalize(front);
	}
	//��]��
	XMFLOAT3 Up = GetUp();
	XMVECTOR Axis = DirectX::XMLoadFloat3(&Up);


	//��]��
	XMVECTOR Dot = XMVector3Dot(front, Vec);
	float dot;
	XMStoreFloat(&dot, Dot);
	dot = acosf(dot);//���W�A���ɕϊ�

	//��̃x�N�g�����ߎ����Ă��鎞�͒�����return
	if (isnan(fabsf(dot))) {
		return;
	}

	//��̃x�N�g�����ߎ����Ă��鎞�͒�����return
	if ((fabsf(dot) < XMConvertToRadians(1))) {
		return;
	}

	XMVECTOR q;

	//��]���̎Z�o
	XMVECTOR Cross;
	{
		Cross = XMVector3Cross(front, Vec);
		Cross = XMVector3Normalize(Cross);
	}
	XMFLOAT3 cross;
	XMStoreFloat3(&cross, Cross);


	if (cross.y < 0)
	{
		q = XMQuaternionRotationAxis(-Axis, dot);
	}
	else
	{
		q = XMQuaternionRotationAxis(Axis, dot);
	}




	q = XMQuaternionMultiply(q, Qu);

	//�⊮������
	q = XMQuaternionSlerp(Qu, q, trunSpeed);

	XMStoreFloat4(&Q, q);

	SetQuaternion(Q);


}
//�ڕW�ɐi�ރx�N�g���̎Z�o
bool Charactor::MoveOnPosition(VECTOR3 Position)
{
	constexpr float Scale = 0.1f;
	if (SearchPosition(Scale,Position))
	{
		//�������ɓo�^���Ă���̂Ői�ޕK�v���Ȃ�
		return false;
	}
	VECTOR3 vec = Position - pos;
	vec.y = 0.0f;
	XMVECTOR Vec = XMLoadFloat3(&vec);
	XMVECTOR N_Vec = XMVector3Normalize(Vec);
	//�i�ރx�N�g��
	XMVECTOR MoveVec = XMVectorScale(N_Vec, speed);
	XMStoreFloat3(&moveVec,MoveVec);
	

	return true;
}

//���G�͈͂�Target�������TRUE��Ԃ�
bool Charactor::SearchPosition(const float L,VECTOR3 Position)
{
	//�ڕW�܂ł̋������Z�o
	float TargetL;
	{
		VECTOR3 vec = pos - Position;
		XMVECTOR Vec = XMLoadFloat3(&vec);
		Vec = XMVector3Length(Vec);
		XMStoreFloat(&TargetL, Vec);
	}
	//�ڕW�܂ł̋����Ɣ�ׂ�
	return TargetL <= L;

}

//�c�����̓����蔻��iY�����j
void Charactor::VerticalCollision()
{
	VECTOR3 Start = { pos.x,pos.y + BesideRayPickUP, pos.z };
	VECTOR3 End = { pos.x,pos.y - BesideRayPickUnder, pos.z };
	RayOut ray;
	Collision::Instance().RayPick(Start, End, ray);
	//ImGui::Begin("a");
	//ImGui::Text("%f,%f,%f", ray.Normal.x, ray.Normal.y, ray.Normal.z);
	//ImGui::End();
	if (ray.materialIndex >= 0)
	{
		pos.y = ray.Pos.y;
	}

}
//�������̓����蔻��iXZ���ʁj
void Charactor::BesideCollision()
{
	VECTOR3 Start = { pos.x - moveVec.x,pos.y - moveVec.y + BesideRayPickUP, pos.z - moveVec.z };
	VECTOR3 End = { pos.x + moveVec.x,pos.y + moveVec.y + BesideRayPickUnder, pos.z + moveVec.z };
	//���C�s�b�N�ɓ��������ʒu�̏��
	RayOut ray;
	//�␳�ʒu
	VECTOR3 Position=GetPos();

	//���a���l���������C�s�b�N
	//Collision::Instance().RadiusRayPick(Start, End, ray,1.0f);
	Collision::Instance().RayPick(Start, End, ray);
	//�����������Ă���Ȃ�
	if (ray.materialIndex >= 0)
	{
		////�␳�ʒu�̌v�Z
		//XMVECTOR start = XMLoadFloat3(&Start);
		//XMVECTOR end = XMLoadFloat3(&End);
		////�ǂ̖@��
		//XMVECTOR Normal = XMLoadFloat3(&ray.Normal);
		////�͂ݏo���x�N�g��
		//XMVECTOR V = XMVectorSubtract(end, XMLoadFloat3(&ray.Pos));
		////���˃x�N�g����@���Ɏˉe
		//XMVECTOR Dot = XMVector3Dot(Normal, XMVectorNegate(V));
		//float dot;
		//XMStoreFloat(&dot, Dot);
		//
		//XMVECTOR vec = XMVectorScale(Normal, dot);
		//XMVECTOR Pos = XMVectorAdd(vec, V);
		//XMFLOAT3 Ve;
		//XMStoreFloat3(&Ve, Pos);
		//
		////�i�s�x�N�g�������߂�
		//Position.x += Ve.x;
		//Position.z += Ve.z;
		//�͂ݏo���x�N�g���̎Z�o
		XMVECTOR V_RayHitPositionEnd;
		{
			VECTOR3 rayHitposition;
			rayHitposition = ray.Pos - End;
			V_RayHitPositionEnd = XMLoadFloat3(&rayHitposition);
		}
		
		//�@��
		XMVECTOR RayHitNormal;
		{
			RayHitNormal = XMLoadFloat3(&ray.Normal);
			RayHitNormal = XMVector3Normalize(RayHitNormal);
		}
		
		//���ׂ���␳�ʒu�̎Z�o
		VECTOR3 WallPosition;
		{
			XMVECTOR Dot;
			Dot = XMVector3Dot(V_RayHitPositionEnd, RayHitNormal);
			Dot=XMVector3Length(Dot);
			float dot;
			XMStoreFloat(&dot, Dot);
			XMVECTOR Vec = XMVectorScale(RayHitNormal, dot);
			VECTOR3 vec;
			XMStoreFloat3(&vec, Vec);
		
			WallPosition = End + vec;
			//Position = End + vec;
		}
		
		//���a���A�␳�ʒu��ς���
		{
			//VECTOR3 rayHitposition;
			//rayHitposition = pos - ray.Pos;
			//XMVECTOR V_HitEnd = XMLoadFloat3(&rayHitposition);
			//XMVECTOR Dot = XMVector3Dot(V_HitEnd, RayHitNormal);
			//float dot;
			//XMStoreFloat(&dot, Dot);
			//MEMO �������̕�����������
			//Position = WallPosition + ray.Normal * radius;
			Position = WallPosition;
			//�ł�X���W�������������l���邰���Ȃ̂Ō��i�K�ł͂���ɉ��p���Ă���
		//	Position = WallPosition + ray.Normal * dot;
		}
		//�ǂɂ߂荞��ł��܂��̂ł�����l������
		//���C�s�b�N�ɓ��������ʒu�̏��
		RayOut ray2;
		Start = { pos.x,pos.y + BesideRayPickUP,pos.z };
		End = { Position.x ,Position.y, Position.z };
		Collision::Instance().RayPick(Start, End, ray2);
		//�߂荞�݂��Ă����ǂ���
		if (ray2.materialIndex >= 0)
		{
			//�߂荞�ݔ���
		
			//���z����Ƃ����ł��邩�H
			if (TryInclined(ray2.Normal))
			{
				pos.x = Position.x;
				pos.z = Position.z;
			}
		}
		else
		{
			pos.x = Position.x;
			pos.z = Position.z;
		}
		

	}
	else
	{
		Move();
	}


	////�ߋ��̈ʒu���獡��̈ʒu�܂Ŋe�����Ƀ��C�s�b�N���s��
	//if (oldPos.x >= pos.x)
	//{
	//	Start = { pos.x + speed ,pos.y + BesideRayPickUP, pos.z}; 
	//	End   = { pos.x - speed ,pos.y + BesideRayPickUP, pos.z};
	//}
	//else
	//{
	//	Start = { pos.x - speed ,pos.y + BesideRayPickUP, pos.z}; 
	//	End   = { pos.x + speed ,pos.y + BesideRayPickUP, pos.z};
	//}
	////�����͂�����x��Ƃ����点�ĕ␳������
	//
	//
	//
	//TK_Lib::Debug3D::Line(Start, End, { 0,1,0,1 });
	////X���␳
	//Collision::Instance().RayPick(Start, End, ray);
	////�����������Ă���Ȃ�
	//if (ray.materialIndex >= 0)
	//{
	//	pos.x = ray.Pos.x+(ray.Normal.x*speed);
	//}
	//
	//
	////Z���␳
	//
	////�ߋ��̈ʒu���獡��̈ʒu�܂Ŋe�����Ƀ��C�s�b�N���s��
	//if (oldPos.z >= pos.z)
	//{
	//	Start = { pos.x  ,pos.y + BesideRayPickUP, pos.z + speed };
	//	End = { pos.x  ,pos.y + BesideRayPickUP, pos.z - speed };
	//}
	//else
	//{
	//	Start = { pos.x  ,pos.y + BesideRayPickUP, pos.z - speed };
	//	End = { pos.x  ,pos.y + BesideRayPickUP, pos.z + speed };
	//}
	//
	//TK_Lib::Debug3D::Line(Start, End, { 0,0,1,1 });
	//
	//Collision::Instance().RayPick(Start, End, ray);
	////�����������Ă���Ȃ�
	//if (ray.materialIndex >= 0)
	//{
	//	pos.z = ray.Pos.z + (ray.Normal.z * speed);
	//}



}

//�X�e�[�W�ɂ͂ݏo�Ă��Ȃ����␳(�ŏI�m�F)
void Charactor::StageOverhang()
{
	//�ߋ��̈ʒu���獡�̈ʒu�܂ł����C�s�b�N

//	VECTOR3 Start = { oldPos.x,   oldPos.y+BesideRayPickUP, oldPos.z } ;
//	VECTOR3 End =   { pos.x,      pos.y   +BesideRayPickUP, pos.z };
//	TK_Lib::Debug3D::Line(Start, End);
//	//���C�s�b�N�ɓ��������ʒu�̏��
//	RayOut ray;
//
//	//���a���l���������C�s�b�N
//	Collision::Instance().RayPick(Start, End, ray);
//	//Collision::Instance().RadiusRayPick(Start, End, ray,speed);
//	if (ray.materialIndex >= 0)
//	{
//		pos.z = oldPos.z;
//		pos.x = oldPos.x;
//	}
}
//�w�肳�ꂽ�ʒu�܂ł̃x�N�g���̎Z�o
XMVECTOR Charactor::Vector(const VECTOR3 Position)
{
	XMVECTOR PosA,PosB,Vec;
	PosA = XMLoadFloat3(&pos);
	PosB = XMLoadFloat3(&Position);
	//�����Z�����l��Ԃ�
	return XMVectorSubtract(PosB,PosA);
}
//�w�肳�ꂽ�ʒu�܂ł̋����̎Z�o
float Charactor::Length(const VECTOR3 Position)
{
	float L;
	XMVECTOR Vec=Vector(Position);
	Vec = XMVector3Length(Vec);
	XMStoreFloat(&L,Vec);
	return L;
}

void Charactor::Move()
{
	pos.x += moveVec.x * speed;
	pos.z += moveVec.z * speed;
}
//���x�ɉ��Z
void Charactor::AddVelocity(VECTOR3 velocity)
{
	this->velocity += velocity;

	XMVECTOR Velocity = XMLoadFloat3(&this->velocity);
	float L;
	XMStoreFloat(&L, Velocity);
	//�������x��MaxVelocity���傫���Ȃ�
	if (L >= MaxVelocity)
	{
		Velocity = XMVector3Normalize(Velocity);
		Velocity = XMVectorScale(Velocity,MaxVelocity);
		//���x��MaxVelocity�ɂȂ�
		XMStoreFloat3(&this->velocity, Velocity);
	}
}
void Charactor::SetInvincibleTime(int invincibleTime)
{
	this->invincibleTime = invincibleTime;
}

//�X�V����
void Charactor::AttackCoolTimeUpdate()
{
	if (attackCoolTime >= 1)
	{
		attackCoolTime--;
	}
}

//�X�V����
void Charactor::InvincibleTimeUpdate()
{
	if (invincibleTime >= 1)
	{
		invincibleTime--;
	}
}
//�_���[�W�𔻒�
bool Charactor::AddDamage(int Damage,int SetinvincibleTime)
{
	//�̗͂�0�ȉ��Ȃ�
	if (GetHp()<= 0)return false;
	//���G���Ȃ�
	if (invincibleTime > 0)return false;

	invincibleTime = SetinvincibleTime;
	hp -= Damage;
	
	//���������c���Ă����Ȃ�
	if (hp>=1)
	{//�_���[�W�t���O�̃I��
		SetDamageFlg(true);

	}
	else//���S���Ă���Ȃ�
	{
		//�_���[�W�t���O�̃I��
		SetDeadFlg(true);
	}
	return true;
}
