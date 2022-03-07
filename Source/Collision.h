#pragma once
#include "Navigation.h"
using namespace std;
class Actor;
//当たり判定のモデルタイプ
enum ModelCollisionType
{
	CollisionModel,//レイピックに使うModel
	NavModel,//キャラクターAIに対するナビModel
};
//当たり判定のモデル
class ModelCollsion
{
public:
	ModelCollisionType type;
	Actor* actorModel;
	int modelIndex;
};

class Collision
{
private:
	//モデルの当たり判定リスト
	vector<ModelCollsion> CollisionModels;
	//ナビ判定
	unique_ptr<NavCollision> navCollision;

	static Collision* instance;
	//ちょい上の方からレイをあてるための距離
	static constexpr float RayUP = 3.0f;
	//レイのY方向の終点位置距離
	static constexpr float RayUnder = 3.0f;
public:
	Collision();
	~Collision() {}
	//当たり判定モデルの登録
	void RegisterModel(const int model, const ModelCollisionType type,Actor* actor);
	//
	bool SearchRoat(const VECTOR3& Pos,VECTOR3 & OutPos);
	//円の円との当たり判定
	bool SphereVsSphere(const VECTOR3& posA, const float& weghtA, const float& radiusA, const VECTOR3& posB, const float& weghtB, const float& radiusB, VECTOR3& outPosA, VECTOR3& outPosB);

	void SetTarget(const VECTOR3& Pos);
	//レイピック
	void RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray);

	//ぶつかったActorオブジェクトの算出レイピック
	void RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray,Actor*& actorModel);

	//半径分を考慮したレイピック
	void RadiusRayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray,float radius);
	//削除
	void Clear();
	//テスト用
	void NavRender();
	void CollisionRender();


	//AIのためのステージ構成
	void NacStageBuild();
	//当たり判定のモデルの削除
	void DeleteCollisionModel(int model);
	//インスタンス取得
	static Collision& Instance()
	{
		return *instance;
	}
	//ステージのリスト取得
	vector<ModelCollsion> *GetCollisionModels() { return &CollisionModels; };
	

};