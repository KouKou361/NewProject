#pragma once
#include "Navigation.h"
using namespace std;
class Actor;
//当たり判定のモデルタイプ
enum ModelCollisionType
{
	COLLISION_MODEL,//レイピックに使うModel
	NAV_MODEL,//キャラクターAIに対するナビModel
};
//当たり判定のモデル
class ModelCollsion
{
public:
	ModelCollisionType type;
	Actor* actorModel;
	int modelIndex;
};
//当たり判クラス
class Collision
{
private:
	//モデルの当たり判定リスト
	vector<ModelCollsion> collisionModels;
	//ナビ判定
	unique_ptr<NavCollision> navCollision;

	static Collision* instance;
	//ちょい上の方からレイをあてるための距離
	static constexpr float rayUP = 3.0f;
	//レイのY方向の終点位置距離
	static constexpr float rayUnder = 3.0f;
public:
	Collision();
	~Collision() {}
	//当たり判定モデルの登録
	void RegisterModel(const int model, const ModelCollisionType type,Actor* actor);
	//ナビメッシュによる到着目標の位置
	void SetTarget(const VECTOR3& pos);
	//レイピック
	void RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray);
	//ぶつかったActorオブジェクトの算出レイピック
	void RayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray,Actor*& actorModel);
	//半径分を考慮したレイピック
	void RadiusRayPick(const VECTOR3& start, const VECTOR3& end, RayOut& ray,float radius);
	//削除
	void Clear();
	//ナビの描画
	void NavRender();
	//当たり判定の描画
	void CollisionRender();
	//AIのためのステージ構成
	void NacStageBuild();
	//当たり判定のモデルの削除
	void DeleteCollisionModel(int model);

	//ナビメッシュによる経路探索
	bool SearchRoat(const VECTOR3& pos, VECTOR3& outPos);
	//円の円との当たり判定
	bool SphereVsSphere(const VECTOR3& posA, const float& weghtA, const float& radiusA, const VECTOR3& posB, const float& weghtB, const float& radiusB, VECTOR3& outPosA, VECTOR3& outPosB);

	//ステージのリスト取得
	inline vector<ModelCollsion> *GetCollisionModels() { return &collisionModels; };

	//インスタンス取得
	static Collision& Instance()
	{
		return *instance;
	}
	

};