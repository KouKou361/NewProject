#include "Collision.h"
Collision* Collision::instance;

Collision::Collision()
{
	instance = this;
	navCollision = make_unique<NavCollision>();
}
//Navメッシュを使って経路探索をするモデル登録
void Collision::RegisterModel(const int model, const ModelCollisionType type,Actor* actor)
{
	ModelCollsion modelCollision;
	modelCollision.modelIndex = model;
	modelCollision.type = type;
	modelCollision.actorModel = actor;

	collisionModels.push_back(modelCollision);
}
//Navメッシュを使って経路探索をするモデル全消し
void Collision::Clear()
{
	collisionModels.clear();
	navCollision->Clear();
}

//レイピック
void Collision::RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray)
{
	float L = FLT_MAX;
	RayOut nearRay;
	for (const ModelCollsion &model : collisionModels)
	{
		//もしモデルタイプがレイピック用のモデルではないのならば
		if (model.modelIndex <= -1)continue;

		//もしモデルタイプがレイピック用のモデルではないのならば
		if (model.type != ModelCollisionType::COLLISION_MODEL)continue;


		TK_Lib::Model::LayPick(model.modelIndex,start, end, ray);
		if (ray.materialIndex <= -1)continue;
		//もし今までレイピックした中で近い距離なら
		if (L >= ray.distance)
		{
			nearRay = ray;
		}
	}
	ray = nearRay;
}

//レイピック
void Collision::RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray,Actor*& actor)
{
	float L = FLT_MAX;
	RayOut nearRay;
	Actor* saveActor = nullptr;
	for (const ModelCollsion &model : collisionModels)
	{
		//もしモデルタイプがレイピック用のモデルではないのならば
		if (model.type != ModelCollisionType::COLLISION_MODEL)continue;

		TK_Lib::Model::LayPick(model.modelIndex, start, end, ray);
		if (ray.materialIndex <= -1)continue;
		//もし今までレイピックした中で近い距離なら
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


//ナビメッシュ構築（最初に呼んでおく）
void Collision::NacStageBuild()
{
	for (const ModelCollsion &modelCollision : collisionModels)
	{
		//もしモデルタイプがナビモデルではないのならば
		if (modelCollision.type != ModelCollisionType::NAV_MODEL)continue;
		//構成
		navCollision->NavStageBuild(modelCollision.modelIndex);
	}
}
//モデルの当たり判定描画（デバッグ用）
void Collision::CollisionRender()
{

	for (int i = 0; i < GetCollisionModels()->size(); i++)
	{
		int Index = GetCollisionModels()->at(i).modelIndex;
		TK_Lib::Draw::Model(Index, ShaderType::Shader_NoLight);
	}

}
//ナビメッシュの描画（デバッグ用）
void Collision::NavRender()
{
	navCollision->Render();

}
//当たり判定のモデルの削除
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

//経路探索
//(戻り値：経路探索外にいる時、または経路探索失敗した場合はfalse)
//成功した時は戻り値がtrue
bool Collision::SearchRoat(const VECTOR3& Pos, VECTOR3& OutPos)
{
	VECTOR3 StartPos = { Pos.x,Pos.y + RayUP ,Pos.z };
	VECTOR3 EndPos = { Pos.x,Pos.y - RayUnder ,Pos.z };
	NavEdge *edge = nullptr;
	if (navCollision->GetOnNavMeshToRayPick(StartPos, EndPos, edge))
	{
		//経路探索
		navCollision->SearchRoat(edge, navCollision->GetNavTarget()->inMesh);
		bool result= navCollision->CreateNearVectol(Pos, navCollision->GetNavTarget()->pos, OutPos);

		//navCollision->ClearRoomPos(Pos, OutPos, OutPos);
		return result;

	}
	return false;


	
}

//半径分を考慮したレイピック
void Collision::RadiusRayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray, float radius)
{
	assert(L"没関数を使おうとしました！");
	float L = FLT_MAX;
	RayOut nearRay;
	for (const ModelCollsion &model : collisionModels)
	{
		//もしモデルタイプがレイピック用のモデルではないのならば
		if (model.type != ModelCollisionType::COLLISION_MODEL)continue;

		TK_Lib::Model::RadiusLayPick(model.modelIndex, start, end, ray,radius);
		//もし今までレイピックした中で近い距離なら
		if (L >= ray.distance)
		{
			nearRay = ray;
		}
	}
	ray = nearRay;
}

//円の円との当たり判定
bool Collision::SphereVsSphere(const VECTOR3& posA, const float& weghtA, const float& radiusA, const VECTOR3& posB, const float& weghtB, const float& radiusB, VECTOR3& outPosA,VECTOR3& outPosB)
{
	VECTOR3  vec = posB-posA;
	XMVECTOR Vec = XMLoadFloat3(&vec);
	//押し出す方向
	XMVECTOR N_Vec = XMVector3Normalize(Vec);
	Vec = XMVector3Length(Vec);
	float L;
	XMStoreFloat(&L, Vec);

	//もし当たっていたなら
	if (radiusA + radiusB >= L)
	{
		//重さを考慮する
		float weghtARatio = (weghtB / (weghtA + weghtB))*(L-(radiusA + radiusB));
		float weghtBRatio = (weghtA / (weghtA + weghtB))*(L-(radiusA + radiusB));
		
		//PosAの移動計算
			XMVECTOR MoveVec = XMVectorScale(N_Vec, weghtARatio);
			VECTOR3 V;
			XMStoreFloat3(&V, MoveVec);
			outPosA = V + posA;
			outPosA.y = posA.y;

		//PosBの移動計算
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
