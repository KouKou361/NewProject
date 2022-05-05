#pragma once
#include "Lib.h"
#include <queue>
#include <stack>

class NavEdge;

//�i�r���f���̈������̃|���S�����
class NavPolygonData
{
public:
	//�|���S���̎O�_�̈ʒu
	VECTOR3 pos[3] = {};
};

//�|���S���ƃ|���S�����q���m�[�h
//(�o�H�T�����鎞�ɁA�H���Ă������|���S����ۑ�����m�[�h)
class NavNode
{
public:
	NavEdge* nextNavMesh=nullptr;
	float length=0;//�����̏d�S���瑊��̏d�S�܂ł̋���
	
};


class NavEdge
{
public:
	bool searchflg = false;//�T���t���O
	VECTOR3 centerPos = {};
	vector<VECTOR3>positions;
	//�q���m�[�h
	vector<NavNode*> navNodes;
	//�e�̃G�b�W(�T�����鎞�Ɏg��)
	NavEdge* parent=nullptr;

	//����NacNodes�ɓo�^����Ă���m�[�h���ǂ���
	bool EdgeDuplicate(NavEdge* edge);
};

//�o�H�T������ڕW�f�[�^
class NavTargetData
{
public:
	//�i�r���b�V���ł�����t���O
	bool NavgasionPossibleFlg = false;//�i	//true�F�ڕW�͌o�H�T���ŒH�蒅����B  false�F�ڕW�͌o�H�T���ŒH�蒅���Ȃ��B�j
	NavEdge* inMesh=nullptr;//�ڕW�n�_�����郁�b�V��
	VECTOR3 pos = {};//�ڕW�n�_
};

class NavCollision
{
private:
	//�n�ʃ��b�V�������蔻��
	vector<NavPolygonData>collisionModelsPos;
	//�i�r���b�V��
	vector<NavEdge*>navMeshes;
	//�X�^�[�g�ʒu����{�[���܂ł�Edge
	vector<NavEdge*> roatEdge;
	//�^�[�Q�b�g�̏��
	NavTargetData *target=nullptr;
public:
	//AI�̂��߂̃X�e�[�W�\��
	void NavStageBuild(const int navModelIndex);

	//�e�X�g�p
	void Render();

	//�S����
	void Clear();

	//�^�[�Q�b�g�̐ݒ�
	void SetTarget(const VECTOR3& pos, const VECTOR3& pos2);

	//�o�H�T���i���b�V���P�ʂŁj
	void SearchRoat(NavEdge*& start, NavEdge*& end);

	//NavEdge������ۂ̋����̎Z�o
	bool CreateNearVectol(const VECTOR3 position, const VECTOR3 target, VECTOR3& outPos);

	//���C�ɓ��������i�r���b�V���̎擾
	bool GetOnNavMeshToRayPick(const VECTOR3& pos, const VECTOR3& pos2, NavEdge*& mesh);

	//�ڕW�̎擾
	inline NavTargetData* GetNavTarget() { return target; }
private:

	//���̃��b�V���ɖʂ��Ă��Ȃ����_�̎Z�o
	void GetNotContact(const NavEdge* edge, const NavEdge* nextedge, VECTOR3& OutPosition);

	//���̃��b�V���ɖʂ��Ă��钸�_�̎Z�o
	void GetContactPos(const NavEdge* edge, const NavEdge* nextedge, VECTOR3* posision);

	//�O��
	void Cross(const VECTOR3& v, const VECTOR3& v2, VECTOR3& outv);

	//��Ƃ����������
	void ClearRoomPos(const VECTOR3 ownerPos, const VECTOR3 goalPos,   VECTOR3& outPos);

	//�o�H�T���̒T���ς݂�����
	void ClearNavEdgeSearch();

	//��̃x�N�g���̊Ԃ�Tpos�����邩�ǂ����̔���
	bool InPosition(const VECTOR3& rpos, const VECTOR3& pos1, const VECTOR3& pos2, const VECTOR3& tpos);

	//
	bool rayVsray2D(const VECTOR3 posA1, const VECTOR3 posA2, const VECTOR3 posB1, const VECTOR3 posB2);

	//��̃G�b�W�̒��_���ǂꂩ�ڐG���Ă����Ȃ�true��Ԃ�
	bool Contant(NavEdge*& edge1, NavEdge*& edge2);

	//��̃x�N�g���̊Ԃ̊p�x�̎Z�o
	float GetAngle(const VECTOR3& rpos, const VECTOR3& pos1, const VECTOR3& pos2 );

	//======================================
	//SearchRoat�֐��ŕK�v�Ȋ֐�
	//====================================== 
	
	//���[�J����Ԃ��烏�[���h���W
	void NavModelLocalToWorld(const int navModelIndex);

	//���b�V���z��̍쐬
	void CreateNavMeshes();

	//�ׂ̃��b�V���̊֘A����
	void RelatedToNextMesh();

	//�_�C�N�X�g���@�ŖڕW�̎Z�o
	void DijkstraMesh(std::queue<NavEdge*>& queue, NavEdge*& nowEdge, NavEdge* GoalEdge);

	//�o�H�T��������ɁA�X�^�[�g����S�[���܂ŒH��B
	void PursueNavMesh(std::stack<NavEdge*>& stack, NavEdge*& nowEdge, const NavEdge* startEdge);

	//stack�f�[�^����o�H�T�������i�r���b�V��������z��ɓ����
	void SetRoatEdge(std::stack<NavEdge*>& stack);

	//======================================
	//CreateNearRoat�֐��ŕK�v�Ȋ֐�
	//====================================== 
	
	//�Ԑ��Ɛ����t�̕��тɂȂ��Ă����琳�������ɕ��ёւ���
	void RearrangesPosition(VECTOR3 &Pos1, VECTOR3& Pos2,VECTOR3 originPos,const NavEdge* edge, const NavEdge* nextedge, VECTOR3& OutPosition);

	//�i�r���b�V���p�̎Z�o
	void SearchCorner(NavEdge* edge, NavEdge* nextedge, VECTOR3& notContctPosition, VECTOR3& pos1, VECTOR3& pos2, const VECTOR3& originPos, VECTOR3& anwer);
};