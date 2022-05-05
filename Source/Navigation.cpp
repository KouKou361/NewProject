#include "Navigation.h"
#include <queue>
#include <stack>


//���ɓo�^����Ă���m�[�h���ǂ���
bool NavEdge::EdgeDuplicate(NavEdge* edge)
{
	for (NavNode* Node : navNodes)
	{
		if (edge == Node->nextNavMesh)
		{
			//���ɓo�^����Ă���
			return true;
		}
	}
	//�o�^����Ă��Ȃ�
	return false;

}

//AI�̂��߂̃X�e�[�W�\��
void NavCollision::NavStageBuild(int navModelIndex)
{
	//�o�H�T������ڕW�f�[�^
	target = new NavTargetData();

	//���f�������[�J����Ԃ��烏�[���h���W�ɕϊ�
	NavModelLocalToWorld(navModelIndex);

	//�i�r���b�V���z��̍쐬
	CreateNavMeshes();

	//�ׂ̃i�r���b�V���̊֘A����
	RelatedToNextMesh();

}

//�G�b�W�̌o�H�T���i������:�i�r���b�V���̃X�^�[�g�A��Q����:�i�r���b�V���̃S�[���j
void NavCollision::SearchRoat(NavEdge*& Start, NavEdge*& End)
{
	//�����^�[�Q�b�g���S�Ă�NavEdge���ɂ͂��Ȃ��Ȃ�
	if (target->NavgasionPossibleFlg == false)return;

	//�T�����̃f�[�^
	std::queue<NavEdge*> queue;

	//���݈ʒu��Edge
	NavEdge* nowEdge = nullptr;

	//�T�����̃f�[�^
	std::stack<NavEdge*> stack;



	//�ŏ��̒n�_��ݒ�
	queue.push(Start);

	//�o�H�T���̒T���ς݂������ď�����
	ClearNavEdgeSearch();

	//�_�C�N�X�g���@�ŖڕW�n�_�܂Ń|���S���P�ʂŎZ�o���Ă����B
	DijkstraMesh(queue,nowEdge, End);

	//�o�H�T��������ɁA�X�^�[�g����S�[���܂ŒH��B
	PursueNavMesh(stack, nowEdge, Start);
	
	//stack�f�[�^����o�H�T�������i�r���b�V��������z��ɓ����
	SetRoatEdge(stack);
	
}

//NavEdge������ۂ̋����̎Z�o�i������:�X�^�[�g����ʒu�A������:�S�[������ʒu,��O����:�����j
bool NavCollision::CreateNearVectol(const VECTOR3 Position, const VECTOR3 Target, VECTOR3& OutVectol)
{
	//�����^�[�Q�b�g���S�Ă�NavEdge���ɂ͂��Ȃ��Ȃ�
	if (target->NavgasionPossibleFlg == false)return false;

	//�Ƃ肠���� �����}�X�Ȃ�return;
	if (roatEdge.size() <= 1) {
		OutVectol = Target;
		return true;
	}
	//�Q�G�b�W���ʂ��Ă��钸�_
	VECTOR3 ContantPos[2];

	//�Q�G�b�W���ʂ��Ă��钸�_��Position�̃x�N�g��
	VECTOR3 Vcontant[2];

	//�Q�G�b�W���ʂ��Ă��Ȃ�
	VECTOR3 NotContctPosition;

	//�Q�G�b�W���ʂ��Ă��Ȃ����_��Position�̃x�N�g��
	VECTOR3 VNotContctPosition;

	//�ŒZ�����ɐi�ނ��߂̃x�N�g���i�����j
	VECTOR3 V_Answer = Target;

	//�G�b�W�f�[�^�̎Z�o
	NavEdge* edge = roatEdge.at(0);
	NavEdge* Nextedge = roatEdge.at(1);

	//static int degugIndex = 0;

	//ImGui::Begin("aaaa");
	//ImGui::InputInt("Test", &degugIndex);
	//ImGui::End();

	//�Q�G�b�W���ʂ��Ă��钸�_�̎Z�o
	GetContactPos(edge, Nextedge, ContantPos);

	//���̃��b�V���ɖʂ��Ă��Ȃ����_�̎Z�o
	GetNotContact(edge, Nextedge, NotContctPosition);

	//�����Ԑ��Ɛ����t�Ȃ���ѕς���i�t�Ȃ�s���������j
	RearrangesPosition(ContantPos[0], ContantPos[1], Position, edge, Nextedge, NotContctPosition);

	//�i�r���b�V����ł̊p�̎Z�o
	SearchCorner(edge, Nextedge, NotContctPosition, ContantPos[0], ContantPos[1], Position, V_Answer);
	


	if (V_Answer.x + V_Answer.y + V_Answer.z == 0)return false;
	OutVectol = V_Answer;
	return true;

	//Position.y = V_Answer.y;
	//TK_Lib::Debug3D::Line(Position, V_Answer, { 1,0,0,1 });




}

//�e�X�g�p
void NavCollision::Render()
{
	//�o�H�T���̉���
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
//�^�[�Q�b�g�̐ݒ�
void NavCollision::SetTarget(const VECTOR3& Pos, const VECTOR3& Pos2)
{
	//�����ł̓^�[�Q�b�g������|���S���̎Z�o���Ă���
	target->NavgasionPossibleFlg = GetOnNavMeshToRayPick(Pos, Pos2, target->inMesh);
	//�ʒu�̍X�V
	target->pos = Pos;
}


//=======================================================================
//�������牺�̃R�[�h�͌o�H�T���N���X�̓����֐��ł���A��{�I��NavCollison�֐��݂̂ł������悤���Ă��Ȃ�(���̂���private�����Ă���)
//�܂����w�i���ς�O�ρj��_�C�N�X�g���@�Ȃǂ����悤���Ă��āA���ɓ���ȃR�[�h�ɂȂ��Ă���B
//�����₤�R�����g�A�E�g�i�����̂݁j�Ő�������̂Ɍ��E���������B 
//�����ŁA��������Ƃł��邪���̃Q�[���v���W�F�N�g�t�@�C����[�v���O�����̎d�l��]�t�@�C��������Ǝv���B
//�����ɐ�����₤���Ƃɂ���B
// �i�֐��̐����ł͂Ȃ��A�o�H�T���̗���Ƒ�G�c�Ȑ����j
//=======================================================================



//�o�H�T���̒T���ς݂�����
void NavCollision::ClearNavEdgeSearch()
{
	for (NavEdge* Edge : navMeshes)
	{
		Edge->searchflg = false;
		Edge->parent = nullptr;
	}
}


//���̃|���S���ɖʂ��Ă��Ȃ����_�̎Z�o
void NavCollision::GetNotContact(const NavEdge* edge, const NavEdge* nextedge, VECTOR3& OutPosition)
{
	//�ʂ��Ă��Ȃ����_�̎Z�o
	for (VECTOR3 pos1 : nextedge->positions)
	{
		bool flg = false;
		for (VECTOR3 pos2 : edge->positions)
		{
			//�ʂ��Ă���I
			if (pos1 == pos2)
			{
				flg = true;
				break;
			}
		}
		//�ʂ��Ă��Ȃ��Ȃ�
		if (flg == false)
		{
			OutPosition = pos1;
			break;
		}
	}
}
//��̃x�N�g���̊Ԃ�Tpos�����邩�ǂ����̔���
bool NavCollision::InPosition(const VECTOR3 &Rpos, const VECTOR3& Pos1, const VECTOR3& Pos2, const VECTOR3& Tpos)
{

	XMVECTOR R = DirectX::XMLoadFloat3(&Rpos);
	XMVECTOR A = DirectX::XMLoadFloat3(&Pos1);
	XMVECTOR B = DirectX::XMLoadFloat3(&Pos2);
	XMVECTOR T = DirectX::XMLoadFloat3(&Tpos);
	//R����݂Ẵx�N�g�����v�Z����
	XMVECTOR RA = XMVector3Normalize(XMVectorSubtract(A, R));
    XMVECTOR RB = XMVector3Normalize(XMVectorSubtract(B, R));
    XMVECTOR RT = XMVector3Normalize(XMVectorSubtract(T, R));
	//�@���̎擾
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


//��̃x�N�g���̊Ԃ̊p�x�̎Z�o
float NavCollision::GetAngle(const VECTOR3& Rpos, const VECTOR3& pos1, const VECTOR3& pos2)
{
	VECTOR3 V[2];
	XMVECTOR Pos[2];
	XMVECTOR Dot;
	float dot;
	V[0] = pos1 - Rpos;
	V[1] = pos2 - Rpos;
	//��̃x�N�g���̊p�x�̎Z�o
	Pos[0] = XMLoadFloat3(&V[0]);
	Pos[1] = XMLoadFloat3(&V[1]);
	Pos[0] = XMVector3Normalize(Pos[0]);
	Pos[1] = XMVector3Normalize(Pos[1]);
	Dot = XMVector3Dot(Pos[0], Pos[1]);
	XMStoreFloat(&dot, Dot);
	return dot;
}

//���̃��b�V���ɖʂ��Ă��钸�_�̎Z�o
void NavCollision::GetContactPos(const NavEdge* edge, const NavEdge* Nextedge,  VECTOR3 *Posision)
{
	int ret = 0;
	for (VECTOR3 pos1 : Nextedge->positions)
	{
		bool flg = false;
		for (VECTOR3 pos2 : edge->positions)
		{
			//�ʂ��Ă���I
			if (pos1 == pos2)
			{
				Posision[ret] = pos1;
				ret++;
				break;
			}
		}
	}
}
//�S����
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
	//��̃x�N�g���̐����x�N�g���̎Z�o
	XMVECTOR Cross, Pos1, Pos2;
	Pos1 = XMLoadFloat3(&V);
	Pos2 = XMLoadFloat3(&V2);
	Cross = XMVector3Cross(Pos1, Pos2);
	XMStoreFloat3(&OutV, Cross);
}
//��̃G�b�W�̒��_���ǂꂩ�ڐG���Ă����Ȃ�true��Ԃ�
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

//��Ƃ����������
void NavCollision::ClearRoomPos(const VECTOR3 ownerPos, const VECTOR3 GoalPos,  VECTOR3 &OutPos)
{
	//��Ƃ�
	constexpr float Volume = 1.1f;
	VECTOR3 vec1, vec2;
	vec1= target->pos - ownerPos;//�X�^�[�g��Target�̃x�N�g��
	vec2= GoalPos - ownerPos;//�X�^�[�g�ƃS�[���̃x�N�g��

	//TK_Lib::Debug3D::Line(target->Position , ownerPos);
	//TK_Lib::Debug3D::Line(GoalPos, ownerPos, {0,1,0,1});
	//�p���狗��������������

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

//���[�J����Ԃ��烏�[���h���W
void NavCollision::NavModelLocalToWorld(const int navModelIndex)
{
	const std::shared_ptr<ModelResource> model = TK_Lib::Model::GetModels().at(navModelIndex);

	for (const ModelResource::Mesh& mesh : model->GetMeshes())
	{
		const std::vector<ModelResource::Vertex>& vetices = mesh.vertices;
		const std::vector<UINT> indices = mesh.indices;

		//���b�V���m�[�h�擾
		const ModelResource::NodeTest& node = model->GetNodetest().at(mesh.nodeIndex);

		//���C�����[���h��Ԃ��탍�[�J����Ԃɕϊ�����
		XMMATRIX WorldTranceform = XMLoadFloat4x4(&node.worldTransform);
		XMMATRIX InverseWorldTranceform = XMMatrixInverse(nullptr, WorldTranceform);
		//���[�J�����
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
				//�O�p�`�̒��_�����Z�o����
				const ModelResource::Vertex& a = vetices.at(indices.at(index));
				const int indexB = index + 1;
				const int indexC = index + 2;


				const ModelResource::Vertex& b = vetices.at(indices.at(indexB));
				const ModelResource::Vertex& c = vetices.at(indices.at(indexC));



				XMVECTOR A = DirectX::XMLoadFloat3(&a.position);
				XMVECTOR B = DirectX::XMLoadFloat3(&b.position);
				XMVECTOR C = DirectX::XMLoadFloat3(&c.position);

				// //�O�p�`�̎O�Ӄx�N�g�����Z�o
				// XMVECTOR AB = XMVectorSubtract(B, A);
				// XMVECTOR BC = XMVectorSubtract(C, B);
				// XMVECTOR CA = XMVectorSubtract(A, C);
				// //�O�p�`�̖@���x�N�g���̎Z�o
				// XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(AB, BC));
				// // XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(BC,AB));
				// //���ς̒l���v���X�Ȃ痠����
				// XMVECTOR Dot = XMVector3Dot(V_Up, Normal);
				// float dot;
				// XMStoreFloat(&dot, Dot);
				// //if (dot != 0)continue;//������
				// dot = acosf(dot);
				// //if (dot >=XMConvertToRadians(40))continue;//������

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

//���b�V���z��̍쐬
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
		{//�d�S�̎Z�o
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

//�ׂ̃��b�V���̊֘A����
void NavCollision::RelatedToNextMesh()
{
	//�ׂ̃��b�V���̊֘A����
	for (NavEdge* navEdge : navMeshes)
	{
		for (NavEdge* navEdge2 : navMeshes)
		{
			if (navEdge == navEdge2)continue;

			//��ƂȂ郁�b�V��
			for (int i = 0; i < navEdge->positions.size(); i++)
			{
				//�֘A�ƂȂ郁�b�V��
				for (int j = 0; j < navEdge2->positions.size(); j++)
				{
					//��_���A�Ȃ��Ă���I
					if (navEdge->positions.at(i) == navEdge2->positions.at(j))
					{
						VECTOR3 Duplicate = navEdge->positions.at(i);
						//�Q�_�Ƃ��A�Ȃ��Ă��邩�ǂ���	
						for (int k = 0; k < navEdge->positions.size(); k++)
						{
							if (Duplicate == navEdge->positions.at(k))continue;

							for (int m = 0; m < navEdge2->positions.size(); m++)
							{
								if (navEdge->positions.at(k) == navEdge2->positions.at(m))
								{
									//���ɓo�^����Ă��邩�ǂ���
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


//���C�ɓ��������i�r���b�V���̎擾
bool NavCollision::GetOnNavMeshToRayPick(const VECTOR3& Pos, const VECTOR3& Pos2, NavEdge*& mesh)
{
	//TK_Lib::Debug3D::Line(Pos, Pos2, VECTOR4(0, 1, 0, 1));

	XMVECTOR Start = XMLoadFloat3(&Pos);
	XMVECTOR End = XMLoadFloat3(&Pos2);

	XMVECTOR Vec = XMVectorSubtract(End, Start);
	XMVECTOR Dir = XMVector3Normalize(Vec);
	XMVECTOR Length = XMVector3Length(Vec);
	//���C�̒���
	float neart;
	XMStoreFloat(&neart, Length);


	//�ŒZ����
	float NearL = FLT_MAX;
	//�ŒZ�����̃G�b�W
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


		//�O�p�`�̎O�Ӄx�N�g�����Z�o
		XMVECTOR AB = XMVectorSubtract(B, A);
		XMVECTOR BC = XMVectorSubtract(C, B);
		XMVECTOR CA = XMVectorSubtract(A, C);
		//�O�p�`�̖@���x�N�g���̎Z�o
		XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(AB, BC));
		//XMVECTOR Normal = XMVector3Normalize(XMVector3Cross(BC,AB));
		//���ς̒l���v���X�Ȃ痠����
		XMVECTOR Dot = XMVector3Dot(Dir, Normal);
		float dot;
		XMStoreFloat(&dot, Dot);
		if (dot >= 0)continue;//������

		//���C�ƕ��ʂ̌����_
		XMVECTOR d1 = XMVector3Dot(XMVectorSubtract(A, Start), Normal);
		//XMVECTOR d2 = XMVector3Dot(Normal, Dir);
		XMVECTOR T = XMVectorDivide(d1, Dot);
		float t;
		XMStoreFloat(&t, T);
		//��_�܂ł̋��������܂łɌv�Z�����ŋߋ��������傫���Ƃ��̓X�L�b�v
		if (t<0.0f || t>neart)continue;
		XMVECTOR Position = XMVectorMultiply(Dir, T);
		Position = XMVectorAdd(Position, Start);
		XMFLOAT3 pos;
		XMStoreFloat3(&pos, Position);

		//��_���O�p�`�̓����ɂ��邩����
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

//�_�C�N�X�g���@�ŖڕW�̎Z�o
void NavCollision::DijkstraMesh(std::queue<NavEdge*>& queue, NavEdge*& nowEdge, NavEdge* GoalEdge)
{
	//�o�H�T��(�_�C�N�X�g���@)
	while (!queue.empty())
	{
		//�X�^�b�N�ɋl�܂ꂽ�G�b�W�f�[�^�����o��
		nowEdge = queue.front();
		//�폜
		queue.pop();

		//�m�[�h��H��
		for (NavNode* node : nowEdge->navNodes)
		{
			if (node->nextNavMesh->searchflg)continue;
			//�ǉ�
			queue.push(node->nextNavMesh);
			//�e�̐ݒ�i�i�񂾈ʒu�̋O�Ղ��c���Ă����j
			node->nextNavMesh->parent = nowEdge;
			//�T�������t���O
			node->nextNavMesh->searchflg = true;

			//	//�T���̉���
			//	VECTOR3 Pos1 = { nowEdge->Positions.at(0).x,nowEdge->Positions.at(0).y + 0.2f ,nowEdge->Positions.at(0).z };
			//			VECTOR3 Pos2 = { nowEdge->Positions.at(1).x,nowEdge->Positions.at(1).y + 0.2f ,nowEdge->Positions.at(1).z };
			//			VECTOR3 Pos3 = { nowEdge->Positions.at(2).x,nowEdge->Positions.at(2).y + 0.2f ,nowEdge->Positions.at(2).z };
			//	
			//			TK_Lib::Debug3D::Line(Pos1, Pos2, { 0,0,1,1 });
			//			TK_Lib::Debug3D::Line(Pos2, Pos3, { 0,0,1,1 });
			//			TK_Lib::Debug3D::Line(Pos3, Pos1, { 0,0,1,1 });
		}

		//�ړI�n�ɓ����I
		if (nowEdge == GoalEdge)break;//�I��


	}
}

//�o�H�T��������ɁA�X�^�[�g����S�[���܂ŒH��B
void NavCollision::PursueNavMesh(std::stack<NavEdge*>& stack, NavEdge*& nowEdge, const NavEdge* startEdge)
{
	

	while (true)
	{

		stack.push(nowEdge);
		if (nowEdge == startEdge)break;
		if (nowEdge)
		{
			//�ЂƂO�̃G�b�W�ɖ߂�B
			nowEdge = nowEdge->parent;
		}


	}
}
//stack�f�[�^����o�H�T�������i�r���b�V��������z��ɓ����
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

// �Ԑ��Ɛ����t�̕��тɂȂ��Ă����琳�������ɕ��ёւ���
void NavCollision::RearrangesPosition(VECTOR3 & Pos1, VECTOR3 & Pos2, VECTOR3 originPos, const NavEdge * edge, const NavEdge * nextedge, VECTOR3 & OutPosition)
{
	VECTOR3 c;
	Cross(Pos2 - originPos, Pos1 - originPos, c);
	if (c.y > 0)
	{
		//���ёւ�
		c = Pos1;
		Pos1 = Pos2;
		Pos2 = c;
		//���̃��b�V���ɖʂ��Ă��Ȃ����_�̎Z�o
		GetNotContact(edge, nextedge, OutPosition);

	}
}

//�i�r���b�V���p�̎Z�o
void NavCollision::SearchCorner(NavEdge* edge, NavEdge* nextedge,VECTOR3 &notContctPosition, VECTOR3& pos1, VECTOR3& pos2, const VECTOR3 &originPos,VECTOR3& anwer )
{
	//�p��������܂ŎZ�o
	for (int i = 0; i < roatEdge.size() - 1; i++)
	{
		//���Ǝ��̃��b�V���̎Z�o
		edge = roatEdge.at(i);
		const int index = i + 1;
		nextedge = roatEdge.at(index);

		//���̃��b�V���ɖʂ��Ă��Ȃ����_�̎Z�o
		GetNotContact(edge, nextedge, notContctPosition);

		//�ʒu��K�p
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
		//	//�f�o�b�N
		//	{
		//		// //��
		//		// TK_Lib::Debug3D::Line(edge->centerPos, ContantPos[0], { 1,0,0,1 });
		//		// //��
		//		// TK_Lib::Debug3D::Line(edge->centerPos, ContantPos[1], { 0,0,1,1 });
		//		// //��
		//		// TK_Lib::Debug3D::Line(edge->centerPos, NotContctPosition, { 0,1,0,1 });
		//		// //���F
		//		//if (RoatEdge.size()-i >2)
		//		//{
		//		//	TK_Lib::Debug3D::Line(edge->centerPos, RoatEdge.at(i + 2)->centerPos, { 1,1,0,1 });
		//		//}
		//		//else
		//		//{
		//		//	TK_Lib::Debug3D::Line(edge->centerPos, RoatEdge.at(i)->centerPos, { 1,1,0,1 });
		//		//}
		//		// 
		//		////��
		//		//TK_Lib::Debug3D::Line(Position, ContantPos[0], { 1,0,0,1 });
		//		////��
		//		//TK_Lib::Debug3D::Line(Position, ContantPos[1], { 0,0,1,1 });
		//		//��
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
			//��
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
			//��
			Cross(pos1 - originPos, notContctPosition - originPos, Cr);
			//
			if (Cr.y >= 0)
			{
				pos1 = notContctPosition;
			}
			//��
			//ContantPos[0] = NotContctPosition;
		}



	}
}