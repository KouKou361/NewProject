#include "Navigation.h"
#include <queue>
#include <stack>


//既に登録されているノードかどうか
bool NavEdge::EdgeDuplicate(NavEdge* edge)
{
	for (NavNode* Node : navNodes)
	{
		if (edge == Node->nextNavMesh)
		{
			//既に登録されている
			return true;
		}
	}
	//登録されていない
	return false;

}

//AIのためのステージ構成
void NavCollision::NavStageBuild(int navModelIndex)
{
	//経路探索する目標データ
	target = new NavTargetData();

	//モデルをローカル空間からワールド座標に変換
	NavModelLocalToWorld(navModelIndex);

	//ナビメッシュ配列の作成
	CreateNavMeshes();

	//隣のナビメッシュの関連ずけ
	RelatedToNextMesh();

}

//エッジの経路探索（第一引数:ナビメッシュのスタート、第２引数:ナビメッシュのゴール）
void NavCollision::SearchRoat(NavEdge*& Start, NavEdge*& End)
{
	//もしターゲットが全てのNavEdge内にはいないなら
	if (target->NavgasionPossibleFlg == false)return;

	//探索候補のデータ
	std::queue<NavEdge*> queue;

	//現在位置のEdge
	NavEdge* nowEdge = nullptr;

	//探索候補のデータ
	std::stack<NavEdge*> stack;



	//最初の地点を設定
	queue.push(Start);

	//経路探索の探索済みを消して初期化
	ClearNavEdgeSearch();

	//ダイクストラ法で目標地点までポリゴン単位で算出していく。
	DijkstraMesh(queue,nowEdge, End);

	//経路探索した後に、スタートからゴールまで辿る。
	PursueNavMesh(stack, nowEdge, Start);
	
	//stackデータから経路探索したナビメッシュを入れる配列に入れる
	SetRoatEdge(stack);
	
}

//NavEdgeから実際の距離の算出（第一引数:スタートする位置、第二引数:ゴールする位置,第三引数:答え）
bool NavCollision::CreateNearVectol(const VECTOR3 Position, const VECTOR3 Target, VECTOR3& OutVectol)
{
	//もしターゲットが全てのNavEdge内にはいないなら
	if (target->NavgasionPossibleFlg == false)return false;

	//とりあえず 同じマスならreturn;
	if (roatEdge.size() <= 1) {
		OutVectol = Target;
		return true;
	}
	//２つエッジが面している頂点
	VECTOR3 ContantPos[2];

	//２つエッジが面している頂点とPositionのベクトル
	VECTOR3 Vcontant[2];

	//２つエッジが面していない
	VECTOR3 NotContctPosition;

	//２つエッジが面していない頂点とPositionのベクトル
	VECTOR3 VNotContctPosition;

	//最短距離に進むためのベクトル（答え）
	VECTOR3 V_Answer = Target;

	//エッジデータの算出
	NavEdge* edge = roatEdge.at(0);
	NavEdge* Nextedge = roatEdge.at(1);

	//static int degugIndex = 0;

	//ImGui::Begin("aaaa");
	//ImGui::InputInt("Test", &degugIndex);
	//ImGui::End();

	//２つエッジが面している頂点の算出
	GetContactPos(edge, Nextedge, ContantPos);

	//次のメッシュに面していない頂点の算出
	GetNotContact(edge, Nextedge, NotContctPosition);

	//もし赤線と青線が逆なら並び変える（逆なら都合が悪い）
	RearrangesPosition(ContantPos[0], ContantPos[1], Position, edge, Nextedge, NotContctPosition);

	//ナビメッシュ上での角の算出
	SearchCorner(edge, Nextedge, NotContctPosition, ContantPos[0], ContantPos[1], Position, V_Answer);
	


	if (V_Answer.x + V_Answer.y + V_Answer.z == 0)return false;
	OutVectol = V_Answer;
	return true;

	//Position.y = V_Answer.y;
	//TK_Lib::Debug3D::Line(Position, V_Answer, { 1,0,0,1 });




}

//テスト用
void NavCollision::Render()
{
	//経路探索の可視化
	for (int i = 0; i < roatEdge.size(); i++)
	{
		NavEdge* edge = roatEdge.at(i);
		VECTOR3 Pos1 = { edge->positions.at(0).x,edge->positions.at(0).y +0.5f ,edge->positions.at(0).z };
		VECTOR3 Pos2 = { edge->positions.at(1).x,edge->positions.at(1).y +0.5f ,edge->positions.at(1).z };
		VECTOR3 Pos3 = { edge->positions.at(2).x,edge->positions.at(2).y +0.5f ,edge->positions.at(2).z };

		TK_Lib::Debug3D::Line(Pos1, Pos2, { 0,0,1,1 });
		TK_Lib::Debug3D::Line(Pos2, Pos3, { 0,0,1,1 });
		TK_Lib::Debug3D::Line(Pos3, Pos1, { 0,0,1,1 });
	}

	for (NavPolygonData node : collisionModelsPos)
	{
		VECTOR3 Pos1 = { node.pos[0].x,node.pos[0].y + 0.3f ,node.pos[0].z };
		VECTOR3 Pos2 = { node.pos[1].x,node.pos[1].y + 0.3f ,node.pos[1].z };
		VECTOR3 Pos3 = { node.pos[2].x,node.pos[2].y + 0.3f ,node.pos[2].z };

		TK_Lib::Debug3D::Line(Pos1, Pos2, { 0,0,0,1 });
		TK_Lib::Debug3D::Line(Pos2, Pos3, { 0,0,0,1 });
		TK_Lib::Debug3D::Line(Pos3, Pos1, { 0,0,0,1 });
	}
	//for (const NavEdge* nacMesh : NacMeshes)
	//{
	//	//if (test == NacMeshes.size() - 1)return;
	//	//	test++;
	//	for (int index = 0; index < nacMesh->Positions.size();index++)
	//	{
	//		int nextIndex = index+1;
	//		if (index == nacMesh->Positions.size()-1)
	//		{
	//			//break;
	//			nextIndex = 0;
	//		}
	//		VECTOR3 Pos1 = { nacMesh->Positions.at(index).x,nacMesh->Positions.at(index).y + 0.1f ,nacMesh->Positions.at(index).z };
	//		VECTOR3 Pos2 = { nacMesh->Positions.at(nextIndex).x,nacMesh->Positions.at(nextIndex).y + 0.1f ,nacMesh->Positions.at(nextIndex).z };
	//		TK_Lib::Debug3D::Line(Pos1, Pos2, VECTOR4(0, 1, 0, 1));
	//	}
	////	TK_Lib::Debug3D::Circle(nacMesh.Positions.at(0), 0.1);
	////	TK_Lib::Debug3D::Circle(nacMesh.Positions.at(1), 0.1);
	//}
	//
}
//ターゲットの設定
void NavCollision::SetTarget(const VECTOR3& Pos, const VECTOR3& Pos2)
{
	//ここではターゲットがいるポリゴンの算出している
	target->NavgasionPossibleFlg = GetOnNavMeshToRayPick(Pos, Pos2, target->inMesh);
	//位置の更新
	target->pos = Pos;
}


//=======================================================================
//ここから下のコードは経路探索クラスの内部関数であり、基本的にNavCollison関数のみでしかしようしていない(そのためprivate化している)
//また数学（内積や外積）やダイクストラ法などをしようしていて、非常に難解なコードになっている。
//それを補うコメントアウト（文字のみ）で説明するのに限界を感じた。 
//そこで、ざっくりとであるがこのゲームプロジェクトファイルの[プログラムの仕様書]ファイルがあると思う。
//そこに説明を補うことにする。
// （関数の説明ではなく、経路探索の流れと大雑把な説明）
//=======================================================================



//経路探索の探索済みを消す
void NavCollision::ClearNavEdgeSearch()
{
	for (NavEdge* Edge : navMeshes)
	{
		Edge->searchflg = false;
		Edge->parent = nullptr;
	}
}


//次のポリゴンに面していない頂点の算出
void NavCollision::GetNotContact(const NavEdge* edge, const NavEdge* nextedge, VECTOR3& OutPosition)
{
	//面していない頂点の算出
	for (VECTOR3 pos1 : nextedge->positions)
	{
		bool flg = false;
		for (VECTOR3 pos2 : edge->positions)
		{
			//面している！
			if (pos1 == pos2)
			{
				flg = true;
				break;
			}
		}
		//面していないなら
		if (flg == false)
		{
			OutPosition = pos1;
			break;
		}
	}
}
//二つのベクトルの間にTposがいるかどうかの判定
bool NavCollision::InPosition(const VECTOR3 &Rpos, const VECTOR3& Pos1, const VECTOR3& Pos2, const VECTOR3& Tpos)
{

	XMVECTOR R = DirectX::XMLoadFloat3(&Rpos);
	XMVECTOR A = DirectX::XMLoadFloat3(&Pos1);
	XMVECTOR B = DirectX::XMLoadFloat3(&Pos2);
	XMVECTOR T = DirectX::XMLoadFloat3(&Tpos);
	//Rからみてのベクトルを計算する
	XMVECTOR RA = XMVector3Normalize(XMVectorSubtract(A, R));
    XMVECTOR RB = XMVector3Normalize(XMVectorSubtract(B, R));
    XMVECTOR RT = XMVector3Normalize(XMVectorSubtract(T, R));
	//法線の取得
	XMVECTOR Normal= XMVector3Normalize(XMVector3Cross(RA, RB));

	XMVECTOR Dot;
	float dot;
	XMVECTOR Cross;
	//1
	{
		Cross = XMVector3Cross(RA,RT);
		Cross = XMVector3Normalize(Cross);
		Dot = XMVector3Dot(Cross, Normal);
		XMStoreFloat(&dot, Dot);
		if (dot < 0)return false;

	}

	//2
	{
		Cross = XMVector3Cross(RT, RB);
		Cross = XMVector3Normalize(Cross);
		Dot = XMVector3Dot(Cross, Normal);
		XMStoreFloat(&dot, Dot);
		if (dot < 0)return false;

	}
	return true;

	
	
}


//二つのベクトルの間の角度の算出
float NavCollision::GetAngle(const VECTOR3& Rpos, const VECTOR3& pos1, const VECTOR3& pos2)
{
	VECTOR3 V[2];
	XMVECTOR Pos[2];
	XMVECTOR Dot;
	float dot;
	V[0] = pos1 - Rpos;
	V[1] = pos2 - Rpos;
	//二つのベクトルの角度の算出
	Pos[0] = XMLoadFloat3(&V[0]);
	Pos[1] = XMLoadFloat3(&V[1]);
	Pos[0] = XMVector3Normalize(Pos[0]);
	Pos[1] = XMVector3Normalize(Pos[1]);
	Dot = XMVector3Dot(Pos[0], Pos[1]);
	XMStoreFloat(&dot, Dot);
	return dot;
}

//次のメッシュに面している頂点の算出
void NavCollision::GetContactPos(const NavEdge* edge, const NavEdge* Nextedge,  VECTOR3 *Posision)
{
	int ret = 0;
	for (VECTOR3 pos1 : Nextedge->positions)
	{
		bool flg = false;
		for (VECTOR3 pos2 : edge->positions)
		{
			//面している！
			if (pos1 == pos2)
			{
				Posision[ret] = pos1;
				ret++;
				break;
			}
		}
	}
}
//全消し
void NavCollision::Clear()
{
	if (target != nullptr)
	{
		delete target;
		target = nullptr;
	}
	collisionModelsPos.clear();
	for (NavEdge* mesh : navMeshes)
	{
		for (NavNode* node : mesh->navNodes)
		{
			if (node)
			{
				delete node;
				node = nullptr;
			}
		}
		if (mesh)
		{
			delete mesh;
			mesh = nullptr;
		}
	}

	navMeshes.clear();
}
void NavCollision::Cross(const VECTOR3& V, const VECTOR3& V2, VECTOR3 &OutV)
{
	//二つのベクトルの垂直ベクトルの算出
	XMVECTOR Cross, Pos1, Pos2;
	Pos1 = XMLoadFloat3(&V);
	Pos2 = XMLoadFloat3(&V2);
	Cross = XMVector3Cross(Pos1, Pos2);
	XMStoreFloat3(&OutV, Cross);
}
//二つのエッジの頂点がどれか接触していたならtrueを返す
bool NavCollision::Contant(NavEdge*& edge1, NavEdge*& edge2)
{
	for (VECTOR3 pos1 : edge1->positions)
	{
		for (VECTOR3 pos2 : edge2->positions)
		{
			if (pos1 == pos2) {
				return true;
			}
		}
	}
	return false;
}

//ゆとりを持たせる
void NavCollision::ClearRoomPos(const VECTOR3 ownerPos, const VECTOR3 GoalPos,  VECTOR3 &OutPos)
{
	//ゆとり
	constexpr float Volume = 1.1f;
	VECTOR3 vec1, vec2;
	vec1= target->pos - ownerPos;//スタートとTargetのベクトル
	vec2= GoalPos - ownerPos;//スタートとゴールのベクトル

	//TK_Lib::Debug3D::Line(target->Position , ownerPos);
	//TK_Lib::Debug3D::Line(GoalPos, ownerPos, {0,1,0,1});
	//角から距離を持たせたい

	//
	XMVECTOR LPos;
	{
		XMVECTOR Vec1, Vec2, N_Vec1, N_Vec2;
		

		Vec1 = XMLoadFloat3(&vec1);
		Vec2 = XMLoadFloat3(&vec2);

		N_Vec1 = XMVector3Normalize(Vec1);
		N_Vec2 = XMVector3Normalize(Vec2);
		XMVECTOR V=XMVector3Dot(N_Vec1, Vec2);
	//	V = XMVector3Length(V);
		float L;
		XMStoreFloat(&L,V);

		LPos=XMVectorScale(N_Vec1,L);
		LPos = XMVectorAdd(LPos, XMLoadFloat3(&ownerPos));

	}

	//
	XMVECTOR Goal= XMLoadFloat3(&GoalPos);

	XMVECTOR VolumeVec;
	{
		XMVECTOR Vec;
		Vec = XMVectorSubtract(Goal, LPos);
		XMVECTOR NVec = XMVector3Normalize(Vec);

		VolumeVec = XMVectorScale(NVec, Volume);
	}

	VECTOR3 Answer; 
	XMStoreFloat3(&Answer, VolumeVec );
	Answer = Answer + GoalPos;
	Answer.y = GoalPos.y;

	OutPos = Answer;

	//TK_Lib::Debug3D::Line(GoalPos, Answer, {0,0,1,1});
	
	




}
bool NavCollision::rayVsray2D(VECTOR3 Pos, VECTOR3 Pos2, VECTOR3 pos, VECTOR3 pos2 )
{
	VECTOR3 AB = Pos2- Pos;
	VECTOR3 AC = pos - Pos;
	VECTOR3 AD = pos2 - Pos;

	AB.y = AB.z;
	AC.y = AC.z;
	AD.y = AD.z;

	XMVECTOR V_AB = XMLoadFloat3(&AB);
	XMVECTOR V_AC = XMLoadFloat3(&AC);
	XMVECTOR V_AD = XMLoadFloat3(&AD);

	XMVECTOR Cross=XMVector2Cross(V_AB,V_AC);
	XMVECTOR cross = XMVector2Cross(V_AB, V_AD);
	float _Cross;
	float _cross;
	XMStoreFloat(&_Cross, Cross);
	XMStoreFloat(&_cross, cross);
	if (_Cross * _cross)
	{
		return true;
	}
	return false;
}

//ローカル空間からワールド座標
void NavCollision::NavModelLocalToWorld(const int navModelIndex)
{
	const std::shared_ptr<ModelResource> model = TK_Lib::Model::GetModels().at(navModelIndex);

	for (const ModelResource::Mesh& mesh : model->GetMeshes())
	{
		const std::vector<ModelResource::Vertex>& vetices = mesh.vertices;
		const std::vector<UINT> indices = mesh.indices;

		//メッシュノード取得
		const ModelResource::NodeTest& node = model->GetNodetest().at(mesh.nodeIndex);

		//レイをワールド空間かわローカル空間に変換する
		XMMATRIX WorldTranceform = XMLoadFloat4x4(&node.worldTransform);
		XMMATRIX InverseWorldTranceform = XMMatrixInverse(nullptr, WorldTranceform);
		//ローカル空間
		//V_Up = XMVector3TransformNormal(V_Up, InverseWorldTranceform);

		int materialIndex = -1;
		//XMVECTOR HitPosition;
		//XMVECTOR HitNormalize;
		//XMVECTOR PolygonPostion[3];
		NavPolygonData stageNode;

		for (const ModelResource::Subset& subset : mesh.subsets)
		{
			for (UINT i = 0; i < subset.indexCount; i += 3)
			{

				UINT index = subset.startIndex + i;
				//三角形の頂点情報を算出する
				const ModelResource::Vertex& a = vetices.at(indices.at(index));
				const int indexB = index + 1;
				const int indexC = index + 2;


				const ModelResource::Vertex& b = vetices.at(indices.at(indexB));
				const ModelResource::Vertex& c = vetices.at(indices.at(indexC));



				XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
				XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
				XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

				// //三角形の三辺ベクトルを算出
				// XMVECTOR AB = XMVectorSubtract(B, A);
				// XMVECTOR BC = XMVectorSubtract(C, B);
				// XMVECTOR CA = XMVectorSubtract(A, C);
				// //三角形の法線ベクトルの算出
				// XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(AB, BC));
				// // XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(BC,AB));
				// //内積の値がプラスなら裏向き
				// XMVECTOR Dot = XMVector3Dot(V_Up, Normal);
				// float dot;
				// XMStoreFloat(&dot, Dot);
				// //if (dot != 0)continue;//裏向き
				// dot = acosf(dot);
				// //if (dot >=XMConvertToRadians(40))continue;//裏向き

				XMVECTOR WorldPolygonPostion[3];
				WorldPolygonPostion[0] = XMVector3TransformCoord(A, WorldTranceform);
				WorldPolygonPostion[1] = XMVector3TransformCoord(B, WorldTranceform);
				WorldPolygonPostion[2] = XMVector3TransformCoord(C, WorldTranceform);

				VECTOR3 WorldPostion[3];
				XMStoreFloat3(&stageNode.pos[0], WorldPolygonPostion[0]);
				XMStoreFloat3(&stageNode.pos[1], WorldPolygonPostion[1]);
				XMStoreFloat3(&stageNode.pos[2], WorldPolygonPostion[2]);



				collisionModelsPos.push_back(stageNode);
			}

		}
	}
}

//メッシュ配列の作成
void NavCollision::CreateNavMeshes()
{
	for (int i = 0; i <= collisionModelsPos.size(); i++)
	{

		if (i >= collisionModelsPos.size())break;

		NavEdge* navEdge = new NavEdge();

		VECTOR3 Pos1 = collisionModelsPos.at(i).pos[0];
		VECTOR3 Pos2 = collisionModelsPos.at(i).pos[1];
		VECTOR3 Pos3 = collisionModelsPos.at(i).pos[2];


		//	VECTOR3 Pos4 = CollisionModelsPos.at(i+1).Pos[1];
		//	if (InPosition(Pos1, Pos2, Pos3, Pos4))
		{//重心の算出
			navEdge->centerPos = (Pos1 + Pos2 + Pos3) / 3;
			navEdge->positions.push_back(Pos1);
			navEdge->positions.push_back(Pos2);
			//	nacMesh->Positions.push_back(Pos4);
			navEdge->positions.push_back(Pos3);
		}




		navMeshes.push_back(navEdge);
		//	break;

	}
}

//隣のメッシュの関連ずけ
void NavCollision::RelatedToNextMesh()
{
	//隣のメッシュの関連ずけ
	for (NavEdge* navEdge : navMeshes)
	{
		for (NavEdge* navEdge2 : navMeshes)
		{
			if (navEdge == navEdge2)continue;

			//基準となるメッシュ
			for (int i = 0; i < navEdge->positions.size(); i++)
			{
				//関連となるメッシュ
				for (int j = 0; j < navEdge2->positions.size(); j++)
				{
					//一点が連なっている！
					if (navEdge->positions.at(i) == navEdge2->positions.at(j))
					{
						VECTOR3 Duplicate = navEdge->positions.at(i);
						//２点とも連なっているかどうか	
						for (int k = 0; k < navEdge->positions.size(); k++)
						{
							if (Duplicate == navEdge->positions.at(k))continue;

							for (int m = 0; m < navEdge2->positions.size(); m++)
							{
								if (navEdge->positions.at(k) == navEdge2->positions.at(m))
								{
									//既に登録されているかどうか
									if (navEdge->EdgeDuplicate(navEdge2))break;

									NavNode* navNode = new NavNode();
									navNode->nextNavMesh = navEdge2;
									XMVECTOR A = XMLoadFloat3(&navEdge->centerPos);
									XMVECTOR B = XMLoadFloat3(&navEdge2->centerPos);
									XMVECTOR Length = XMVector3Length(XMVectorSubtract(A, B));
									XMStoreFloat(&navNode->length, Length);
									navEdge->navNodes.push_back(navNode);
								}

							}

						}

					}
				}

			}

		}

	}
}


//レイに当たったナビメッシュの取得
bool NavCollision::GetOnNavMeshToRayPick(const VECTOR3& Pos, const VECTOR3& Pos2, NavEdge*& mesh)
{
	//TK_Lib::Debug3D::Line(Pos, Pos2, VECTOR4(0, 1, 0, 1));

	XMVECTOR Start = XMLoadFloat3(&Pos);
	XMVECTOR End = XMLoadFloat3(&Pos2);

	XMVECTOR Vec = XMVectorSubtract(End, Start);
	XMVECTOR Dir = XMVector3Normalize(Vec);
	XMVECTOR Length = XMVector3Length(Vec);
	//レイの長さ
	float neart;
	XMStoreFloat(&neart, Length);


	//最短距離
	float NearL = FLT_MAX;
	//最短距離のエッジ
	NavEdge* SaveEdge = nullptr;

	for (NavEdge* navEdge : navMeshes)
	{

		XMVECTOR A = DirectX::XMLoadFloat3(&navEdge->positions.at(0));
		XMVECTOR B = DirectX::XMLoadFloat3(&navEdge->positions.at(1));
		XMVECTOR C = DirectX::XMLoadFloat3(&navEdge->positions.at(2));

		for (int i = 0; i < 3; i++)
		{
			VECTOR3 P = navEdge->positions.at(i) - Pos;
			XMVECTOR V = XMLoadFloat3(&P);
			V = XMVector3Length(V);
			float NL;
			XMStoreFloat(&NL, V);
			if (NearL >= NL)
			{
				NearL = NL;
				SaveEdge = navEdge;

			}

		}


		//三角形の三辺ベクトルを算出
		XMVECTOR AB = XMVectorSubtract(B, A);
		XMVECTOR BC = XMVectorSubtract(C, B);
		XMVECTOR CA = XMVectorSubtract(A, C);
		//三角形の法線ベクトルの算出
		XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(AB, BC));
		//XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(BC,AB));
		//内積の値がプラスなら裏向き
		XMVECTOR Dot = XMVector3Dot(Dir, Normal);
		float dot;
		XMStoreFloat(&dot, Dot);
		if (dot >= 0)continue;//裏向き

		//レイと平面の交差点
		XMVECTOR d1 = XMVector3Dot(XMVectorSubtract(A, Start), Normal);
		//XMVECTOR d2 = XMVector3Dot(Normal, Dir);
		XMVECTOR T = XMVectorDivide(d1, Dot);
		float t;
		XMStoreFloat(&t, T);
		//交点までの距離が今までに計算した最近距離よりも大きいときはスキップ
		if (t<0.0f || t>neart)continue;
		XMVECTOR Position = XMVectorMultiply(Dir, T);
		Position = XMVectorAdd(Position, Start);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, Position);

		//交点が三角形の内側にあるか判定
				//1
		{
			XMVECTOR V1 = XMVectorSubtract(Position, A);
			XMVECTOR Cross = XMVector3Cross(AB, V1);
			//	XMVECTOR Cross = XMVector3Cross(V1,AB);
			XMVECTOR Dot1 = XMVector3Dot(Cross, Normal);
			float dot1;
			XMStoreFloat(&dot1, Dot1);
			if (dot1 < 0)continue;
		}

		//2
		{
			XMVECTOR V2 = XMVectorSubtract(Position, B);
			XMVECTOR Cross2 = XMVector3Cross(BC, V2);
			//XMVECTOR Cross2 = XMVector3Cross(V2, BC);
			XMVECTOR Dot2 = XMVector3Dot(Cross2, Normal);
			float dot2;
			XMStoreFloat(&dot2, Dot2);
			if (dot2 < 0)continue;

		}


		//3
		{
			XMVECTOR V3 = XMVectorSubtract(Position, C);
			XMVECTOR Cross3 = XMVector3Cross(CA, V3);
			//XMVECTOR Cross3 = XMVector3Cross(V3,CA );
			XMVECTOR Dot3 = XMVector3Dot(Cross3, Normal);
			float dot3;
			XMStoreFloat(&dot3, Dot3);
			if (dot3 < 0)continue;

		}
		mesh = navEdge;

		return true;

	}
	mesh = SaveEdge;

	return true;
}

//ダイクストラ法で目標の算出
void NavCollision::DijkstraMesh(std::queue<NavEdge*>& queue, NavEdge*& nowEdge, NavEdge* GoalEdge)
{
	//経路探索(ダイクストラ法)
	while (!queue.empty())
	{
		//スタックに詰まれたエッジデータを取り出し
		nowEdge = queue.front();
		//削除
		queue.pop();

		//ノードを辿る
		for (NavNode* node : nowEdge->navNodes)
		{
			if (node->nextNavMesh->searchflg)continue;
			//追加
			queue.push(node->nextNavMesh);
			//親の設定（進んだ位置の軌跡を残していく）
			node->nextNavMesh->parent = nowEdge;
			//探索したフラグ
			node->nextNavMesh->searchflg = true;

			//	//探索の可視化
			//	VECTOR3 Pos1 = { nowEdge->Positions.at(0).x,nowEdge->Positions.at(0).y + 0.2f ,nowEdge->Positions.at(0).z };
			//			VECTOR3 Pos2 = { nowEdge->Positions.at(1).x,nowEdge->Positions.at(1).y + 0.2f ,nowEdge->Positions.at(1).z };
			//			VECTOR3 Pos3 = { nowEdge->Positions.at(2).x,nowEdge->Positions.at(2).y + 0.2f ,nowEdge->Positions.at(2).z };
			//	
			//			TK_Lib::Debug3D::Line(Pos1, Pos2, { 0,0,1,1 });
			//			TK_Lib::Debug3D::Line(Pos2, Pos3, { 0,0,1,1 });
			//			TK_Lib::Debug3D::Line(Pos3, Pos1, { 0,0,1,1 });
		}

		//目的地に到着！
		if (nowEdge == GoalEdge)break;//終了


	}
}

//経路探索した後に、スタートからゴールまで辿る。
void NavCollision::PursueNavMesh(std::stack<NavEdge*>& stack, NavEdge*& nowEdge, const NavEdge* startEdge)
{
	

	while (true)
	{

		stack.push(nowEdge);
		if (nowEdge == startEdge)break;
		if (nowEdge)
		{
			//ひとつ前のエッジに戻る。
			nowEdge = nowEdge->parent;
		}


	}
}
//stackデータから経路探索したナビメッシュを入れる配列に入れる
void NavCollision::SetRoatEdge(std::stack<NavEdge*>& stack)
{
	int size = static_cast<int>(stack.size());
	roatEdge.clear();

	for (int i = 0; i < size; i++)
	{
		NavEdge* edge = stack.top();
		stack.pop();

		roatEdge.push_back(edge);

		//VECTOR3 Pos1 = { edge->Positions.at(0).x,edge->Positions.at(0).y + 0.4f ,edge->Positions.at(0).z };
		//VECTOR3 Pos2 = { edge->Positions.at(1).x,edge->Positions.at(1).y + 0.4f ,edge->Positions.at(1).z };
		//VECTOR3 Pos3 = { edge->Positions.at(2).x,edge->Positions.at(2).y + 0.4f ,edge->Positions.at(2).z };

		//TK_Lib::Debug3D::Line(Pos1, Pos2, { 0,0,0,1 });
		//TK_Lib::Debug3D::Line(Pos2, Pos3, { 0,0,0,1 });
		//TK_Lib::Debug3D::Line(Pos3, Pos1, { 0,0,0,1 });

	}


	//	Start = nowEdge;
}

// 赤線と青線が逆の並びになっていたら正しい方に並び替える
void NavCollision::RearrangesPosition(VECTOR3 & Pos1, VECTOR3 & Pos2, VECTOR3 originPos, const NavEdge * edge, const NavEdge * nextedge, VECTOR3 & OutPosition)
{
	VECTOR3 c;
	Cross(Pos2 - originPos, Pos1 - originPos, c);
	if (c.y > 0)
	{
		//並び替え
		c = Pos1;
		Pos1 = Pos2;
		Pos2 = c;
		//次のメッシュに面していない頂点の算出
		GetNotContact(edge, nextedge, OutPosition);

	}
}

//ナビメッシュ角の算出
void NavCollision::SearchCorner(NavEdge* edge, NavEdge* nextedge,VECTOR3 &notContctPosition, VECTOR3& pos1, VECTOR3& pos2, const VECTOR3 &originPos,VECTOR3& anwer )
{
	//角を見つけるまで算出
	for (int i = 0; i < roatEdge.size() - 1; i++)
	{
		//今と次のメッシュの算出
		edge = roatEdge.at(i);
		const int index = i + 1;
		nextedge = roatEdge.at(index);

		//次のメッシュに面していない頂点の算出
		GetNotContact(edge, nextedge, notContctPosition);

		//位置を適用
		VECTOR3 RedCross, BlueCross, RCross;
		VECTOR3 V_Yellow;
		if (roatEdge.size() - i > 2)
		{
			const int index = i + 2;
			V_Yellow = nextedge->centerPos - roatEdge.at(index)->centerPos;
		}
		else
		{
			V_Yellow = nextedge->centerPos - roatEdge.at(i)->centerPos;
		}


		VECTOR3 V_Green = notContctPosition - edge->centerPos;
		VECTOR3 V_Red = pos1 - edge->centerPos;
		VECTOR3 V_Blue = pos2 - edge->centerPos;

		Cross(V_Yellow, V_Green, RCross);



		//if (degugIndex == i)
		//{
		//	//デバック
		//	{
		//		// //赤
		//		// TK_Lib::Debug3D::Line(edge->centerPos, ContantPos[0], { 1,0,0,1 });
		//		// //青
		//		// TK_Lib::Debug3D::Line(edge->centerPos, ContantPos[1], { 0,0,1,1 });
		//		// //緑
		//		// TK_Lib::Debug3D::Line(edge->centerPos, NotContctPosition, { 0,1,0,1 });
		//		// //黄色
		//		//if (RoatEdge.size()-i >2)
		//		//{
		//		//	TK_Lib::Debug3D::Line(edge->centerPos, RoatEdge.at(i + 2)->centerPos, { 1,1,0,1 });
		//		//}
		//		//else
		//		//{
		//		//	TK_Lib::Debug3D::Line(edge->centerPos, RoatEdge.at(i)->centerPos, { 1,1,0,1 });
		//		//}
		//		// 
		//		////赤
		//		//TK_Lib::Debug3D::Line(Position, ContantPos[0], { 1,0,0,1 });
		//		////青
		//		//TK_Lib::Debug3D::Line(Position, ContantPos[1], { 0,0,1,1 });
		//		//緑
		//		//TK_Lib::Debug3D::Line(Position, NotContctPosition, { 0,1,0,1 });
		//
		//		//ImGui::Begin("aaaa");
		//		//ImGui::Text("Cross=%f", V_Yellow.y);
		//		//ImGui::End();
		//	}
		//}
		VECTOR3 Cr;
		VECTOR3 RVec;
		XMVECTOR NV;
		constexpr float R = 0.5f;

		if (RCross.y <= 0)
		{
			Cross(pos1 - originPos, notContctPosition - originPos, Cr);
			if (Cr.y <= 0)
			{
				RVec = pos1 - edge->centerPos;
				//TK_Lib::Debug3D::Line(ContantPos[0] , edge->centerPos);
				NV = XMLoadFloat3(&RVec);
				NV = XMVector3Normalize(NV);
				NV = XMVectorScale(NV, R);
				XMStoreFloat3(&RVec, NV);

				anwer = pos1 - RVec;
				break;
			}
			//青
			Cross(pos2 - originPos, notContctPosition - originPos, Cr);
			//
			if (Cr.y <= 0)
			{
				pos2 = notContctPosition;
			}
			//CrNotContctPosition

		}
		else
		{
			Cross(pos2 - originPos, notContctPosition - originPos, Cr);
			if (Cr.y >= 0)
			{
				//RVec = ContantPos[1] - Nextedge->centerPos;

				RVec = pos2 - edge->centerPos;
				//TK_Lib::Debug3D::Line(ContantPos[1], edge->centerPos);
				NV = XMLoadFloat3(&RVec);
				NV = XMVector3Normalize(NV);
				NV = XMVectorScale(NV, R);
				XMStoreFloat3(&RVec, NV);

				//	TK_Lib::Debug3D::Line(ContantPos[1], RoatEdge[i]->centerPos);
				anwer = pos1 - RVec;
				break;
			}
			//青
			Cross(pos1 - originPos, notContctPosition - originPos, Cr);
			//
			if (Cr.y >= 0)
			{
				pos1 = notContctPosition;
			}
			//赤
			//ContantPos[0] = NotContctPosition;
		}



	}
}