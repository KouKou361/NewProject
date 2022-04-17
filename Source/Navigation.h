#pragma once
#include "Lib.h"
class NavEdge;

//ナビモデルのメッシュ情報
class NavCollisionNode
{
public:
	VECTOR3 pos[3];
};


//ノード
class NavNode
{
public:
	NavEdge* nextNavMesh;
	float length;//自分の重心から相手の重心までの距離
	
};
class NavEdge
{
public:
	bool searchflg = false;//探索フラグ
	VECTOR3 centerPos;
	vector<VECTOR3>positions;
	//子供ノード
	vector<NavNode*> navNodes;
	//親のエッジ(探索する時に使う)
	NavEdge* parent;

	//既にNacNodesに登録されているノードかどうか
	bool EdgeDuplicate(NavEdge* edge);
};
class NavTarget
{
public:
	bool function;
	NavEdge* inMesh;
	VECTOR3 position;
};


class NavCollision
{
private:
	//地面メッシュ当たり判定
	vector<NavCollisionNode>collisionModelsPos;
	//ナビメッシュ
	vector<NavEdge*>navMeshes;
	//スタート位置からボールまでのEdge
	vector<NavEdge*> roatEdge;
	//ターゲットの情報
	NavTarget *target;
public:
	//AIのためのステージ構成
	void NavStageBuild(const int navModelIndex);
	//テスト用
	void Render();
	//全消し
	void Clear();
	//ターゲットの設定
	void SetTarget(const VECTOR3& pos, const VECTOR3& pos2);
	//経路探索の探索済みを消す
	void ClearNavEdgeSearch();
	//次のメッシュに面していない頂点の算出
	void GetNotContact(NavEdge* edge, NavEdge* nextedge, VECTOR3& outPosition);
	//次のメッシュに面している頂点の算出
	void GetContactPos(const NavEdge* edge, const NavEdge* nextedge, VECTOR3* posision);
	//経路探索（メッシュ単位で）
	void SearchRoat(NavEdge*& start, NavEdge*& end);
	//外積
	void Cross(const VECTOR3& v, const VECTOR3& v2, VECTOR3& outv);
	//ゆとりを持たせる
	void ClearRoomPos(const VECTOR3 ownerPos, const VECTOR3 goalPos,   VECTOR3& outPos);
	//NavEdgeから実際の距離の算出
	bool CreateNearRoat(const VECTOR3 position, const VECTOR3 target,  VECTOR3 &outPos);
	//レイに当たったナビメッシュの取得
	bool GetOnNacMesh(const VECTOR3& pos, const VECTOR3& pos2, NavEdge*& mesh);
	//二つのベクトルの間にTposがいるかどうかの判定
	bool InPosition(const VECTOR3& rpos, const VECTOR3& pos1, const VECTOR3& pos2, const VECTOR3& tpos);
	//
	bool rayVsray2D(const VECTOR3 posA1, const VECTOR3 posA2, const VECTOR3 posB1, const VECTOR3 posB2);
	//二つのエッジの頂点がどれか接触していたならtrueを返す
	bool Contant(NavEdge*& edge1, NavEdge*& edge2);
	//二つのベクトルの間の角度の算出
	float GetAngle(const VECTOR3& rpos, const VECTOR3& pos1, const VECTOR3& pos2 );

	inline NavTarget* GetNavTarget() { return target;}
};