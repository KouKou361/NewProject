#pragma once
#include "Lib.h"

//ナビモデルのメッシュ情報
class NavCollisionNode
{
public:
	VECTOR3 Pos[3];
};
class NavEdge;
//ノード
class NavNode
{
public:
	NavEdge* NextNavMesh;
	float Length;//自分の重心から相手の重心までの距離
	
};
class NavEdge
{
public:
	bool searchflg = false;//探索フラグ
	VECTOR3 centerPos;
	vector<VECTOR3>Positions;
	//子供ノード
	vector<NavNode*> NacNodes;
	//親のエッジ(探索する時に使う)
	NavEdge* parent;

	//既にNacNodesに登録されているノードかどうか
	bool EdgeDuplicate(NavEdge* edge);
};
class NavTarget
{
public:
	bool function;
	NavEdge* InMesh;
	VECTOR3 Position;
};


class NavCollision
{
private:
	//地面メッシュ当たり判定
	vector<NavCollisionNode>CollisionModelsPos;
	//ナビメッシュ
	vector<NavEdge*>NacMeshes;
	//スタート位置からボールまでのEdge
	vector<NavEdge*> RoatEdge;
	//ターゲットの情報
	NavTarget *target;
public:
	//AIのためのステージ構成
	void NavStageBuild(int navModelIndex);
	//テスト用
	void Render();
	//全消し
	void Clear();
	//NavEdgeから実際の距離の算出
	bool CreateNearRoat(VECTOR3 Position, VECTOR3 Target,VECTOR3 &OutPos);
	//レイに当たったナビメッシュの取得
	bool GetOnNacMesh(const VECTOR3& Pos, const VECTOR3& Pos2, NavEdge*& mesh);
	//二つのベクトルの間にTposがいるかどうかの判定
	bool InPosition(const VECTOR3& Rpos, const VECTOR3& Pos1, const VECTOR3& Pos2, const VECTOR3& Tpos);
	//ターゲットの設定
	void SetTarget(const VECTOR3& Pos, const VECTOR3& Pos2);
	//経路探索の探索済みを消す
	void ClearNavEdgeSearch();
	//次のメッシュに面していない頂点の算出
	void GetNotContact(NavEdge* edge, NavEdge* nextedge, VECTOR3& OutPosition);
	//二つのベクトルの間の角度の算出
	float GetAngle(const VECTOR3& Rpos, const VECTOR3& pos1, const VECTOR3& pos2 );
	//次のメッシュに面している頂点の算出
	void GetContactPos(const NavEdge* edge, const NavEdge* Nextedge, VECTOR3* Posision);

	void SearchRoat(NavEdge*& Start, NavEdge*& End);
	bool rayVsray2D(VECTOR3 Pos, VECTOR3 Pos2, VECTOR3 pos, VECTOR3 pos2 );
	void Cross(const VECTOR3& V, const VECTOR3& V2, VECTOR3 &OutV);
	//二つのエッジの頂点がどれか接触していたならtrueを返す
	bool Contant(NavEdge*& edge1, NavEdge*& edge2);
	
	//このままでは場合によってははみ出る可能性があるので
	//ゆとりを持たせる
	void ClearRoomPos(VECTOR3 ownerPos, VECTOR3 GoalPos, VECTOR3& OutPos);
	NavTarget* GetNavTarget() { 
		return target;
	}
};