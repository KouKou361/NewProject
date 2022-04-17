#pragma once
#include "Lib.h"
class NavEdge;

//�i�r���f���̃��b�V�����
class NavCollisionNode
{
public:
	VECTOR3 pos[3];
};


//�m�[�h
class NavNode
{
public:
	NavEdge* nextNavMesh;
	float length;//�����̏d�S���瑊��̏d�S�܂ł̋���
	
};
class NavEdge
{
public:
	bool searchflg = false;//�T���t���O
	VECTOR3 centerPos;
	vector<VECTOR3>positions;
	//�q���m�[�h
	vector<NavNode*> navNodes;
	//�e�̃G�b�W(�T�����鎞�Ɏg��)
	NavEdge* parent;

	//����NacNodes�ɓo�^����Ă���m�[�h���ǂ���
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
	//�n�ʃ��b�V�������蔻��
	vector<NavCollisionNode>collisionModelsPos;
	//�i�r���b�V��
	vector<NavEdge*>navMeshes;
	//�X�^�[�g�ʒu����{�[���܂ł�Edge
	vector<NavEdge*> roatEdge;
	//�^�[�Q�b�g�̏��
	NavTarget *target;
public:
	//AI�̂��߂̃X�e�[�W�\��
	void NavStageBuild(const int navModelIndex);
	//�e�X�g�p
	void Render();
	//�S����
	void Clear();
	//�^�[�Q�b�g�̐ݒ�
	void SetTarget(const VECTOR3& pos, const VECTOR3& pos2);
	//�o�H�T���̒T���ς݂�����
	void ClearNavEdgeSearch();
	//���̃��b�V���ɖʂ��Ă��Ȃ����_�̎Z�o
	void GetNotContact(NavEdge* edge, NavEdge* nextedge, VECTOR3& outPosition);
	//���̃��b�V���ɖʂ��Ă��钸�_�̎Z�o
	void GetContactPos(const NavEdge* edge, const NavEdge* nextedge, VECTOR3* posision);
	//�o�H�T���i���b�V���P�ʂŁj
	void SearchRoat(NavEdge*& start, NavEdge*& end);
	//�O��
	void Cross(const VECTOR3& v, const VECTOR3& v2, VECTOR3& outv);
	//��Ƃ����������
	void ClearRoomPos(const VECTOR3 ownerPos, const VECTOR3 goalPos,   VECTOR3& outPos);
	//NavEdge������ۂ̋����̎Z�o
	bool CreateNearRoat(const VECTOR3 position, const VECTOR3 target,  VECTOR3 &outPos);
	//���C�ɓ��������i�r���b�V���̎擾
	bool GetOnNacMesh(const VECTOR3& pos, const VECTOR3& pos2, NavEdge*& mesh);
	//��̃x�N�g���̊Ԃ�Tpos�����邩�ǂ����̔���
	bool InPosition(const VECTOR3& rpos, const VECTOR3& pos1, const VECTOR3& pos2, const VECTOR3& tpos);
	//
	bool rayVsray2D(const VECTOR3 posA1, const VECTOR3 posA2, const VECTOR3 posB1, const VECTOR3 posB2);
	//��̃G�b�W�̒��_���ǂꂩ�ڐG���Ă����Ȃ�true��Ԃ�
	bool Contant(NavEdge*& edge1, NavEdge*& edge2);
	//��̃x�N�g���̊Ԃ̊p�x�̎Z�o
	float GetAngle(const VECTOR3& rpos, const VECTOR3& pos1, const VECTOR3& pos2 );

	inline NavTarget* GetNavTarget() { return target;}
};