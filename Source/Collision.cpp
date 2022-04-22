#include "Collision.h"
Collision* Collision::instance;
Collision::Collision()
{
	instance = this;
	navCollision = make_unique<NavCollision>();
}
//�o�^
void Collision::RegisterModel(const int model, const ModelCollisionType type,Actor* actor)
{
	ModelCollsion modelCollision;
	modelCollision.modelIndex = model;
	modelCollision.type = type;
	modelCollision.actorModel = actor;

	collisionModels.push_back(modelCollision);
}
//�S����
void Collision::Clear()
{

	collisionModels.clear();
	navCollision->Clear();
}
//���C�s�b�N
void Collision::RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray)
{
	float L = FLT_MAX;
	RayOut nearRay;
	for (ModelCollsion model : collisionModels)
	{
		//�������f���^�C�v�����C�s�b�N�p�̃��f���ł͂Ȃ��̂Ȃ��
		if (model.modelIndex <= -1)continue;

		//�������f���^�C�v�����C�s�b�N�p�̃��f���ł͂Ȃ��̂Ȃ��
		if (model.type != ModelCollisionType::COLLISION_MODEL)continue;


		TK_Lib::Model::LayPick(model.modelIndex,start, end, ray);
		if (ray.materialIndex <= -1)continue;
		//�������܂Ń��C�s�b�N�������ŋ߂������Ȃ�
		if (L >= ray.distance)
		{
			nearRay = ray;
		}
	}
	ray = nearRay;
}

//���C�s�b�N
void Collision::RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray,Actor*& actor)
{
	float L = FLT_MAX;
	RayOut nearRay;
	Actor* saveActor = nullptr;
	for (ModelCollsion model : collisionModels)
	{
		//�������f���^�C�v�����C�s�b�N�p�̃��f���ł͂Ȃ��̂Ȃ��
		if (model.type != ModelCollisionType::COLLISION_MODEL)continue;

		TK_Lib::Model::LayPick(model.modelIndex, start, end, ray);
		if (ray.materialIndex <= -1)continue;
		//�������܂Ń��C�s�b�N�������ŋ߂������Ȃ�
		if (L >= ray.distance)
		{
			if (model.actorModel != nullptr)
			{
				saveActor = model.actorModel;
			}
			
			nearRay = ray;
		}
	}
	ray = nearRay;
	actor = saveActor;
}


//AI�̂��߂̃X�e�[�W�\��
void Collision::NacStageBuild()
{
	for (ModelCollsion modelCollision : collisionModels)
	{
		//�������f���^�C�v���i�r���f���ł͂Ȃ��̂Ȃ��
		if (modelCollision.type != ModelCollisionType::NAV_MODEL)continue;
		//�\��
		navCollision->NavStageBuild(modelCollision.modelIndex);
	}
}
//���f���̓����蔻��`��i�f�o�b�O�p�j
void Collision::CollisionRender()
{

	for (int i = 0; i < GetCollisionModels()->size(); i++)
	{
		int Index = GetCollisionModels()->at(i).modelIndex;
		TK_Lib::Draw::Model(Index, ShaderType::Shader_NoLight);
	}

}
//�i�r���b�V���̕`��i�f�o�b�O�p�j
void Collision::NavRender()
{
	navCollision->Render();

}
//�����蔻��̃��f���̍폜
void Collision::DeleteCollisionModel(int modelIndex)
{
	for (auto it = collisionModels.begin(); it != collisionModels.end();)
	{

		if (it->modelIndex == modelIndex)
		{
			collisionModels.erase(it);
			break;
		}
		else
		{
			it++;
		}

		
	}
}
//
bool Collision::SearchRoat(const VECTOR3& Pos, VECTOR3& OutPos)
{
	VECTOR3 StartPos = { Pos.x,Pos.y + RayUP ,Pos.z };
	VECTOR3 EndPos = { Pos.x,Pos.y - RayUnder ,Pos.z };
	NavEdge *edge = nullptr;
	if (navCollision->GetOnNacMesh(StartPos, EndPos, edge))
	{
		//�o�H�T��
		navCollision->SearchRoat(edge, navCollision->GetNavTarget()->inMesh);
		bool result= navCollision->CreateNearRoat(Pos, navCollision->GetNavTarget()->position, OutPos);

		//navCollision->ClearRoomPos(Pos, OutPos, OutPos);
		return result;

	}
	return false;


	
}

//���a�����l���������C�s�b�N
void Collision::RadiusRayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray, float radius)
{
	float L = FLT_MAX;
	RayOut nearRay;
	for (ModelCollsion model : collisionModels)
	{
		//�������f���^�C�v�����C�s�b�N�p�̃��f���ł͂Ȃ��̂Ȃ��
		if (model.type != ModelCollisionType::COLLISION_MODEL)continue;

		TK_Lib::Model::RadiusLayPick(model.modelIndex, start, end, ray,radius);
		//�������܂Ń��C�s�b�N�������ŋ߂������Ȃ�
		if (L >= ray.distance)
		{
			nearRay = ray;
		}
	}
	ray = nearRay;
}

//�~�̉~�Ƃ̓����蔻��
bool Collision::SphereVsSphere(const VECTOR3& posA, const float& weghtA, const float& radiusA, const VECTOR3& posB, const float& weghtB, const float& radiusB, VECTOR3& outPosA,VECTOR3& outPosB)
{
	VECTOR3  vec = posB-posA;
	XMVECTOR Vec = XMLoadFloat3(&vec);
	//�����o������
	XMVECTOR N_Vec = XMVector3Normalize(Vec);
	Vec = XMVector3Length(Vec);
	float L;
	XMStoreFloat(&L, Vec);

	//�����������Ă����Ȃ�
	if (radiusA + radiusB >= L)
	{
		//�d�����l������
		float weghtARatio = (weghtB / (weghtA + weghtB))*(L-(radiusA + radiusB));
		float weghtBRatio = (weghtA / (weghtA + weghtB))*(L-(radiusA + radiusB));
		
		//PosA�̈ړ��v�Z
			XMVECTOR MoveVec = XMVectorScale(N_Vec, weghtARatio);
			VECTOR3 V;
			XMStoreFloat3(&V, MoveVec);
			outPosA = V + posA;
			outPosA.y = posA.y;

		//PosB�̈ړ��v�Z
			MoveVec = XMVectorScale(N_Vec, -weghtBRatio);
			XMStoreFloat3(&V, MoveVec);
			outPosB = V + posB;
			outPosB.y = posB.y;
			return true;
		
		
	}
	return false;


}

void Collision::SetTarget(const VECTOR3& Pos)
{

	VECTOR3 StartPos = { Pos.x,Pos.y + RayUP ,Pos.z };
	VECTOR3 EndPos = { Pos.x,Pos.y - RayUnder ,Pos.z };
	
	navCollision->SetTarget(StartPos, EndPos);
}
