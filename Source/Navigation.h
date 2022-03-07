#pragma once
#include "Lib.h"

//�i�r���f���̃��b�V�����
class NavCollisionNode
{
public:
	VECTOR3 Pos[3];
};
class NavEdge;
//�m�[�h
class NavNode
{
public:
	NavEdge* NextNavMesh;
	float Length;//�����̏d�S���瑊��̏d�S�܂ł̋���
	
};
class NavEdge
{
public:
	bool searchflg = false;//�T���t���O
	VECTOR3 centerPos;
	vector<VECTOR3>Positions;
	//�q���m�[�h
	vector<NavNode*> NacNodes;
	//�e�̃G�b�W(�T�����鎞�Ɏg��)
	NavEdge* parent;

	//����NacNodes�ɓo�^����Ă���m�[�h���ǂ���
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
	//�n�ʃ��b�V�������蔻��
	vector<NavCollisionNode>CollisionModelsPos;
	//�i�r���b�V��
	vector<NavEdge*>NacMeshes;
	//�X�^�[�g�ʒu����{�[���܂ł�Edge
	vector<NavEdge*> RoatEdge;
	//�^�[�Q�b�g�̏��
	NavTarget *target;
public:
	//AI�̂��߂̃X�e�[�W�\��
	void NavStageBuild(int navModelIndex);
	//�e�X�g�p
	void Render();
	//�S����
	void Clear();
	//NavEdge������ۂ̋����̎Z�o
	bool CreateNearRoat(VECTOR3 Position, VECTOR3 Target,VECTOR3 &OutPos);
	//���C�ɓ��������i�r���b�V���̎擾
	bool GetOnNacMesh(const VECTOR3& Pos, const VECTOR3& Pos2, NavEdge*& mesh);
	//��̃x�N�g���̊Ԃ�Tpos�����邩�ǂ����̔���
	bool InPosition(const VECTOR3& Rpos, const VECTOR3& Pos1, const VECTOR3& Pos2, const VECTOR3& Tpos);
	//�^�[�Q�b�g�̐ݒ�
	void SetTarget(const VECTOR3& Pos, const VECTOR3& Pos2);
	//�o�H�T���̒T���ς݂�����
	void ClearNavEdgeSearch();
	//���̃��b�V���ɖʂ��Ă��Ȃ����_�̎Z�o
	void GetNotContact(NavEdge* edge, NavEdge* nextedge, VECTOR3& OutPosition);
	//��̃x�N�g���̊Ԃ̊p�x�̎Z�o
	float GetAngle(const VECTOR3& Rpos, const VECTOR3& pos1, const VECTOR3& pos2 );
	//���̃��b�V���ɖʂ��Ă��钸�_�̎Z�o
	void GetContactPos(const NavEdge* edge, const NavEdge* Nextedge, VECTOR3* Posision);

	void SearchRoat(NavEdge*& Start, NavEdge*& End);
	bool rayVsray2D(VECTOR3 Pos, VECTOR3 Pos2, VECTOR3 pos, VECTOR3 pos2 );
	void Cross(const VECTOR3& V, const VECTOR3& V2, VECTOR3 &OutV);
	//��̃G�b�W�̒��_���ǂꂩ�ڐG���Ă����Ȃ�true��Ԃ�
	bool Contant(NavEdge*& edge1, NavEdge*& edge2);
	
	//���̂܂܂ł͏ꍇ�ɂ���Ă͂͂ݏo��\��������̂�
	//��Ƃ����������
	void ClearRoomPos(VECTOR3 ownerPos, VECTOR3 GoalPos, VECTOR3& OutPos);
	NavTarget* GetNavTarget() { 
		return target;
	}
};