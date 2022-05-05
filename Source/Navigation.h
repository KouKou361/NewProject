#pragma once
#include "Lib.h"
#include <queue>
#include <stack>

class NavEdge;

//ナビモデルの一つあたりのポリゴン情報
class NavPolygonData
{
public:
	//ポリゴンの三点の位置
	VECTOR3 pos[3] = {};
};

//ポリゴンとポリゴンを繋ぐノード
//(経路探索する時に、辿っていったポリゴンを保存するノード)
class NavNode
{
public:
	NavEdge* nextNavMesh=nullptr;
	float length=0;//自分の重心から相手の重心までの距離
	
};


class NavEdge
{
public:
	bool searchflg = false;//探索フラグ
	VECTOR3 centerPos = {};
	vector<VECTOR3>positions;
	//子供ノード
	vector<NavNode*> navNodes;
	//親のエッジ(探索する時に使う)
	NavEdge* parent=nullptr;

	//既にNacNodesに登録されているノードかどうか
	bool EdgeDuplicate(NavEdge* edge);
};

//経路探索する目標データ
class NavTargetData
{
public:
	//ナビメッシュでいけるフラグ
	bool NavgasionPossibleFlg = false;//（	//true：目標は経路探索で辿り着ける。  false：目標は経路探索で辿り着けない。）
	NavEdge* inMesh=nullptr;//目標地点がいるメッシュ
	VECTOR3 pos = {};//目標地点
};

class NavCollision
{
private:
	//地面メッシュ当たり判定
	vector<NavPolygonData>collisionModelsPos;
	//ナビメッシュ
	vector<NavEdge*>navMeshes;
	//スタート位置からボールまでのEdge
	vector<NavEdge*> roatEdge;
	//ターゲットの情報
	NavTargetData *target=nullptr;
public:
	//AIのためのステージ構成
	void NavStageBuild(const int navModelIndex);

	//テスト用
	void Render();

	//全消し
	void Clear();

	//ターゲットの設定
	void SetTarget(const VECTOR3& pos, const VECTOR3& pos2);

	//経路探索（メッシュ単位で）
	void SearchRoat(NavEdge*& start, NavEdge*& end);

	//NavEdgeから実際の距離の算出
	bool CreateNearVectol(const VECTOR3 position, const VECTOR3 target, VECTOR3& outPos);

	//レイに当たったナビメッシュの取得
	bool GetOnNavMeshToRayPick(const VECTOR3& pos, const VECTOR3& pos2, NavEdge*& mesh);

	//目標の取得
	inline NavTargetData* GetNavTarget() { return target; }
private:

	//次のメッシュに面していない頂点の算出
	void GetNotContact(const NavEdge* edge, const NavEdge* nextedge, VECTOR3& OutPosition);

	//次のメッシュに面している頂点の算出
	void GetContactPos(const NavEdge* edge, const NavEdge* nextedge, VECTOR3* posision);

	//外積
	void Cross(const VECTOR3& v, const VECTOR3& v2, VECTOR3& outv);

	//ゆとりを持たせる
	void ClearRoomPos(const VECTOR3 ownerPos, const VECTOR3 goalPos,   VECTOR3& outPos);

	//経路探索の探索済みを消す
	void ClearNavEdgeSearch();

	//二つのベクトルの間にTposがいるかどうかの判定
	bool InPosition(const VECTOR3& rpos, const VECTOR3& pos1, const VECTOR3& pos2, const VECTOR3& tpos);

	//
	bool rayVsray2D(const VECTOR3 posA1, const VECTOR3 posA2, const VECTOR3 posB1, const VECTOR3 posB2);

	//二つのエッジの頂点がどれか接触していたならtrueを返す
	bool Contant(NavEdge*& edge1, NavEdge*& edge2);

	//二つのベクトルの間の角度の算出
	float GetAngle(const VECTOR3& rpos, const VECTOR3& pos1, const VECTOR3& pos2 );

	//======================================
	//SearchRoat関数で必要な関数
	//====================================== 
	
	//ローカル空間からワールド座標
	void NavModelLocalToWorld(const int navModelIndex);

	//メッシュ配列の作成
	void CreateNavMeshes();

	//隣のメッシュの関連ずけ
	void RelatedToNextMesh();

	//ダイクストラ法で目標の算出
	void DijkstraMesh(std::queue<NavEdge*>& queue, NavEdge*& nowEdge, NavEdge* GoalEdge);

	//経路探索した後に、スタートからゴールまで辿る。
	void PursueNavMesh(std::stack<NavEdge*>& stack, NavEdge*& nowEdge, const NavEdge* startEdge);

	//stackデータから経路探索したナビメッシュを入れる配列に入れる
	void SetRoatEdge(std::stack<NavEdge*>& stack);

	//======================================
	//CreateNearRoat関数で必要な関数
	//====================================== 
	
	//赤線と青線が逆の並びになっていたら正しい方に並び替える
	void RearrangesPosition(VECTOR3 &Pos1, VECTOR3& Pos2,VECTOR3 originPos,const NavEdge* edge, const NavEdge* nextedge, VECTOR3& OutPosition);

	//ナビメッシュ角の算出
	void SearchCorner(NavEdge* edge, NavEdge* nextedge, VECTOR3& notContctPosition, VECTOR3& pos1, VECTOR3& pos2, const VECTOR3& originPos, VECTOR3& anwer);
};