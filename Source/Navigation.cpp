#include "Navigation.h"
#include <queue>
#include <stack>
//���ɓo�^����Ă���m�[�h���ǂ���
bool NavEdge::EdgeDuplicate(NavEdge* edge)
{
	for (NavNode* Node : NacNodes)
	{
		if (edge == Node->NextNavMesh)
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
	target = new NavTarget();
		std::shared_ptr<ModelResource> model = TK_Lib::Model::GetModels().at(navModelIndex);

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
			XMVECTOR HitPosition;
			XMVECTOR HitNormalize;
			XMVECTOR PolygonPostion[3];
			NavCollisionNode stageNode;

			for (const ModelResource::Subset& subset : mesh.subsets)
			{
				for (UINT i = 0; i < subset.indexCount; i += 3)
				{

					UINT index = subset.startIndex + i;
					//�O�p�`�̒��_�����Z�o����
					const ModelResource::Vertex& a = vetices.at(indices.at(index));
					const ModelResource::Vertex& b = vetices.at(indices.at(index + 1));
					const ModelResource::Vertex& c = vetices.at(indices.at(index + 2));



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
					XMStoreFloat3(&stageNode.Pos[0], WorldPolygonPostion[0]);
					XMStoreFloat3(&stageNode.Pos[1], WorldPolygonPostion[1]);
					XMStoreFloat3(&stageNode.Pos[2], WorldPolygonPostion[2]);



					CollisionModelsPos.push_back(stageNode);
				}

			}




		}


		
		//�i�r���b�V���̍쐬
		int test = 0;
		for (int i = 0; i <= CollisionModelsPos.size(); i++)
		{
		
			if (i >= CollisionModelsPos.size() )break;

			NavEdge* navEdge = new NavEdge();

			VECTOR3 Pos1 = CollisionModelsPos.at(i).Pos[0];
			VECTOR3 Pos2 = CollisionModelsPos.at(i).Pos[1];
			VECTOR3 Pos3 = CollisionModelsPos.at(i).Pos[2];
			
		 
		//	VECTOR3 Pos4 = CollisionModelsPos.at(i+1).Pos[1];
		//	if (InPosition(Pos1, Pos2, Pos3, Pos4))
			{//�d�S�̎Z�o
				navEdge->centerPos = (Pos1 + Pos2 + Pos3) / 3;
				navEdge->Positions.push_back(Pos1);
				navEdge->Positions.push_back(Pos2);
			//	nacMesh->Positions.push_back(Pos4);
				navEdge->Positions.push_back(Pos3);
			}

	
	

				NacMeshes.push_back(navEdge);
			//	break;
			
		}
		//�ׂ̃��b�V���̊֘A����
		for (NavEdge* navEdge : NacMeshes)
		{
			for (NavEdge* navEdge2 : NacMeshes)
			{
				if (navEdge == navEdge2)continue;

				//��ƂȂ郁�b�V��
				for (int i = 0; i < navEdge->Positions.size(); i++)
				{
					//�֘A�ƂȂ郁�b�V��
					for (int j = 0; j < navEdge2->Positions.size(); j++)
					{
						//��_���A�Ȃ��Ă���I
						if (navEdge->Positions.at(i) == navEdge2->Positions.at(j))
						{
							VECTOR3 Duplicate= navEdge->Positions.at(i);
						//�Q�_�Ƃ��A�Ȃ��Ă��邩�ǂ���	
							for (int k = 0; k < navEdge->Positions.size(); k++)
							{
								if (Duplicate == navEdge->Positions.at(k))continue;

								for (int m = 0; m < navEdge2->Positions.size(); m++)
								{
									if (navEdge->Positions.at(k) == navEdge2->Positions.at(m))
									{
										//���ɓo�^����Ă��邩�ǂ���
										if (navEdge->EdgeDuplicate(navEdge2))break;

										NavNode *navNode=new NavNode();
										navNode->NextNavMesh = navEdge2;
										XMVECTOR A = XMLoadFloat3(&navEdge->centerPos);
										XMVECTOR B = XMLoadFloat3(&navEdge2->centerPos);
										XMVECTOR Length = XMVector3Length(XMVectorSubtract(A, B));
										XMStoreFloat(&navNode->Length,Length);
										navEdge->NacNodes.push_back(navNode);
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
bool NavCollision::GetOnNacMesh(const VECTOR3& Pos, const VECTOR3& Pos2, NavEdge*& mesh)
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
	float NearL=FLT_MAX;
	//�ŒZ�����̃G�b�W
	NavEdge* SaveEdge=nullptr;

	for (NavEdge* navEdge : NacMeshes)
	{
		
		XMVECTOR A = DirectX::XMLoadFloat3(&navEdge->Positions.at(0));
		XMVECTOR B = DirectX::XMLoadFloat3(&navEdge->Positions.at(1));
		XMVECTOR C = DirectX::XMLoadFloat3(&navEdge->Positions.at(2));

		for (int i = 0; i < 3; i++)
		{
			VECTOR3 P = navEdge->Positions.at(i) - Pos;
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
		
		//�T���̉���
	 	//VECTOR3 Pos1 = { navEdge->Positions.at(0).x,navEdge->Positions.at(0).y + 0.2f ,navEdge->Positions.at(0).z };
	 	//VECTOR3 Pos2 = { navEdge->Positions.at(1).x,navEdge->Positions.at(1).y + 0.2f ,navEdge->Positions.at(1).z };
	 	//VECTOR3 Pos3 = { navEdge->Positions.at(2).x,navEdge->Positions.at(2).y + 0.2f ,navEdge->Positions.at(2).z };
		//
		//TK_Lib::Debug3D::Line(Pos1, Pos2,{0,1,0,1});
		//TK_Lib::Debug3D::Line(Pos2, Pos3,{0,1,0,1});
		//TK_Lib::Debug3D::Line(Pos3, Pos1,{0,1,0,1});
		//
		//for (NavNode* nacMesh2 : navEdge->NacNodes)
		//{
		//	NavEdge* edge=nacMesh2->NextNavMesh;
		//	Pos1 = { edge->Positions.at(0).x,edge->Positions.at(0).y + 0.2f ,edge->Positions.at(0).z };
		//	Pos2 = { edge->Positions.at(1).x,edge->Positions.at(1).y + 0.2f ,edge->Positions.at(1).z };
		//	Pos3 = { edge->Positions.at(2).x,edge->Positions.at(2).y + 0.2f ,edge->Positions.at(2).z };
		//
		//	TK_Lib::Debug3D::Line(Pos1, Pos2, { 0,0,1,1 });
		//	TK_Lib::Debug3D::Line(Pos2, Pos3, { 0,0,1,1 });
		//	TK_Lib::Debug3D::Line(Pos3, Pos1, { 0,0,1,1 });
		//}
		return true;
		
	}
	mesh = SaveEdge;
	//TK_Lib::Debug3D::Circle(mesh->centerPos, 0.2f);

	return true;
}
//�e�X�g�p
void NavCollision::Render()
{
	//�o�H�T���̉���
	for (int i = 0; i < RoatEdge.size(); i++)
	{
		NavEdge* edge = RoatEdge.at(i);
		VECTOR3 Pos1 = { edge->Positions.at(0).x,edge->Positions.at(0).y +0.5f ,edge->Positions.at(0).z };
		VECTOR3 Pos2 = { edge->Positions.at(1).x,edge->Positions.at(1).y +0.5f ,edge->Positions.at(1).z };
		VECTOR3 Pos3 = { edge->Positions.at(2).x,edge->Positions.at(2).y +0.5f ,edge->Positions.at(2).z };

		TK_Lib::Debug3D::Line(Pos1, Pos2, { 0,0,1,1 });
		TK_Lib::Debug3D::Line(Pos2, Pos3, { 0,0,1,1 });
		TK_Lib::Debug3D::Line(Pos3, Pos1, { 0,0,1,1 });
	}

	for (NavCollisionNode node : CollisionModelsPos)
	{
		VECTOR3 Pos1 = { node.Pos[0].x,node.Pos[0].y + 0.3f ,node.Pos[0].z };
		VECTOR3 Pos2 = { node.Pos[1].x,node.Pos[1].y + 0.3f ,node.Pos[1].z };
		VECTOR3 Pos3 = { node.Pos[2].x,node.Pos[2].y + 0.3f ,node.Pos[2].z };

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
void NavCollision::SetTarget(const VECTOR3& Pos, const VECTOR3& Pos2)
{
	//���C�ɓ��������i�r���b�V���̎擾
	target->function =GetOnNacMesh(Pos,Pos2,target->InMesh);
	target->Position = Pos;
}
//�o�H�T���̒T���ς݂�����
void NavCollision::ClearNavEdgeSearch()
{
	for (NavEdge* Edge : NacMeshes)
	{
		Edge->searchflg = false;
		Edge->parent = nullptr;
	}
}
//���̃��b�V���ɖʂ��Ă��Ȃ����_�̎Z�o
void NavCollision::GetNotContact(NavEdge* edge, NavEdge* nextedge,VECTOR3 &OutPosition)
{
	//�ʂ��Ă��Ȃ����_�̎Z�o
	for (VECTOR3 pos1 : nextedge->Positions)
	{
		bool flg = false;
		for (VECTOR3 pos2 : edge->Positions)
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
//�G�b�W�̌o�H�T��
void NavCollision::SearchRoat(NavEdge*& Start, NavEdge*& End)
{
	//�����^�[�Q�b�g���S�Ă�NavEdge���ɂ͂��Ȃ��Ȃ�
	if (target->function == false)return;

	//�o�H�T���̒T���ς݂�����
	ClearNavEdgeSearch();



	//�T�����̃f�[�^
	std::queue<NavEdge*> queue;
	queue.push(Start);

	//���݈ʒu��Edge
	NavEdge* nowEdge=nullptr;
	//�o�H�T��(�_�C�N�X�g���@)
	while(!queue.empty())
	{
		//�X�^�b�N�ɋl�܂ꂽ�G�b�W�f�[�^�����o��
		nowEdge = queue.front();
		//�폜
		queue.pop();

		//�m�[�h��H��
		for (NavNode* node : nowEdge->NacNodes)
		{
			if (node->NextNavMesh->searchflg)continue;
			//�ǉ�
			queue.push(node->NextNavMesh);
			//�e�̐ݒ�
			node->NextNavMesh->parent = nowEdge;
			node->NextNavMesh->searchflg = true;

		//	//�T���̉���
		//	VECTOR3 Pos1 = { nowEdge->Positions.at(0).x,nowEdge->Positions.at(0).y + 0.2f ,nowEdge->Positions.at(0).z };
		//			VECTOR3 Pos2 = { nowEdge->Positions.at(1).x,nowEdge->Positions.at(1).y + 0.2f ,nowEdge->Positions.at(1).z };
		//			VECTOR3 Pos3 = { nowEdge->Positions.at(2).x,nowEdge->Positions.at(2).y + 0.2f ,nowEdge->Positions.at(2).z };
		//	
		//			TK_Lib::Debug3D::Line(Pos1, Pos2, { 0,0,1,1 });
		//			TK_Lib::Debug3D::Line(Pos2, Pos3, { 0,0,1,1 });
		//			TK_Lib::Debug3D::Line(Pos3, Pos1, { 0,0,1,1 });
			
		}

		//�ړI�n�ɓ���
		if (nowEdge == End)break;

	
	}


	//�T�����̃f�[�^
	std::stack<NavEdge*> stack;

		while (true)
		{

			stack.push(nowEdge);
			if (nowEdge == Start)break;
			nowEdge = nowEdge->parent;
		
		}
		int size = stack.size();
		RoatEdge.clear();
		
		for (int i = 0; i < size; i++)
		{
			NavEdge* edge = stack.top();
			stack.pop();

			RoatEdge.push_back(edge);

			//VECTOR3 Pos1 = { edge->Positions.at(0).x,edge->Positions.at(0).y + 0.4f ,edge->Positions.at(0).z };
			//VECTOR3 Pos2 = { edge->Positions.at(1).x,edge->Positions.at(1).y + 0.4f ,edge->Positions.at(1).z };
			//VECTOR3 Pos3 = { edge->Positions.at(2).x,edge->Positions.at(2).y + 0.4f ,edge->Positions.at(2).z };
			
			//TK_Lib::Debug3D::Line(Pos1, Pos2, { 0,0,0,1 });
			//TK_Lib::Debug3D::Line(Pos2, Pos3, { 0,0,0,1 });
			//TK_Lib::Debug3D::Line(Pos3, Pos1, { 0,0,0,1 });

		}
		
	
//	Start = nowEdge;
}
//NavEdge������ۂ̋����̎Z�o
bool NavCollision::CreateNearRoat(VECTOR3 Position, VECTOR3 Target, VECTOR3& OutPos)
{
	//�����^�[�Q�b�g���S�Ă�NavEdge���ɂ͂��Ȃ��Ȃ�
	if (target->function == false)return false;

	//�Ƃ肠���� //�����}�X�Ȃ�return;
	if (RoatEdge.size() <= 1) {
		OutPos = Target;
		return true;
	}

	VECTOR3 ContantPos[2];//�Q�G�b�W���ʂ��Ă��钸�_
	VECTOR3 Vcontant[2];//�Q�G�b�W���ʂ��Ă��钸�_��Position�̃x�N�g��

	VECTOR3 NotContctPosition;//�Q�G�b�W���ʂ��Ă��Ȃ�
	VECTOR3 VNotContctPosition;//�Q�G�b�W���ʂ��Ă��Ȃ����_��Position�̃x�N�g��

	VECTOR3 V_Answer= Target;

	//�G�b�W�f�[�^�̎Z�o
	NavEdge* edge = RoatEdge.at(0);
	NavEdge* Nextedge = RoatEdge.at(1);

	static int degugIndex = 0;

	//ImGui::Begin("aaaa");
	//ImGui::InputInt("Test", &degugIndex);
	//ImGui::End();

	//�Q�G�b�W���ʂ��Ă��钸�_�̎Z�o
	GetContactPos(edge, Nextedge, ContantPos);
	//���̃��b�V���ɖʂ��Ă��Ȃ����_�̎Z�o
	GetNotContact(edge, Nextedge, NotContctPosition);


	//�����Ԑ��Ɛ����t�Ȃ���ѕς���
	{
		VECTOR3 c;
		Cross(ContantPos[1] - Position, ContantPos[0] - Position, c);
		if (c.y > 0)
		{
			//���ёւ�
			c = ContantPos[0];
			ContantPos[0] = ContantPos[1];
			ContantPos[1] = c;
			//���̃��b�V���ɖʂ��Ă��Ȃ����_�̎Z�o
			GetNotContact(edge, Nextedge, NotContctPosition);

		}

	}


	int red = 0;
	int blue = 0;

	//�p��������܂ŎZ�o
	for (int i = 0; i < RoatEdge.size()-1; i++)
	{
		//���Ǝ��̃��b�V���̎Z�o
		edge = RoatEdge.at(i);
		Nextedge = RoatEdge.at(i + 1);

		//���̃��b�V���ɖʂ��Ă��Ȃ����_�̎Z�o
		GetNotContact(edge, Nextedge, NotContctPosition);

		


		
		//�ʒu��K�p
		VECTOR3 RedCross, BlueCross,RCross;
		VECTOR3 V_Yellow;
		if (RoatEdge.size() - i > 2)
		{
			V_Yellow = Nextedge->centerPos - RoatEdge.at(i + 2)->centerPos;
		}
		else
		{
			V_Yellow = Nextedge->centerPos - RoatEdge.at(i)->centerPos;
		}
		VECTOR3 V_Green = NotContctPosition - edge->centerPos;
		VECTOR3 V_Red = ContantPos[0] - edge->centerPos;
		VECTOR3 V_Blue = ContantPos[1] - edge->centerPos;

		Cross(V_Yellow, V_Green, RCross);
		


		if (degugIndex == i)
		{
			//�f�o�b�N
			{
				// //��
				// TK_Lib::Debug3D::Line(edge->centerPos, ContantPos[0], { 1,0,0,1 });
				// //��
				// TK_Lib::Debug3D::Line(edge->centerPos, ContantPos[1], { 0,0,1,1 });
				// //��
				// TK_Lib::Debug3D::Line(edge->centerPos, NotContctPosition, { 0,1,0,1 });
				// //���F
				//if (RoatEdge.size()-i >2)
				//{
				//	TK_Lib::Debug3D::Line(edge->centerPos, RoatEdge.at(i + 2)->centerPos, { 1,1,0,1 });
				//}
				//else
				//{
				//	TK_Lib::Debug3D::Line(edge->centerPos, RoatEdge.at(i)->centerPos, { 1,1,0,1 });
				//}
				// 
				////��
				//TK_Lib::Debug3D::Line(Position, ContantPos[0], { 1,0,0,1 });
				////��
				//TK_Lib::Debug3D::Line(Position, ContantPos[1], { 0,0,1,1 });
				//��
				//TK_Lib::Debug3D::Line(Position, NotContctPosition, { 0,1,0,1 });

				//ImGui::Begin("aaaa");
				//ImGui::Text("Cross=%f", V_Yellow.y);
				//ImGui::End();
			}
		}
		VECTOR3 Cr;
		VECTOR3 RVec;
		XMVECTOR NV;
		constexpr float R = 0.5f;

		if (RCross.y <= 0)
		{
			Cross(ContantPos[0] - Position, NotContctPosition - Position, Cr);
			if (Cr.y <= 0)
			{
				RVec = ContantPos[0] - edge->centerPos;
				//TK_Lib::Debug3D::Line(ContantPos[0] , edge->centerPos);
				NV = XMLoadFloat3(&RVec);
				NV = XMVector3Normalize(NV);
				NV = XMVectorScale(NV,R);
				XMStoreFloat3(&RVec, NV);
				
				V_Answer = ContantPos[0]- RVec;
				break;
			}
			//��
			Cross(ContantPos[1]-Position, NotContctPosition-Position, Cr);
			//
			if (Cr.y <= 0)
			{
			ContantPos[1] = NotContctPosition;
			}
			//CrNotContctPosition
			
		}
		else
		{
			Cross(ContantPos[1] - Position, NotContctPosition - Position, Cr);
			if (Cr.y >= 0)
			{
				//RVec = ContantPos[1] - Nextedge->centerPos;

				RVec = ContantPos[1] - edge->centerPos;
				//TK_Lib::Debug3D::Line(ContantPos[1], edge->centerPos);
				NV = XMLoadFloat3(&RVec);
				NV = XMVector3Normalize(NV);
				NV = XMVectorScale(NV, R);
				XMStoreFloat3(&RVec, NV);

			//	TK_Lib::Debug3D::Line(ContantPos[1], RoatEdge[i]->centerPos);
				V_Answer = ContantPos[1]- RVec;
				break;
			}
			//��
			Cross(ContantPos[0] - Position, NotContctPosition - Position, Cr);
			//
			if (Cr.y >= 0)
			{
				ContantPos[0] = NotContctPosition;
			}
			//��
			//ContantPos[0] = NotContctPosition;
		}
	


	}


	if (V_Answer.x + V_Answer.y + V_Answer.z == 0)return false;
	OutPos = V_Answer;
	return true;

	//Position.y = V_Answer.y;
	//TK_Lib::Debug3D::Line(Position, V_Answer, { 1,0,0,1 });




}
//���̃��b�V���ɖʂ��Ă��钸�_�̎Z�o
void NavCollision::GetContactPos(const NavEdge* edge, const NavEdge* Nextedge,VECTOR3 *Posision)
{
	int ret = 0;
	for (VECTOR3 pos1 : Nextedge->Positions)
	{
		bool flg = false;
		for (VECTOR3 pos2 : edge->Positions)
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
	CollisionModelsPos.clear();
	for (NavEdge* mesh : NacMeshes)
	{
		for (NavNode* node : mesh->NacNodes)
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

	NacMeshes.clear();
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
	for (VECTOR3 pos1 : edge1->Positions)
	{
		for (VECTOR3 pos2 : edge2->Positions)
		{
			if (pos1 == pos2) {
				return true;
			}
		}
	}
	return false;
}

//��Ƃ����������
void NavCollision::ClearRoomPos(VECTOR3 ownerPos,VECTOR3 GoalPos,VECTOR3 &OutPos)
{
	//��Ƃ�
	constexpr float Volume = 1.1f;
	VECTOR3 vec1, vec2;
	vec1= target->Position - ownerPos;//�X�^�[�g��Target�̃x�N�g��
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